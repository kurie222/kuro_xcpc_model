#!/usr/bin/env bash
set -euo pipefail

OUT=template_book.md
TITLE="Kuro XCPC Algorithm Template (Printable)"
DATE="$(date +'%Y-%m-%d')"

echo "# ${TITLE}" > "$OUT"
echo "" >> "$OUT"
echo "_Generated on: ${DATE}_" >> "$OUT"
echo "" >> "$OUT"
echo "> This handbook is auto-assembled from source code. **Excluded**: Testlib/ and license files." >> "$OUT"
echo "" >> "$OUT"

# In-PDF Table of Contents (requires pandoc --toc --toc-placement=inline)
echo "[TOC]" >> "$OUT"
echo "" >> "$OUT"

# Directories to include (English section titles kept as-is)
DIRS=(BasicAlgo Datastructure Graph Math String)

for DIR in "${DIRS[@]}"; do
  if [ -d "$DIR" ]; then
    echo "" >> "$OUT"
    echo "## ${DIR}" >> "$OUT"
    echo "" >> "$OUT"

    # collect headers/sources, skip nothing inside these dirs (no Testlib here)
    find "$DIR" -type f \( -name "*.cpp" -o -name "*.cc" -o -name "*.hpp" -o -name "*.h" \) \
      | sort | while read -r f; do
        base="$(basename "$f")"
        echo "" >> "$OUT"
        echo "### ${base}" >> "$OUT"
        echo "" >> "$OUT"
        echo '```cpp' >> "$OUT"
        # strip UTF-8 BOM if any; keep file content verbatim
        sed '1s/^\xEF\xBB\xBF//' "$f" >> "$OUT"
        echo '```' >> "$OUT"
      done
  fi
done

# Optional appendix
cat >> "$OUT" <<'EOF'

## Notes
- Suggested flags: `-O2 -std=gnu++20 -Wall -Wextra`. Add `-Ofast` only when safe.
- Avoid duplicate macros/identifiers across modules (`INF`, `mod`, `N`, etc.).
- For faster compile & fewer conflicts, copy only needed modules into contest code.

EOF

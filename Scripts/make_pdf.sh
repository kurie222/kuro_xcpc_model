#!/usr/bin/env bash
set -euo pipefail

MD=template_book.md
PDF=template_book.pdf

# 选引擎：你用 xelatex 就优先它；没有则尝试 tectonic；都没有就给 HTML 预览
ENGINE=""
if command -v xelatex >/dev/null 2>&1; then
  ENGINE="xelatex"
elif command -v tectonic >/dev/null 2>&1; then
  ENGINE="tectonic"
else
  echo "WARN: 未找到 xelatex/tectonic，输出 HTML 预览 template_book.html"
  pandoc "$MD" -o template_book.html --toc --highlight-style=tango
  exit 0
fi

# header：xelatex 走 ctex，自动中文字体；同时配置 listings 断行
HEADER=scripts/header.tex
mkdir -p scripts
if [ "$ENGINE" = "xelatex" ]; then
cat > "$HEADER" <<'EOT'
\usepackage[UTF8]{ctex}    % 自动选择系统中文字体
\usepackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{}
\lhead{Kuro XCPC Template}
\rhead{\leftmark}
\cfoot{\thepage}

% 代码块设置（listings）
\usepackage{listings}
\lstset{
  breaklines=true,
  breakatwhitespace=false,
  columns=fullflexible,
  keepspaces=true,
  basicstyle=\ttfamily\small,
  postbreak=\mbox{$\hookrightarrow$\space}
}
EOT
else
cat > "$HEADER" <<'EOT'
\usepackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{}
\lhead{Kuro XCPC Template}
\rhead{\leftmark}
\cfoot{\thepage}

% 代码块设置（listings）
\usepackage{listings}
\lstset{
  breaklines=true,
  breakatwhitespace=false,
  columns=fullflexible,
  keepspaces=true,
  basicstyle=\ttfamily\small,
  postbreak=\mbox{$\hookrightarrow$\space}
}
EOT
fi

# 先尝试：listings + 语法高亮（避免 Shaded 盒子）
set +e
pandoc "$MD" -o "$PDF" \
  --pdf-engine="$ENGINE" \
  --listings \
  --toc --toc-depth=3 \
  --highlight-style=tango \
  -V geometry:margin=1.6cm \
  -H "$HEADER"
rc=$?
set -e

# 如仍失败，自动回退为无高亮（最稳）
if [ $rc -ne 0 ]; then
  echo "INFO: listings 渲染失败，自动回退到 --no-highlight。"
  pandoc "$MD" -o "$PDF" \
    --pdf-engine="$ENGINE" \
    --no-highlight \
    --toc --toc-depth=3 \
    -V geometry:margin=1.6cm \
    -H "$HEADER"
fi

echo "生成完成：$PDF"

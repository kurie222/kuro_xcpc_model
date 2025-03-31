class st_table
{
public:
    st_table(vector<int> &a)
    {
        siz = a.size() - 1; // 1-index
        LOG2.resize(siz + 1);
        table.resize(siz + 1);
        for (int i = 0; i <= siz; i++)
        {
            table[i].resize(30);
        }
        for (int i = 0; i <= siz; i++)
            table[i][0] = a[i];
        for (int i = 2; i <= siz; i++)
            LOG2[i] = LOG2[i / 2]+1;
        for (int j = 1; j <= LOG2[siz]; j++)
            for (int i = 1; i + (1 << (j - 1)) <= siz; i++)
            {
                table[i][j] = op(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
                // op[i,i+2^j-1]
            }
    }
    int ask(int l, int r)
    {
        assert(l >= 1 && r <= siz && l <= r);
        if (l == r)
            return table[l][0];
        int tp = (LOG2[r - l + 1]);
        return op(table[l][tp], table[r + 1 - (1 << tp)][tp]);
    }

private:
    int siz;
    vector<int> LOG2;
    vector<vector<int>> table;
    int op(int a, int b)
    {
        return std::max(a, b);
    }
};
class st_table
{
public:
    st_table(vector<int> &a)
    {
        siz = a.size() - 1; // 1-index
        LOG2.resize(siz + 1);
        table.resize(24);
        for (int i = 0; i <24; i++)
        {
            table[i].resize(siz+1);
        }
        for (int i = 0; i <= siz; i++)
            table[0][i] = a[i];
        for (int i = 2; i <= siz; i++)
            LOG2[i] = LOG2[i / 2] + 1;
        for (int j = 1; j <= LOG2[siz]; j++)
            for (int i = 1; i + (1 << (j - 1)) <= siz; i++)
            {
                table[j][i] = op(table[j - 1][i], table[j-1][i + (1 << (j - 1))]);
                // op[i,i+2^j-1]
            }
    }
    int ask(int l, int r)
    {
        assert(l >= 1 && r <= siz && l <= r);
        if (l == r)
            return table[0][l];
        int tp = (LOG2[r - l + 1]);
        return op(table[tp][l], table[tp][r + 1 - (1 << tp)]);
    }

private:
    int siz;
    vector<int> LOG2;
    vector<vector<int>> table;
    int op(int a, int b)
    {
        return std::gcd(a, b);
    }
};
struct matrix
{
    vector<vector<int>> data;
    int row, column; // 行，列
    long long MOD = __INT64_MAX__;
    matrix(int n) // 构造n行n列矩阵
    {
        data.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            data[i].resize(n + 1);
        }
        row = n;
        column = n;
    }
    matrix(int n, int m) // 构造n行m列矩阵
    {
        data.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            data[i].resize(m + 1);
        }
        row = n;
        column = m;
    }
    void setmod(int modd)
    {
        MOD=modd;
    }
    matrix operator-(const matrix &T) const
    {
        if (this->column != T.column || this->row != T.row)
        {
            cerr << "minus error!" << endl;
            return matrix(0);
        }
        matrix res(*this);
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
            {
                res.data[i][j] -= T.data[i][j];
                res.data[i][j] = (res.data[i][j] + MOD) % MOD;
            }
        return res;
    }

    matrix operator+(const matrix &T) const
    {
        if (this->column != T.column || this->row != T.row)
        {
            cerr << "add error!" << endl;
            return matrix(0);
        }
        matrix res(*this);
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
            {
                res.data[i][j] += T.data[i][j];
                res.data[i][j] %= MOD;
            }
        return res;
    }

    matrix operator*(const matrix &T) const
    {
        if (this->column != T.row)
        {
            cerr << "mul error" << endl;
            return matrix(0);
        }
        matrix res(row, T.column);
        int r;
        for (int i = 1; i <= res.row; ++i)
            for (int k = 1; k <= this->column; ++k)
            {
                r = data[i][k];
                for (int j = 1; j <= res.column; ++j)
                    res.data[i][j] += T.data[k][j] * r, res.data[i][j] %= MOD;
            }
        return res;
    }

    matrix operator^(long long x) const
    {
        if (column != row)
        {
            cerr << "pow error" << Endl;
            return matrix(0);
        }
        if (x == 1)
            return *this;
        matrix res(column), bas(column);
        for (int i = 1; i <= column; ++i)
            res.data[i][i] = 1;
        for (int i = 1; i <= column; ++i)
            for (int j = 1; j <= column; ++j)
                bas.data[i][j] = data[i][j] % MOD;
        while (x)
        {
            if (x & 1)
                res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
};
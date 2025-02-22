/*
    2025/2/22更新:
    使用模版重写了这个远古矩阵类，使其支持用二维vector直接生成
    注意，普通的快速幂使用的幺元是1，矩阵需要使用单位矩阵
    所以矩阵快速幂在使用时需调用矩阵的qpow成员函数代替泛型快速幂！！！
    尤其是在联合mint使用时
*/

template <typename T>
struct matrix
{
    vector<vector<T>> data;
    int row, column; // 行，列 :1-index
    matrix(vector<vector<T>> vec)
    {
        data = vec;
        row = vec.size() - 1;
        column = vec[1].size() - 1;
    }
    matrix(int n) // 构造n行n列矩阵
    {
        data.resize(n + 1);
        for (int i = 1; i <= n; i++)
        {
            data[i].resize(n + 1);
            data[i][i] = 1;
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
    matrix<T> operator-(const matrix<T> &temp) const
    {
        if (this->column != temp.column || this->row != temp.row)
        {
            cerr << "minus error!" << endl;
            return matrix<T>(0);
        }
        matrix<T> res(*this);
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
            {
                res.data[i][j] -= temp.data[i][j];
                res.data[i][j] = (res.data[i][j]);
            }
        return res;
    }

    matrix<T> operator+(const matrix<T> &temp) const
    {
        if (this->column != temp.column || this->row != temp.row)
        {
            cerr << "add error!" << endl;
            return matrix<T>(0);
        }
        matrix<T> res(*this);
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
            {
                res.data[i][j] += temp.data[i][j];
            }
        return res;
    }

    matrix<T> operator*(const matrix<T> &temp) const
    {
        if (this->column != temp.row)
        {
            cerr << "mul error" << endl;
            return matrix<T>(0);
        }
        matrix<T> res(row, temp.column);
        mint r;
        for (int i = 1; i <= res.row; ++i)
            for (int k = 1; k <= this->column; ++k)
            {
                r = data[i][k];
                for (int j = 1; j <= res.column; ++j)
                    res.data[i][j] += temp.data[k][j] * r;
            }
        return res;
    }
    matrix<T> qpow(int64_t x)
    {
        if (this->column != this->row)
        {
            cerr << "pow error" << Endl;
            return matrix<T>(0);
        }
        if (x == 1)
            return *this;
        matrix<T> res(this->column), bas(this->column);
        for (int i = 1; i <= this->column; ++i)
            res.data[i][i] = 1;
        for (int i = 1; i <= this->column; ++i)
            for (int j = 1; j <= this->column; ++j)
                bas.data[i][j] = this->data[i][j];
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
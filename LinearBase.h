struct LinearBase
{
    // 高斯消元前 idx从0开始
    // 高斯消元后 idx从0开始
    // 前缀线性基：维护一个当前基底的右端点，插入如果靠右，就交换
    int N;
    vector<ull> base;
    int iffzero = 0;
    LinearBase()
    {
        N = 100;
        base.resize(102);
    }
    LinearBase(int n)
    {
        N = n + 5;
        base.resize(n + 20);
    }
    void clear()
    {
        N = 0;
        base.clear();
    }
    bool insert(ull x)
    {
        assert(N != 0);
        for (int i = 62; i >= 0; i--)
        {
            if (!(x & (1ull << i)))
                continue;
            if (!base[i])
            {
                base[i] = x;
                return 1;
            }
            x ^= base[i];
            if (x == 0)
            {
                iffzero = 1;
                return false;
            }
        }
        return 1;
    }
    void gauss()
    {
        assert(N != 0);
        sort(base.begin(), base.end(), greater<ull>());
        int row = 0;
        for (int i = 62; i >= 0; i--)
        {
            for (int j = row; j < N; j++)
            {
                if ((1ull << i) & base[j])
                {
                    swap(base[j], base[row]);
                }
            }
            if (!((1ull << i) & base[row]))
                continue;
            for (int j = 0; j < N; j++)
            {
                if (j == row)
                    continue;
                if ((1ull << i) & base[j])
                {
                    base[j] ^= base[row];
                }
            }
            row++;
        }
    }
    void printbi(ull x)
    {
        for (int j = 62; j >= 0; j--)
        {
            if ((1ull << j) & x)
            {
                cerr << 1;
            }
            else
                cerr << 0;
        }
        cerr << endl;
    }
    void print()
    {
        assert(N != 0);
        for (int i = 0; i < N; i++)
        {
            for (int j = 62; j >= 0; j--)
            {
                if ((1ull << j) & base[i])
                {
                    cerr << 1;
                }
                else
                    cerr << 0;
            }
            cerr << endl;
        }
        cerr << endl;
    }
    LinearBase merge(LinearBase &lb1, LinearBase &lb2)
    {
        LinearBase ans;
        for (int i = 0; i < 65; i++)
        {
            ans.insert(lb1.base[i]);
            ans.insert(lb2.base[i]);
        }
        return ans;
    };
};

struct LinearBase  //前缀线性基模版参考，注意！开了unsigned int
{
    // 高斯消元前 idx从1开始
    // 高斯消元后 idx从0开始
    int N;
    vector<unsigned int> base;
    vector<int> idx;
    int iffzero = 0;
    LinearBase()
    {
        N = 20;
        base.resize(21);
        idx.resize(21);
    }
    LinearBase(int n)
    {
        N = n + 5;
        base.resize(n + 20);
    }
    void clear()
    {
        N = 0;
        base.clear();
    }
    bool insert(ull x,int dx)
    {
        assert(N != 0);
        for (int i = 20; i >= 0; i--)
        {
            if (!(x & (1ull << i)))
                continue;
            if (!base[i])
            {
                base[i] = x;
                idx[i]=dx;
                return 1;
            }
            if(idx[i]<dx)
            {
                swap(base[i],x);
                swap(idx[i],dx);
            }
            x ^= base[i];
            if (x == 0)
            {
                iffzero = 1;
                return false;
            }
        }
        return 1;
    }
    void gauss()
    {
        assert(N != 0);
        sort(base.begin(), base.end(), greater<ull>());
        int row = 0;
        for (int i = 20; i >= 0; i--)
        {
            for (int j = row; j < N; j++)
            {
                if ((1ull << i) & base[j])
                {
                    swap(base[j], base[row]);
                    swap(idx[j],idx[row]);
                }
            }
            if (!((1ull << i) & base[row]))
                continue;
            for (int j = 0; j < N; j++)
            {
                if (j == row)
                    continue;
                if ((1ull << i) & base[j])
                {
                    base[j] ^= base[row];
                }
            }
            row++;
        }
    }
    void printbi(ull x)
    {
        for (int j = 20; j >= 0; j--)
        {
            if ((1ull << j) & x)
            {
                cerr << 1;
            }
            else
                cerr << 0;
        }
        cerr << endl;
    }
    void print()
    {
        assert(N != 0);
        for (int i = 0; i < N; i++)
        {
            for (int j = 20; j >= 0; j--)
            {
                if ((1ull << j) & base[i])
                {
                    cerr << 1;
                }
                else
                    cerr << 0;
            }
            cerr << endl;
        }
        cerr << endl;
    }
};
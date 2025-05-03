struct LinearBase
{
    // 高斯消元前 idx从0开始
    // 高斯消元后 idx从0开始
    // 前缀线性基：维护一个当前基底的右端点，插入如果靠右，就交换
    int N;
    vector<ull> base;
    LinearBase()
    {
        N = 60;
        base.resize(64);
    }
    bool insert(ull x)
    {
        assert(N != 0);
        for (int i = N; i >= 0; i--)
        {
            if (!(x & (1ull << i)))
                continue;
            if (!base[i])
            {
                base[i] = x;
                return true;
            }
            x ^= base[i];
            if (x == 0)
            {
                return false;
            }
        }
        return 1;
    }
    bool query(ull x)
    {
        assert(N != 0);
        for (int i = N; i >= 0; i--)
        {
            if (!(x & (1ull << i)))
                continue;
            if (!base[i])
            {
                return 0;
            }
            x ^= base[i];
            if (x == 0)
            {
                return true;
            }
        }
        return 0;
    }
    void gauss()
    {
        assert(N != 0);
        sort(base.begin(), base.end(), greater<ull>());
        int row = 0;
        for (int i = N; i >= 0; i--)
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
};
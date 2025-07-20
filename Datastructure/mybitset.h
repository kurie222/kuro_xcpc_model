using u64 = unsigned long long;
// 0-index
class dybitset
{
public:
    dybitset();
    dybitset(int n)
    {
        siz = n;
        data.resize((n + 63) / 64);
        back_size = n % 64;
    }
    //  默认插入函数都是要插入低sz位
    dybitset(u64 init_data, int sz)
    {
        push_back(init_data, sz);
    }
    //  默认插入函数都是要插入低sz位
    void push_back(u64 init_data, int sz)
    {
        if (sz < 64)
        {
            u64 full2 = (1ull << sz) - 1;
            init_data &= full2;
        }
        if (back_size == 0)
        {
            data.push_back(init_data);
            siz += sz;
            back_size = sz;
            back_size %= 64;
            return;
        }
        if (sz + back_size <= 64)
        {
            int idx = (siz + 63) / 64;
            if (idx >= (int)data.size())
                data.push_back(0);
            data[idx] |= (init_data << back_size);
            siz += sz;
            back_size += sz;
            back_size %= 64;
            return;
        }
        if (sz + back_size > 64)
        {
            int sz1 = 64 - back_size;
            {
                int idx = (siz + 63) / 64;
                if (idx >= (int)data.size())
                    data.push_back(0);
                data[idx] |= (init_data << back_size);
            }
            data.push_back(init_data >> sz1);
            siz += sz;
            back_size += sz;
            back_size %= 64;
            return;
        }
    }
    // 0-index
    bool at(int x)
    {
        assert(x >= 0 && x < siz);
        return (data[x / 64] >> (x % 64)) & 1;
    }
    void set(int x, bool val)
    {
        assert(x >= 0 && x <= siz);
        if (((data[x / 64] >> (x % 64)) ^ val))
            data[x / 64] ^= (1ull) << (x % 64);
    }
    dybitset substr(int l, int r)
    {
        dybitset tp;
        if (l / 64 == r / 64)
        {
            // int ldx=l%64;
            tp.push_back(data[l / 64] >> (l % 64), r - l + 1);
        }
        else
        {
            int li = l / 64, ri = r / 64;
            li++;
            ri--;
            tp.push_back(data[l / 64] >> (l % 64), 64 - (l % 64));
            while (li <= ri)
            {
                tp.push_back(data[li], 64);
                li++;
            }
            tp.push_back(data[r / 64], r % 64 + 1);
        }
        return tp;
    }
    // 特化实现，注意，要求取出的长度不大于64
    u64 substr2(int l, int r)
    {
        assert(r - l + 1 <= 64);
        if (l / 64 == r / 64)
        {
            // int ldx=l%64;
            // tp.push_back(data[l / 64] >> (l % 64), r - l + 1);
            u64 full2 = (1ull << (r - l + 1)) - 1;
            return (data[l / 64] >> (l % 64)) & full2;
        }
        else
        {
            int li = l / 64, ri = r / 64;

            // li++;
            // ri--;
            // tp.push_back(data[l / 64] >> (l % 64), 64 - (l % 64));
            int sz1 = 64 - (l % 64);
            u64 full2 = (1ull << sz1) - 1;
            u64 ans = (data[li] >> (l % 64)) & full2;
            int sz2 = r % 64 + 1;
            u64 full3 = (1ull << sz2) - 1;
            ans |= (((data[ri]) & full3) << sz1);
            // tp.push_back(data[ri], r % 64 + 1);
            return ans;
        }
        // return tp;
    }
    void flip(int x)
    {
        assert(x >= 0 && x < siz);
        data[x / 64] ^= (1ull) << (x % 64);
    }

    int siz = 0, back_size = 0;
    vector<u64> data;
};
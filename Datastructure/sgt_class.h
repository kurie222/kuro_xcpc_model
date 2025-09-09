//该版本需要注意的是：对于vec的[1,n]建树，用构造函数需要传真实大小(n)！！！否则会RE
struct segment_tree_node_lazytag
{
    long long add;
};
class segment_tree
{
public:
    segment_tree(int max_size)
    {
        init(max_size);
        build(1, max_size);
    }
    segment_tree(int max_size, vector<int> &vec)
    {
        init(max_size);
        build(1, max_size, vec);
    }
    int find_sum(int l, int r, int idx = 1)
    {
        if (lidx[idx] > r || ridx[idx] < l)
            return 0;
        if (lidx[idx] >= l && ridx[idx] <= r)
            return val[idx];
        pushdown(idx);
        return find_sum(l, r, idx * 2) + find_sum(l, r, idx * 2 + 1);
    }
    int find_max(int l, int r, int idx = 1) // maxvalue maxidx
    {
        if (lidx[idx] > r || ridx[idx] < l)
            return -1;
        if (lidx[idx] >= l && ridx[idx] <= r)
            return maxv[idx];
        pushdown(idx);
        auto a = find_max(l, r, idx * 2), b = find_max(l, r, idx * 2 + 1);
        rt max(a,b);
    }
    void add(int l, int r, int add_val, int idx = 1)
    {
        if (lidx[idx] > r || ridx[idx] < l)
            return;
        if (lidx[idx] >= l && ridx[idx] <= r)
        {
            tag[idx].add += add_val;
            val[idx] += add_val * len[idx];
            maxv[idx] += add_val;
            return;
        }
        pushdown(idx);
        add(l, r, add_val, idx * 2);
        add(l, r, add_val, idx * 2 + 1);
        pushup(idx);
    } // 区间加上x
    void set(int l, int val, int idx = 1)
    {
        if (lidx[idx] > l || ridx[idx] < l)
            return;
        if (lidx[idx] == l && ridx[idx] == l)
        {
            this->val[idx] = val;
            maxv[idx] = val;
            return;
        }
        pushdown(idx);
        set(l, val, idx * 2);
        set(l, val, idx * 2 + 1);
        pushup(idx);
    }
private:
    // std::vector<segment_tree_node> tree;
    vector<int> val,lidx,ridx,len;
    vector<int> maxv,maxidx;
    vector<segment_tree_node_lazytag> tag;
    void init(int maxSize)
    {
        maxSize*=4;
        maxSize+=5;
        val.resize(maxSize);
        lidx.resize(maxSize);
        ridx.resize(maxSize);
        maxv.resize(maxSize);
        maxidx.resize(maxSize);
        tag.resize(maxSize);
        len.resize(maxSize);
    }
    void build(int l, int r, std::vector<int> &a, int idx = 1)
    {
        lidx[idx] = l;
        ridx[idx] = r;
        len[idx]=r-l+1;
        if (l == r)
        {
            val[idx] = a[l];
            maxv[idx] = a[l];
            maxidx[idx] = l;
        }
        else
        {
            int mid = (l + r) >> 1;
            build(l, mid, a, idx * 2);
            build(mid + 1, r, a, idx * 2 + 1);
            pushup(idx);
        }
    }
    void build(int l, int r, int idx = 1)
    {
        vector<int> tp(r+1);
        build(l,r,tp);
    }
    inline void pushdown(int idx)
    {
        if(tag[idx].add==0|| lidx[idx] == ridx[idx]) return;
        tag[idx * 2].add += tag[idx].add;
        tag[idx * 2 + 1].add += tag[idx].add;
        val[idx * 2] += len[idx*2] * tag[idx].add;
        val[idx * 2 + 1] += len[idx*2+1] * tag[idx].add;
        maxv[idx * 2] += tag[idx].add;
        maxv[idx * 2 + 1] += tag[idx].add;
        tag[idx].add = 0;
    }
    inline void pushup(int idx)
    {
        val[idx] = val[idx * 2] + val[idx * 2 + 1];
        if (maxv[idx * 2] >= maxv[idx * 2 + 1])
        {
            maxidx[idx] = maxidx[idx * 2];
        }
        else
        {
            maxidx[idx] = maxidx[idx * 2 + 1];
        }
        maxv[idx] = std::max(maxv[idx * 2], maxv[idx * 2 + 1]);
    }
};
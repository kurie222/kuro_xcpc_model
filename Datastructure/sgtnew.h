struct segment_tree_node_lazytag
{
    long long add;
};
struct segment_tree_node
{
    long long val;
    long long length;
    int l, r;
    long long min;
    int minidx; // 这个模版维护的是最小idx
    segment_tree_node_lazytag tag;
};
struct segment_tree
{
    std::vector<segment_tree_node> tree;
    segment_tree(int max_size)
    {
        tree.resize(max_size * 4 + 100);
    }
    void pushup(int idx)
    {
        tree[idx].val = tree[idx * 2].val + tree[idx * 2 + 1].val;
        if (tree[idx * 2].min <= tree[idx * 2 + 1].min)
        {
            tree[idx].minidx = tree[idx * 2].minidx;
        }
        else
        {
            tree[idx].minidx = tree[idx * 2 + 1].minidx;
        }
        tree[idx].min = std::min(tree[idx * 2].min, tree[idx * 2 + 1].min);
    }
    void build(int l, int r, std::vector<int> &a, int idx = 1)
    {
        tree[idx].l = l;
        tree[idx].r = r;
        tree[idx].length = r - l + 1;
        if (l == r)
        {
            tree[idx].val = a[l];
            tree[idx].length = 1;
            tree[idx].l = tree[idx].r = l;
            tree[idx].min = a[l];
            tree[idx].minidx = l;
        }
        else
        {
            int mid = (l + r) >> 1;
            build(l, mid, a, idx * 2);
            build(mid + 1, r, a, idx * 2 + 1);
            pushup(idx);
        }
    }

    void pushdown(int idx)
    {
        tree[idx * 2].tag.add += tree[idx].tag.add;
        tree[idx * 2 + 1].tag.add += tree[idx].tag.add;
        tree[idx * 2].val += tree[idx * 2].length * tree[idx].tag.add;
        tree[idx * 2 + 1].val += tree[idx * 2 + 1].length * tree[idx].tag.add;
        tree[idx * 2].min += tree[idx].tag.add;
        tree[idx * 2 + 1].min += tree[idx].tag.add;
        tree[idx].tag.add = 0;
    }
    ll find_sum(int l, int r, int idx = 1)
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return 0;
        if (tree[idx].l >= l && tree[idx].r <= r)
            return tree[idx].val;
        pushdown(idx);
        pushup(idx);
        return find_sum(l,r,idx*2)+find_sum(l,r,idx*2+1);
    }
    pair<ll,ll> find_min(int l, int r, int idx = 1)//minvalue minidx
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return {INT64_MAX,-1};
        if (tree[idx].l >= l && tree[idx].r <= r)
            return {tree[idx].min,tree[idx].minidx};
        pushdown(idx);
        pushup(idx);
        auto a=find_min(l, r, idx * 2), b=find_min(l, r, idx * 2 + 1);
        if(a.first<=b.first) rt a;
        else rt b;
    }
    void add(int l, int r, int add_val, int idx = 1)
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return;
        if (tree[idx].l >= l && tree[idx].r <= r)
        {
            tree[idx].tag.add += add_val;
            tree[idx].val += add_val * tree[idx].length;
            tree[idx].min += add_val;
            return;
        }
        pushdown(idx);
        add(l, r, add_val, idx * 2);
        add(l, r, add_val, idx * 2 + 1);
        pushup(idx);
    } // 区间加上x
    void set(int l, int val, int idx = 1)
    {
        if (tree[idx].l > l || tree[idx].r < l)
            return;
        if (tree[idx].l == l && tree[idx].r == l)
        {
            tree[idx].val = val;
            tree[idx].min = val;
            return;
        }
        pushdown(idx);
        set(l, val, idx * 2);
        set(l, val, idx * 2 + 1);
        pushup(idx);
    }
};
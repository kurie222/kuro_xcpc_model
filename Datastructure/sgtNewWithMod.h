struct segment_tree_node
{
    long long val;
    long long length;
    int l, r;
    long long max;
    ll maxidx = 0;
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
        tree[idx].max = std::max(tree[idx * 2].max, tree[idx * 2 + 1].max);
        if(tree[idx * 2].max>=tree[idx * 2 + 1].max)
        {
            tree[idx].maxidx=tree[idx*2].maxidx;
        }
        else
            tree[idx].maxidx=tree[idx*2+1].maxidx;
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
            tree[idx].max = a[l];
            tree[idx].maxidx = l;
        }
        else
        {
            int mid = (l + r) >> 1;
            build(l, mid, a, idx * 2);
            build(mid + 1, r, a, idx * 2 + 1);
            pushup(idx);
        }
    }
    ll find_sum(int l, int r, int idx = 1)
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return 0;
        if (tree[idx].l >= l && tree[idx].r <= r)
            return tree[idx].val;
        pushup(idx);
        return find_sum(l, r, idx * 2) + find_sum(l, r, idx * 2 + 1);
    }
    pair<ll, ll> find_max(int l, int r, int idx = 1) // minvalue minidx
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return {-1, -1};
        if (tree[idx].l >= l && tree[idx].r <= r)
            return {tree[idx].max, tree[idx].maxidx};
        pushup(idx);
        auto a = find_max(l, r, idx * 2), b = find_max(l, r, idx * 2 + 1);
        if (a.first >= b.first)
            rt a;
        else
            rt b;
    }
    void set(int l, int val, int idx = 1)
    {
        if (tree[idx].l > l || tree[idx].r < l)
            return;
        if (tree[idx].l == l && tree[idx].r == l)
        {
            tree[idx].val = val;
            tree[idx].max = val;
            return;
        }
        set(l, val, idx * 2);
        set(l, val, idx * 2 + 1);
        pushup(idx);
    }
    void md(int l, int r, int m, int idx = 1)
    {
        // while(find_max(l,r).first>=m)
        // {
        //     auto [x,y]=find_max(l,r);
        //     set(y,x%m);
        // }
        if (tree[idx].l > r || tree[idx].r < l)
            return;
        if (tree[idx].l >= l && tree[idx].r <= r)
        {
            if (tree[idx].l == tree[idx].r)
            {
                tree[idx].val %= m;
                tree[idx].max %=m;
                rt;
            }
            if (tree[idx].max < m)
            {
                rt;
            }
            md(l, r, m, idx * 2);
            md(l, r, m, idx * 2 + 1);
            pushup(idx);
            rt;
        }
        md(l, r, m, idx * 2);
        md(l, r, m, idx * 2 + 1);
        pushup(idx);
    }
};
//常数极大，非必要情况让队友写
struct segment_tree_node_lazytag
{
    long long add;
};
struct segment_tree_node
{
    long long val;
    int length;
    int l, r;
    int ls, rs;
};
struct presist_segment_tree
{
    std::vector<segment_tree_node> tree;
    presist_segment_tree(int max_size)
    {
        tree.resize((25)*max_size);
    }
    void pushup(int idx)
    {
        int ls = tree[idx].ls, rs = tree[idx].rs;
        tree[idx].val = tree[ls].val + tree[rs].val;
    }
    void build(int l, int r, std::vector<int> &a, int idx)
    {
        tree[idx].l = l;
        tree[idx].r = r;
        tree[idx].length = r - l + 1;
        if (l == r)
        {
            tree[idx].val = a[l];
            tree[idx].length = 1;
            tree[idx].l = tree[idx].r = l;
        }
        else
        {
            int mid = (l + r) >> 1;
            tree[idx].ls = idxx;
            
            idxx++;
            build(l, mid, a, tree[idx].ls);
            tree[idx].rs = idxx;
            idxx++;
            build(mid + 1, r, a, tree[idx].rs);
            pushup(idx);
        }
    }
    ll find_sum(int l, int r, int idx)
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return 0;
        if (tree[idx].l >= l && tree[idx].r <= r)
            return tree[idx].val;
        return find_sum(l, r, tree[idx].ls) + find_sum(l, r, tree[idx].rs);
    }
    int set(int l, int val, int idx)
    {
        if (tree[idx].l > l || tree[idx].r < l)
            return idx;
        if (tree[idx].l == l && tree[idx].r == l)
        {
            int tidx = idxx++;
            tree[tidx] = tree[idx];
            tree[idx].val = val;
            swap(tree[idx], tree[tidx]);
            return tidx;
        }
        int tidx = idxx++;
        tree[tidx] = tree[idx];
        tree[tidx].ls = set(l, val, tree[idx].ls);
        tree[tidx].rs = set(l, val, tree[idx].rs);
        pushup(tidx);
        return tidx;
    }
};
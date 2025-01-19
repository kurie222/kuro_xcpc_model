template <typename valType, typename canBeComparedType>
struct segment_tree_node
{
    valType val;
    int length;
    int l, r;
    canBeComparedType min;
    int minidx; // 这个模版维护的是最小idx
};
template <typename valType, typename canBeComparedType>
struct segment_tree
{
    std::vector<segment_tree_node<valType, canBeComparedType>> tree;
    std::function<bool(canBeComparedType, canBeComparedType)> compareFunction;
    std::function<valType(valType, valType)> combineFunction;
    valType valE;
    canBeComparedType compE;
    segment_tree(int max_size, valType valueE, canBeComparedType compareE, std::function<valType(valType, valType)> op = std::plus<valType>(),
    std::function<bool(canBeComparedType, canBeComparedType)> spLess = std::less<canBeComparedType>())
    {
        tree.resize(max_size * 4 + 100);
        combineFunction = op;
        compareFunction = spLess;
        valE = valueE;
        compE = compareE;
    }
    void pushup(int idx)
    {
        tree[idx].val = combineFunction(tree[idx * 2].val, tree[idx * 2 + 1].val);
        if (compareFunction(tree[idx * 2].min, tree[idx * 2 + 1].min))
        {
            tree[idx].minidx = tree[idx * 2].minidx;
            tree[idx].min = tree[idx * 2].min;
        }
        else
        {
            tree[idx].minidx = tree[idx * 2 + 1].minidx;
            tree[idx].min = tree[idx * 2 + 1].min;
        }
    }
    void build(int l, int r, std::vector<valType> &a, int idx = 1)
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
    }
    ll find_sum(int l, int r, int idx = 1)
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return valE;
        if (tree[idx].l >= l && tree[idx].r <= r)
            return tree[idx].val;
        pushdown(idx);
        pushup(idx);
        return combineFunction(find_sum(l, r, idx * 2),find_sum(l, r, idx * 2 + 1));
    }
    pair<canBeComparedType, int> find_min(int l, int r, int idx = 1) // minvalue minidx
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return {compE, 0};
        if (tree[idx].l >= l && tree[idx].r <= r)
            return {tree[idx].min, tree[idx].minidx};
        pushdown(idx);
        pushup(idx);
        auto a = find_min(l, r, idx * 2), b = find_min(l, r, idx * 2 + 1);
        if (compareFunction(a.first, b.first))
            return a;
        else
            return b;
    }
    void set(int l, valType val, int idx = 1)
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
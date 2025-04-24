// hld传入真实大小！！！
//注意：addedge只需要进行任意方向的一次，就会加两条边！！！
template<class T>
constexpr T qpow(T a, long long b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
template<long long P>
struct modint {
    long long x;
    constexpr modint() : x{} {}
    constexpr modint(long long x) : x{norm(x % getMod())} {}
    
    inline static long long Mod=998244353;
    constexpr static long long getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(long long Mod_) {
        Mod = Mod_;
    }
    constexpr long long norm(long long x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr long long val() const {
        return x;
    }
    explicit constexpr operator long long() const {
        return x;
    }
    constexpr modint operator-() const {
        modint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr modint inv() const {
        assert(x != 0);
        return qpow(*this, getMod() - 2);
    }
    constexpr modint &operator*=(modint rhs) & {
        x = x*rhs.x;
        x%=getMod();
        return *this;
    }
    constexpr modint &operator+=(modint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr modint &operator-=(modint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr modint &operator/=(modint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr modint operator*(modint lhs, modint rhs) {
        modint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr modint operator+(modint lhs, modint rhs) {
        modint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr modint operator-(modint lhs, modint rhs) {
        modint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr modint operator/(modint lhs, modint rhs) {
        modint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, modint &a) {
        long long v;
        is >> v;
        a = modint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const modint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(modint lhs, modint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(modint lhs, modint rhs) {
        return lhs.val() != rhs.val();
    }
};
using mint=modint<998244353>;
struct segment_tree_node_lazytag
{
    long long add=0;
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
class segment_tree
{
public:
    segment_tree(int max_size)
    {
        tree.resize(max_size * 4 + 10);
        build(1, max_size);
    }
    segment_tree(int max_size, vector<int> &vec)
    {
        tree.resize(max_size * 4 + 10);
        build(1, max_size, vec);
    }
    long long find_sum(int l, int r, int idx = 1)
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return 0;
        if (tree[idx].l >= l && tree[idx].r <= r)
            return tree[idx].val;
        pushdown(idx);
        pushup(idx);
        return find_sum(l, r, idx * 2) + find_sum(l, r, idx * 2 + 1);
    }
    pair<ll, ll> find_min(int l, int r, int idx = 1) // minvalue minidx
    {
        if (tree[idx].l > r || tree[idx].r < l)
            return {INT64_MAX, -1};
        if (tree[idx].l >= l && tree[idx].r <= r)
            return {tree[idx].min, tree[idx].minidx};
        pushdown(idx);
        pushup(idx);
        auto a = find_min(l, r, idx * 2), b = find_min(l, r, idx * 2 + 1);
        if (a.first <= b.first)
            rt a;
        else
            rt b;
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

private:
    std::vector<segment_tree_node> tree;
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
    void build(int l, int r, int idx = 1)
    {
        tree[idx].l = l;
        tree[idx].r = r;
        tree[idx].length = r - l + 1;
        if (l == r)
        {
            tree[idx].val = 0;
            tree[idx].length = 1;
            tree[idx].l = tree[idx].r = l;
            tree[idx].min = 0;
            tree[idx].minidx = l;
        }
        else
        {
            int mid = (l + r) >> 1;
            build(l, mid, idx * 2);
            build(mid + 1, r, idx * 2 + 1);
            pushup(idx);
        }
    }
    void pushdown(int idx)
    {
        tree[idx * 2].tag.add += tree[idx].tag.add;
        tree[idx * 2 + 1].tag.add += tree[idx].tag.add;
        tree[idx * 2].val += tree[idx * 2].length * tree[idx].tag.add;
        tree[idx * 2 + 1].val += tree[idx * 2 + 1].length * tree[idx].tag.add;
        tree[idx].tag.add = 0;
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
};
// 1-n
class HLD
{
public:
    segment_tree sgt = segment_tree(1);
    HLD(int size)
    {
        n = size;
        sgt = segment_tree(n + 1);
        fa.resize(n + 1);
        dep = siz = hson = top = dfn = rdfn = fa;
        edge.resize(n + 1);
    }
    HLD(int size, int root)
    {
        n = size;
        sgt = segment_tree(n + 1);
        fa.resize(n + 1);
        dep = siz = hson = top = dfn = rdfn = fa;
        edge.resize(n + 1);
        HLD::root = root;
    }
    HLD(int size, int root, vector<int> &initValue)
    {
        n = size;
        // sgt = segment_tree(n, initValue);
        oriVal=initValue;
        fa.resize(n + 1);
        dep = siz = hson = top = dfn = rdfn = fa;
        edge.resize(n + 1);
        HLD::root = root;
    }
    void addEdge(int u, int v)
    {
        assert(pre_tag == 0);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int lca(int u, int v)
    {
        init();
        while (top[u] != top[v])
        {
            if (dep[top[u]] > dep[top[v]])
                u = fa[top[u]];
            else
                v = fa[top[v]];
        }
        return dep[u] > dep[v] ? v : u;
    }
    long long rangeQuery(int x, int y)
    {
        init();
        long long ans = 0;
        while (top[x] != top[y])
        { // 当两个点不在同一条链上
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);                           // 把x点改为所在链顶端的深度更深的那个点
            ans += sgt.find_sum(dfn[top[x]], dfn[x]); // ans加上x点到x所在链顶端 这一段区间的点权和
            x = fa[top[x]];                           // 把x跳到x所在链顶端的那个点的上面一个点
        }
        // 直到两个点处于一条链上
        if (dep[x] > dep[y])
            swap(x, y);                      // 把x点深度更深的那个点
        ans += sgt.find_sum(dfn[x], dfn[y]); // 这时再加上此时两个点的区间和即可
        return ans ;
    }
    long long sonQuery(int x)
    {
        init();
        return sgt.find_sum(dfn[x], dfn[x] + siz[x] - 1);
    }
    inline void rangeAdd(int x, int y, int add_val)
    {
        init();
        add_val %= mod;
        while (top[x] != top[y])
        {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            sgt.add(dfn[top[x]], dfn[x], add_val);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        sgt.add(dfn[x], dfn[y], add_val);
    }

    void sonAdd(int x, int add_val)
    {
        init();
        sgt.add(dfn[x], dfn[x] + siz[x] - 1, add_val);
    }

private:
    int n;
    int root = 1;
    int pre_tag = 0;
    vector<int> fa, dep, siz, hson, top, dfn, rdfn;
    vector<vector<int>> edge;
    vector<int> oriVal;
    int cnt = 0;
    void init()
    {
        if (pre_tag)
            return;
        pre_tag = 1;
        dfs1(root, 0);
        dfs2(root, 0, root);
        if(oriVal.size())
        {
            vector<int> newVal(n+1);
            for(int i=1;i<=n;i++)
            {
                newVal[dfn[i]]=oriVal[i];
            }
            sgt=segment_tree(n,newVal);
        }
    }
    void dfs1(int now, int father)
    {
        fa[now] = father;
        dep[now] = dep[father] + 1;
        int mson = -1;
        hson[now] = -1;
        siz[now] = 1;
        for (auto i : edge[now])
        {
            if (i == father)
                continue;
            dfs1(i, now);
            if (siz[i] > mson)
            {
                mson = siz[i];
                hson[now] = i;
            }
            siz[now] += siz[i];
        }
    }
    void dfs2(int now, int fa, int t)
    {
        top[now] = t;
        cnt++;
        dfn[now] = cnt;
        rdfn[cnt] = now;
        if (hson[now] == -1)
            return;
        dfs2(hson[now], now, t); // 优先对重儿子进行 DFS，可以保证同一条重链上的点 DFS 序连续
        for (auto i : edge[now])
        {
            if (i == fa || i == hson[now])
            {
                continue;
            }
            dfs2(i, now, i);
        }
    }
};
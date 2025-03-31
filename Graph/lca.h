class LCA
{
public:
    LCA(int size, int root = 1)
    {
        this->root = root;
        siz = size;
        edge.resize(size + 2);
        dep.resize(size + 2);
        fa.resize(size + 2);
        for (int i = 0; i <= size; i++)
            fa[i].resize(30);
        LOG2.resize(size + 2);
        for (int i = 2; i <= size; i++)
        {
            LOG2[i] = LOG2[i / 2] + 1;
        }
    }
    void addEdge(int u, int v)
    {
        assert(!init_tag);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int lca(int u, int v)
    {
        if (!init_tag)
        {
            init();
        }
        if (dep[u] > dep[v])
            return lca(v, u);
        while (dep[u] != dep[v])
        {
            v = fa[v][(int)LOG2[dep[v] - dep[u]]];
        }
        if (u == v)
            return u;
        for (int i = LOG2[dep[u]]; i >= 0; i--)
        {
            if (fa[u][i] != fa[v][i])
            {
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        return fa[u][0];
    }

private:
    int root; // 需要初始化根在哪
    int siz = 0;
    int lca_tag = 0, lca_itag = 0;
    vector<vector<int>> edge;
    vector<int> dep;
    vector<vector<int>> fa;
    vector<ll> LOG2;
    int init_tag = 0;
    void dfs(int now, int father, int depth)
    {
        dep[now] = depth;
        for (auto i : edge[now])
        {
            if (i == father)
                continue;
            fa[i][0] = now;
            dfs(i, now, depth + 1);
        }
    }
    void init()
    {
        init_tag = 1;
        dfs(root, -1, 1);
        for (int j = 1; j < 30; j++)
            for (int i = 1; i <= siz; i++)
            {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
            }
    }
};
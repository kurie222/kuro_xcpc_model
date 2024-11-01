int root; // 需要初始化根在哪
int lca_tag = 0, lca_itag = 0;
vector<int> edge[maxn];
int dfn[maxn];
int fa[maxn][30];
int LOG2[maxn];
void lca_init()
{
    if (lca_itag)
        return;
    lca_itag = 1;
    LOG2[0] = -1;
    for (int i = 1; i < maxn; i++)
        LOG2[i] = LOG2[i / 2] + 1;
}
void dfs(int now, int father)
{
    assert(root != 0);
    if (!lca_itag)
        lca_init();
    lca_tag = 1;
    fa[now][0] = father;
    dfn[now] = dfn[father] + 1;
    for (int i = 1; i <= LOG2[dfn[now]]; i++)
    {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    }
    for (auto i : edge[now])
        if (i != father)
            dfs(i, now);
}
int lca(int u, int v)
{
    if (!lca_tag)
        dfs(root, 0);
    if (dfn[u] > dfn[v])
        return lca(v, u);
    while (dfn[u] != dfn[v])
    {
        v = fa[v][(int)LOG2[dfn[v] - dfn[u]]];
    }
    if (u == v)
        return u;
    for (int i = LOG2[dfn[u]]; i >= 0; i--)
    {
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
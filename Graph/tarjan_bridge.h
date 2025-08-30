// 复制自oi-wiki
vector<int> low(n + 1), dfn(n + 1);
int idx = 0;
vector<int> isbridge(m + 1);
vector<int> edge(n + 1);
int cnt_bridge = 0;
vector<int> father(n + 1);

auto tarjan = [&](this auto &&self, int u, int fa) -> void
{
    father[u] = fa;
    low[u] = dfn[u] = ++idx;
    for (auto [v, b] : edge[u])
    {
        if (!dfn[v])
        {
            self(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
            {
                isbridge[b] = true;
                ++cnt_bridge;
            }
        }
        else if (v != fa)
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
};
tarjan(1, 0);
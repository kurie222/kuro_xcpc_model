// 注意：两个版本只是欧拉路径，想找欧拉回路：
// 有向图版本：把判非法改成要求所有点出度入度相等
// 无向图版本：把判非法改成要求所有点的度数都是偶数
class orderedPath
{
public:
    orderedPath(int nn, int mm) : n(nn), m(mm)
    {
        edge.resize(n + 1);
        edge2.resize(n + 1);
        vis.resize(m + 1);
        ansEdge.resize(m + 1);
        ansNode.resize(m + 1);
        in.resize(n + 1);
        out.resize(n + 1);
    }
    void addEdge(int u, int v)
    {
        edge[u].push_back({v, idx});
        edge2[u].push_back({v});
        edge2[v].push_back({u});
        idx++;
        in[v]++;
        out[u]++;
    }
    bool solve()
    {
        int idx1 = m;
        vector<int> vist(n + 1);
        auto dfs1 = [&](auto &&self, int now, int fa) -> void
        {
            if (vist[now])
                return;
            vist[now] = 1;
            for (auto i : edge2[now])
            {
                if (i == fa)
                    continue;
                self(self, i, now);
            }
        };
        int s = 0, t = 0;
        for (int i = 1; i <= n; i++)
        {
            if (in[i] == out[i] - 1)
            {
                if (!s)
                    s = i;
                else
                    return 0;
            }
            else if (in[i] - 1 == out[i])
            {
                if (!t)
                    t = i;
                else
                    return 0;
            }
            else if (in[i] != out[i])
            {
                return 0;
            }
        }
        if ((s && !t) || (!s && t))
            return 0;
        if (!s && !t)
            s = 1;
        dfs1(dfs1, s, -1);
        for (int i = 1; i <= n; i++)
        {
            if (!vist[i] && in[i] + out[i] > 0)
                return 0;
        }
        auto dfs = [&](auto &&self, int now, int e) -> void
        {
            while (edge[now].size())
            {
                auto [x, y] = edge[now].back();
                edge[now].pop_back();
                if (!vis[y])
                {
                    vis[y] = 1;
                    self(self, x, y);
                }
            }
            ansEdge[idx1] = e;
            ansNode[idx1] = now;
            idx1--;
        };
        dfs(dfs, s, 0);
        return 1;
    }
    vector<int> ansEdge, ansNode;

private:
    vector<vector<p2>> edge;
    vector<vector<int>> edge2;
    vector<int> vis;
    vector<int> in, out;
    int idx = 1;
    int n, m;
};
class unorderedPath
{
public:
    unorderedPath(int nn, int mm) : n(nn), m(mm)
    {
        edge.resize(n + 1);
        vis.resize(m + 1);
        ansEdge.resize(m + 1);
        ansNode.resize(m + 1);
    }
    void addEdge(int u, int v)
    {
        edge[u].push_back({v, idx});
        edge[v].push_back({u, idx});
        idx++;
    }
    bool solve()
    {
        int idx1 = m;
        vector<int> vist(n + 1);
        auto dfs1 = [&](auto &&self, int now, int fa) -> void
        {
            if (vist[now])
                return;
            vist[now] = 1;
            for (auto [i, j] : edge[now])
            {
                if (i == fa)
                    continue;
                self(self, i, now);
            }
        };
        int s = 0, t = 0;
        for (int i = 1; i <= n; i++)
        {
            if (edge[i].size() % 2 == 1)
            {
                if (!s)
                    s = i;
                else if (!t)
                    t = i;
                else
                    return 0;
            }
        }
        if (s && !t)
            return 0;
        if (!s && !t)
            s = 1;
        dfs1(dfs1, s, -1);
        for (int i = 1; i <= n; i++)
        {
            if (!vist[i])
                return 0;
        }
        auto dfs = [&](auto &&self, int now, int e) -> void
        {
            while (edge[now].size())
            {
                auto [x, y] = edge[now].back();
                edge[now].pop_back();
                if (!vis[y])
                {
                    vis[y] = 1;
                    self(self, x, y);
                }
            }
            ansEdge[idx1] = e;
            ansNode[idx1] = now;
            idx1--;
        };
        dfs(dfs, s, 0);
        return 1;
    }
    vector<int> ansEdge, ansNode;

private:
    vector<vector<p2>> edge;
    vector<int> vis;
    int idx = 1;
    int n, m;
};
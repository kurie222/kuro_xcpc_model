void dij()
{
    priority_queue<node> pq;
    pq.push(ori_node);
    while (pq.size())
    {
        auto tp = pq.top();
        pq.pop();
        for (auto v:u)
        {
            if (dis[u] + (len[v][u]) <dis[v])
            {
                dis[v]=len[v][u]+dis[u];
                pq.push(node(v));
            }
        }
    }
}
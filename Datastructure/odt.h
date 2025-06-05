//注意：如果值域是[1,n],你需要开成[1,n+1]!!!
using p3 = std::array<int, 3>;
struct Cht_tree
{
    set<p3> s;
    void init()
    {
        s.clear();
    }
    auto split(int x)
    {
        auto it = s.lower_bound({x, 0, 0});
        if (it != s.end() && (*it)[0] == x)
            return it;
        --it;
        auto [l, r, v] = *it;
        s.erase(it);
        s.insert({l, x - 1, v});
        return s.insert({x, r, v}).first;
    }
    void assign(int l, int r, int v)
    {
        auto itr = split(r + 1), itl = split(l);
        vector<p3> vi;
        while (itl != itr)
        {
            auto [x, y, z] = *itl;
            vi.push_back(*itl);
            itl++;
        }
        for (auto i : vi)
            s.erase(i);
        s.insert({l, r, v});
    }
    int find(int idx)
    {
        auto it = s.lower_bound(p3({idx, -1, 0}));
        if (it != s.end() && (*it)[0] == idx)
            rt(*it)[2];
        assert(it != s.begin());

        it--;
        rt(*it)[2];
    }
};
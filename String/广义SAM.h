struct Suffix_Automaton // 注意！广义SAM需要在每次插入新串前将last置为1！！！
{
    static const int N = 2000005, MAXS = 30;
    int tot = 1, ru[N], link[N], maxlen[N], endpos[N], ch[N][MAXS], last = 1;
    // endpos[x]: |endpos[x]| 即节点x的endpos大小
    Suffix_Automaton() { tot = 1; }
    void insert(int w)
    {
        if (ch[last][w])
        {
            int p = last, x = ch[p][w];
            if (maxlen[p] + 1 == maxlen[x])
            {
                endpos[x] = 1;
                last = x;
                return;
            }
            else
            {
                int y = ++tot;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < MAXS; ++i)
                    ch[y][i] = ch[x][i];
                while (p && ch[p][w] == x)
                    ch[p][w] = y, p = link[p];
                link[y] = link[x], link[x] = y;
                endpos[y] = 1;
                last = y;
                return;
            }
        }
        int z = ++tot, p = last;
        maxlen[z] = maxlen[last] + 1;
        while (p && !ch[p][w])
            ch[p][w] = z, p = link[p];
        if (!p)
            link[z] = 1;
        else
        {
            int x = ch[p][w];
            if (maxlen[p] + 1 == maxlen[x])
                link[z] = x;
            else
            {
                int y = ++tot;
                maxlen[y] = maxlen[p] + 1;
                for (int i = 0; i < 26; ++i)
                    ch[y][i] = ch[x][i];
                while (p && ch[p][w] == x)
                    ch[p][w] = y, p = link[p];
                link[y] = link[x], link[z] = link[x] = y;
            }
        }
        endpos[z] = 1;
        last = z;
        return;
    }
    vector<int> p[N]; // 建立parent树，以便从上到下dfs
    void dfs(int u)
    {
        int v;
        for (int i = 0; i < p[u].size(); i++)
        {
            v = p[u][i];
            dfs(v);
            endpos[u] += endpos[v];
        }
    }
    void clear()
    {
        for (int i = 1; i <= tot; i++)
        {
            ru[i] = link[i] = maxlen[i] =endpos[i]= 0;
            for (int j = 0; j < MAXS; j++)
                ch[i][j] = 0;
        }
        tot = last = 1;
    }
    // 注意！在使用该方法前，endpos[]代表每个点作为“终结点”的次数
    // 使用该方法后，endpos[]指在串中出现总次数，即原数组的子树求和
    void get_endpos()
    {
        for (int i = 1; i <= tot; i++)
            p[i].clear();
        for (int i = 2; i <= tot; i++)
        {
            p[link[i]].push_back(i); // 建立parent树，以便从上到下dfs
        }
        dfs(1);
        for (int i = 1; i <= tot; i++)
            p[i].clear();
    }
    /*
    下面是原版广义SAM的get_endpos(),常数是上面的vector版的1/2,但本人不太会这个版本。
    */
    //  queue<int> Q;
    //  void get_endpos()
    //  {
    //      for (int i = 2; i <= tot; ++i)
    //          ++ru[link[i]];
    //      for (int i = 1; i <= tot; ++i)
    //          if (!ru[i])
    //              Q.push(i);
    //      while (!Q.empty())
    //      {
    //          int x = Q.front();
    //          Q.pop();
    //          endpos[link[x]] += endpos[x];
    //          if (!(--ru[link[x]]))
    //              Q.push(link[x]);
    //      }
    //  }
} sam;
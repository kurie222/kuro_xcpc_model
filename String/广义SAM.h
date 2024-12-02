struct Suffix_Automaton
{
    static const int N = 2000005, MAXS = 30;
    int tot = 1, ru[N], link[N], maxlen[N], endpos[N], ch[N][MAXS], last = 1;
    queue<int> Q;
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
                last=x;
                return ;
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
                last=y;
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
        last=z;
        return;
    }
    void get_endpos()
    {
        for (int i = 2; i <= tot; ++i)
            ++ru[link[i]];
        for (int i = 1; i <= tot; ++i)
            if (!ru[i])
                Q.push(i);
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            endpos[link[x]] += endpos[x];
            if (!(--ru[link[x]]))
                Q.push(link[x]);
        }
    }
} sam;
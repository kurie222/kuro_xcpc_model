struct SUBM
{
    // 1-idx
    static const int maxn = 2050, maxs = 26;
    int ch[maxn][maxs], la[maxs];
    int idx = maxn;
    void clear()
    {
        memset(la, 0, sizeof la);
        for (int i = 1; i < idx; i++)
            for (int j = 0; j < maxs; j++)
            {
                ch[i][j] = 0;
            }
        idx=1;
    }
    void clear(int n)
    {
        memset(la, 0, sizeof la);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < maxs; j++)
            {
                ch[i][j] = 0;
            }
        idx=1;
    }
    void init(string &s)
    {
        clear(s.size()+10);
        for (int i = s.size(); i >= 2; i--)
        {
            for (int j = 0; j < maxs; j++)
            {
                ch[i][j] = la[j];
            }
            la[s[i - 1] - 'a'] = i;
        }
        for (int j = 0; j < maxs; j++)
        {
            ch[1][j] = la[j];
        }
        idx = s.size() + 3;
    }
    void init(vector<int> &a)
    {
        clear(s.size()+10);
        for (int i = a.size(); i >= 2; i--)
        {
            for (int j = 0; j < maxs; j++)
            {
                ch[i][j] = la[j];
            }
            la[a[i - 1]] = i;
        }
        for (int j = 0; j < maxs; j++)
        {
            ch[1][j] = la[j];
        }
        idx = a.size() + 3;
    }
}
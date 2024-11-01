int LOG2[maxn];
int st_table_init_tag = 0;
vector<int> a(maxn);
int st_table[maxn][30];
template <typename T>
T op(T a, T b)
{
    return std::max(a, b);
}
void st_table_init()
{

    LOG2[0] = 0;
    for (int i = 1; i <= maxn; i++)
        LOG2[i] = log2(i);
    st_table_init_tag = 1;
}
void build()
{
    if (!st_table_init_tag)
        st_table_init();
    for(int i=0;i<=n;i++)
    st_table[i][0]=a[i];
    for (int j = 1; j <= LOG2[n]; j++)
        for (int i = 1; i + (1 << (j - 1)) <= n + 1; i++)
        {
            st_table[i][j] = op(st_table[i][j - 1], st_table[i + (1 << (j - 1))][j - 1]);
            // op[i,i+2^j-1]
        }
}
int srh(int l, int r)
{
    if (l == r)
        return st_table[l][0];
    int tp = (LOG2[r - l + 1]);
    return op(st_table[l][tp], st_table[r + 1 - (1 << tp)][tp]);
}
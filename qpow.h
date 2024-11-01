template <typename T>
T qpow(T a, T b, long long p)
{
    int res = 1;
    for (; b; b /= 2, a = (1ll * a * a) % p)
    {
        if (b % 2)
        {
            res = 1LL * res * a % p;
        }
    }
    return res;
}
template <typename T>
T qpow(T a, T b)
{
    int res = 1;
    for (; b; b /= 2, a = (1ll * a * a))
    {
        if (b % 2)
        {
            res = 1LL * res * a;
        }
    }
    return res;
}

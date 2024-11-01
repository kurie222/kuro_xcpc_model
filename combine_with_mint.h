template <class T>
constexpr T qpow(T a, long long b)
{
    T res = 1;
    for (; b; b /= 2, a *= a)
    {
        if (b % 2)
        {
            res *= a;
        }
    }
    return res;
}

constexpr long long mul(long long a, long long b, long long p)
{
    long long res = a * b - ((long long)(1.L * a * b / p) * p);
    res %= p;
    if (res < 0)
    {
        res += p;
    }
    return res;
}
template <long long P>
struct modint
{
    long long x;
    constexpr modint() : x{} {}
    constexpr modint(long long x) : x{norm(x % getMod())} {}

    static long long Mod;
    constexpr static long long getMod()
    {
        if (P > 0)
        {
            return P;
        }
        else
        {
            return Mod;
        }
    }
    constexpr static void setMod(long long Mod_)
    {
        Mod = Mod_;
    }
    constexpr long long norm(long long x) const
    {
        if (x < 0)
        {
            x += getMod();
        }
        if (x >= getMod())
        {
            x -= getMod();
        }
        return x;
    }
    constexpr long long val() const
    {
        return x;
    }
    explicit constexpr operator long long() const
    {
        return x;
    }
    constexpr modint operator-() const
    {
        modint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr modint inv() const
    {
        assert(x != 0);
        return qpow(*this, getMod() - 2);
    }
    constexpr modint &operator*=(modint rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr modint &operator+=(modint rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr modint &operator-=(modint rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr modint &operator/=(modint rhs) &
    {
        return *this *= rhs.inv();
    }
    friend constexpr modint operator*(modint lhs, modint rhs)
    {
        modint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr modint operator+(modint lhs, modint rhs)
    {
        modint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr modint operator-(modint lhs, modint rhs)
    {
        modint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr modint operator/(modint lhs, modint rhs)
    {
        modint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, modint &a)
    {
        long long v;
        is >> v;
        a = modint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const modint &a)
    {
        return os << a.val();
    }
    friend constexpr bool operator==(modint lhs, modint rhs)
    {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(modint lhs, modint rhs)
    {
        return lhs.val() != rhs.val();
    }
};
using mint = modint<maxi>;
using i64 = long long;
template<typename T>
struct Comb
{
    const int N;
    vector<T> fac, invfac;
    Comb(int n) : N(n), fac(n + 2), invfac(n + 2) { init(); };
    T inv(T x) { return qpow(x, mod - 2); };
    void init()
    {
        fac[0] = 1;
        for (int i = 1; i <= N; ++i)
            fac[i] = fac[i - 1] * i ;
        invfac[N] = inv(fac[N]);
        for (int i = N - 1; i >= 0; --i)
            invfac[i] = (invfac[i + 1] * (i + 1)) ;
    }
    T C(int n, int m)
    {
        if (n < m || m < 0)
            return 0;
        return fac[n] * invfac[m]  * invfac[n - m] ;
    }
    T A(int n, int m)
    {
        if (n < m || m < 0)
            return 0;
        return fac[n] * invfac[n - m] ;
    }
};
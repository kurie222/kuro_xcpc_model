template<class T>
constexpr T qpow(T a, long long b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr long long mul(long long a, long long b, long long p) {
    long long res = a * b - ((long long)(1.L * a * b / p) * p);
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<long long P>
struct modint {
    long long x;
    constexpr modint() : x{} {}
    constexpr modint(long long x) : x{norm(x % getMod())} {}
    
    static long long Mod;
    constexpr static long long getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(long long Mod_) {
        Mod = Mod_;
    }
    constexpr long long norm(long long x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr long long val() const {
        return x;
    }
    explicit constexpr operator long long() const {
        return x;
    }
    constexpr modint operator-() const {
        modint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr modint inv() const {
        assert(x != 0);
        return qpow(*this, getMod() - 2);
    }
    constexpr modint &operator*=(modint rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr modint &operator+=(modint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr modint &operator-=(modint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr modint &operator/=(modint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr modint operator*(modint lhs, modint rhs) {
        modint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr modint operator+(modint lhs, modint rhs) {
        modint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr modint operator-(modint lhs, modint rhs) {
        modint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr modint operator/(modint lhs, modint rhs) {
        modint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, modint &a) {
        long long v;
        is >> v;
        a = modint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const modint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(modint lhs, modint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(modint lhs, modint rhs) {
        return lhs.val() != rhs.val();
    }
};
using mint=modint<998244353>;
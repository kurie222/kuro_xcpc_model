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
template<long long P>
struct modint {
    long long x;
    constexpr modint() : x{} {}
    constexpr modint(long long x) : x{norm(x % getMod())} {}
    
    inline static long long Mod=998244353;
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
        x = x*rhs.x;
        x%=getMod();
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
//如果需要使用setmod，传0进入模版即可
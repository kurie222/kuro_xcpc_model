using i64 = long long;
const int mod = 1e9 + 7;
struct Comb {
    const int N;
    vector<i64> fac, invfac;
    Comb(int n) : N(n), fac(n + 2), invfac(n + 2) { init(); };
    i64 qpow(i64 x, i64 p) {
        i64 res = 1 % mod; x %= mod;
        for (; p; p >>= 1, x = x * x % mod)
            if (p & 1) res = res * x % mod;
        return res;
    }
    i64 inv(i64 x) { return qpow(x, mod - 2); };
    void init() {
        fac[0] = 1;
        for (int i = 1; i <= N; ++i) fac[i] = fac[i - 1] * i % mod;
        invfac[N] = inv(fac[N]);
        for (int i = N - 1; i >= 0; --i) invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
    i64 C(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    }
    i64 A(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac[n] * invfac[n - m] % mod;
    }
};
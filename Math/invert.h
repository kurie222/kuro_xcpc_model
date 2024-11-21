const int p = 998244353;
int m[maxn];
int mod(int a,int p)
{
    return (a%p+p)%p;
}
int inv(int n,int p)
{
    if(m[n])
        return m[n];
    m[n]=mod(-p/n*inv(p%n,p),p);
    return m[n];

}
//线性需要for(i-n)
void exgcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
int inv2(int a, int n) {
    int x, y;
    exgcd(a, n, x, y);    
    x = (x % n + n) % n;   
    return x;
}
//ax==1 (mod b)
//gcd(a,n)=1
//ax+by=1
template <typename T,typename T2>
T qpow(T base, T power, T2 mod)
{
    T temp = 1;
    while (power!=1)
    {
        if (power & 1)
        {
            temp *= base;
            temp %= mod;
            power--;
            continue;
        }
        base *= base;
        base %= mod;
        power >>= 1;
    }
    return (base * temp) % mod;
}
int inv3(int a,int p)
{
  return qpow(a,p-2,p);
}
//x==a^(p-2) (mod p)
//p is prime
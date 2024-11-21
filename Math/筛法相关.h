// 线性筛求欧拉函数
vector<int> pri;
bool not_prime[N];
int phi[N];

void pre(int n)
{
  phi[1] = 1;
  for (int i = 2; i <= n; i++)
  {
    if (!not_prime[i])
    {
      pri.push_back(i);
      phi[i] = i - 1;
    }
    for (int pri_j : pri)
    {
      if (i * pri_j > n)
        break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0)
      {
        phi[i * pri_j] = phi[i] * pri_j;
        break;
      }
      phi[i * pri_j] = phi[i] * phi[pri_j];
    }
  }
}
// 筛法求莫比乌斯函数
vector<int> pri;
bool not_prime[N];
int mu[N];

void pre(int n)
{
  mu[1] = 1;
  for (int i = 2; i <= n; ++i)
  {
    if (!not_prime[i])
    {
      mu[i] = -1;
      pri.push_back(i);
    }
    for (int pri_j : pri)
    {
      if (i * pri_j > n)
        break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0)
      {
        mu[i * pri_j] = 0;
        break;
      }
      mu[i * pri_j] = -mu[i];
    }
  }
}
// 筛法求因数个数
vector<int> pri;
bool not_prime[N];
int d[N], num[N];

void pre(int n)
{
  d[1] = 1;
  for (int i = 2; i <= n; ++i)
  {
    if (!not_prime[i])
    {
      pri.push_back(i);
      d[i] = 2;
      num[i] = 1;
    }
    for (int pri_j : pri)
    {
      if (i * pri_j > n)
        break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0)
      {
        num[i * pri_j] = num[i] + 1;
        d[i * pri_j] = d[i] / num[i * pri_j] * (num[i * pri_j] + 1);
        break;
      }
      num[i * pri_j] = 1;
      d[i * pri_j] = d[i] * 2;
    }
  }
}
// 因数个数前缀和 n<2^63(SP26073)
// O(n^(1/3)logn)
void myw(lll x)
{
  if (!x)
    return;
  myw(x / 10);
  printf("%d", (int)(x % 10));
}

struct vec
{
  ll x, y;
  vec(ll x0 = 0, ll y0 = 0) { x = x0, y = y0; }
  vec operator+(const vec b) { return vec(x + b.x, y + b.y); }
};

ll N;
vec stk[1000005];
int len;
vec P;
vec L, R;

bool ninR(vec a) { return N < (lll)a.x * a.y; }
bool steep(ll x, vec a) { return (lll)N * a.x <= (lll)x * x * a.y; }

lll Solve()
{
  len = 0;
  ll cbr = cbrt(N), sqr = sqrt(N);
  P.x = N / sqr, P.y = sqr + 1;
  lll ans = 0;
  stk[++len] = vec(1, 0);
  stk[++len] = vec(1, 1);
  while (1)
  {
    L = stk[len--];
    while (ninR(vec(P.x + L.x, P.y - L.y)))
      ans += (lll)P.x * L.y + (lll)(L.y + 1) * (L.x - 1) / 2,
          P.x += L.x, P.y -= L.y;
    if (P.y <= cbr)
      break;
    R = stk[len];
    while (!ninR(vec(P.x + R.x, P.y - R.y)))
      L = R, R = stk[--len];
    while (1)
    {
      vec mid = L + R;
      if (ninR(vec(P.x + mid.x, P.y - mid.y)))
        R = stk[++len] = mid;
      else if (steep(P.x + mid.x, R))
        break;
      else
        L = mid;
    }
  }
  for (int i = 1; i < P.y; i++)
    ans += N / i;
  return ans * 2 - sqr * sqr;
}

int T;

int main()
{
  scanf("%d", &T);
  while (T--)
  {
    scanf("%lld", &N);
    myw(Solve());
    printf("\n");
  }
}
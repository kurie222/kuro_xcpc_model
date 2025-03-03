vector<int> pri;
vector<int> not_prime(maxn);
vector<int> minfac(maxn);
void pre(int n)
{
  not_prime[1] = 1;
  for (int i = 2; i <= n; ++i)
  {
    if (!not_prime[i])
    {
      pri.push_back(i);
    }
    for (int pri_j : pri)
    {
      if (i * pri_j > n)
        break;
      not_prime[i * pri_j] = true;
      minfac[i * pri_j] = pri_j;
      if (i % pri_j == 0)
      {
        break;
      }
    }
  }
}

vector<int> prime;
bool is_prime[maxn];
void Eratosthenes(int n)
{
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; ++i)
  {
    is_prime[i] = true;
  }
  for (int i = 2; i <= n; ++i)
  {
    if (is_prime[i])
    {
      prime.push_back(i);
      if ((long long)i * i > n)
        continue;
      for (int j = i * i; j <= n; j += i)
      {
        is_prime[j] = false;
      }
    }
  }
}
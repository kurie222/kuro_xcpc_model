int gcd(int a, int b) {
  if(a<b) return gcd(b,a);
  while (b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}
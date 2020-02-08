bool odd(int n) { return n & 0x1; }
int half(int n) { return n >> 1; }

int mult_help(int r, int n, int a)
{
  while (true)
  {
    if (odd(n))
    {
      r = r + a;
      if (n == 1)
        return r;
    }
    n = half(n);
    a = a + a;
  }
}

int multiply(int n, int a)
{
  while (!odd(n))
  {
    a += a;
    n = half(n);
  }
  if (n == 1) return a;
  return mult_help(a, half(n - 1), a + a);
}
#include <functional>
#include <iostream>

#define Integer typename

template <Integer N>
bool odd(N n) { return bool(n & 0x1); }

template <Integer N>
int half(N n) { return n >> 1; }

template <typename A, typename N>
A mult_help(A r, N n, A a)
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

auto main() -> int
{
  std::cout << multiply(7, 8) << std::endl;
}
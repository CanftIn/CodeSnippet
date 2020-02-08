#include <functional>
#include <iostream>

#define NoncommutativeAdditiveMonoid typename
#define NoncommutativeAdditiveGroup typename
#define MultiplicativeSemigroup typename
#define MultiplicativeMonoid typename
#define Regular typename
#define SemigroupOperation typename
#define MonoidOperation typename
#define GroupOperation typename
#define AdditiveGroup typename
#define MultiplicativeGroup typename
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

template <Regular A, Integer N, SemigroupOperation Op>
A power_accumulate_semigroup(A r, A a, N n, Op op)
{
    if (n == 0) return r;
    while (true)
    {
        if (odd(n))
        {
            r = op(r, a);
            if (n == 1) return r;
        }
        n = half(n);
        a = op(a, a);
    }
}

template <Regular A, Integer N, SemigroupOperation Op>
A power_semigroup(A a, N n, Op op)
{
    while (!odd(n))
    {
        a = op(a, a);
        n = half(n);
    }
    if (n == 1) return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <NoncommutativeAdditiveMonoid T>
T identity_element(std::plus<T>)
{
    return T(0);
}

template <MultiplicativeMonoid T>
T identity_element(std::multiplies<T>)
{
    return T(1);
}

template <Regular A, Integer N, MonoidOperation Op>
A power_monoid(A a, N n, Op op)
{
    if (n == 0) return identity_element(op);
    return power_semigroup(a, n, op);
}

template <AdditiveGroup T>
std::negate<T> inverse_operation(std::plus<T>)
{
    return std::negate<T>();
}

template <MultiplicativeGroup T>
struct reciprocal
{
    T operator()(const T& x) const
    {
        return T(1) / x;
    }
};

template <MultiplicativeGroup T>
reciprocal<T> inverse_operation(std::multiplies<T>)
{
    return reciprocal<T>();
}

template <Regular A, Integer N, GroupOperation Op>
A power_group(A a, N n, Op op)
{
    if (n < 0)
    {
        n = -n;
        a = inverse_operation(op)(a); 
    }
    return power_monoid(a, n, op);
}

auto main() -> int
{
  std::plus<int> plus_int;

  std::cout << multiply(7, 8) << std::endl;
  std::cout << power_accumulate_semigroup(0, 7, 8, plus_int) << std::endl;
  std::cout << power_semigroup(7, 8, plus_int) << std::endl;
  std::cout << power_monoid(0, 8, plus_int) << std::endl;
  std::cout << power_group(7, -8, plus_int) << std::endl;
}
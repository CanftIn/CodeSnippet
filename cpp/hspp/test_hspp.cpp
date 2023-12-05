#include <cassert>
#include <optional>
#include <sstream>
#include <tuple>
#include <type_traits>

#include "hspp.h"

using namespace hspp;

auto expectTrue(bool x) {
  if (!x) {
    throw std::runtime_error{"False in expectedTrue!"};
  }
}

template <typename T, typename Enable = void>
struct IsPrintable : std::false_type {};

template <typename T>
struct IsPrintable<T, std::void_t<decltype(std::cout << std::declval<T>())>>
    : std::true_type {};

template <typename T>
constexpr bool isPrintableV = IsPrintable<std::decay_t<T>>::value;

template <typename T, typename U>
auto equal(T l, U r) -> std::enable_if_t<
    std::is_floating_point_v<T> || std::is_floating_point_v<U>, bool> {
  return (std::abs(l - r) < 0.005);
}

template <typename T, typename U>
auto equal(T l, U r) -> std::enable_if_t<
    !std::is_floating_point_v<T> && !std::is_floating_point_v<U>, bool> {
  return l == r;
}

template <typename T, typename U>
auto expectEq(T const& l, U const& r)
    -> std::enable_if_t<(isPrintableV<T> && isPrintableV<U>)> {
  if (!equal(l, r)) {
    std::stringstream ss;
    ss << l << " != " << r;
    throw std::runtime_error{ss.str()};
  }
}

template <typename T, typename U>
auto expectEq(T const& l, U const& r)
    -> std::enable_if_t<!(isPrintableV<T> && isPrintableV<U>)> {
  if (!equal(l, r)) {
    throw std::runtime_error{"Not equal. Types not printable"};
  }
}

// 测试 IsNullary 和 IsId
void testTypeTraits() {
  static_assert(doN::isNullaryV<doN::Nullary<int>>,
                "Nullary should be identified as nullary");
  static_assert(doN::isIdV<doN::Id<int>>, "Id should be identified as Id");
  static_assert(!doN::isNullaryV<int>,
                "int should not be identified as nullary");
}

void testOverload() {
  auto overloaded =
      overload([](int x) { return x * 2; }, [](double x) { return x + 0.5; },
               [](const std::string& s) { return s + " world"; });

  assert(overloaded(10) == 20);                  // 使用 int 参数
  assert(overloaded(2.5) == 3.0);                // 使用 double 参数
  assert(overloaded("hello") == "hello world");  // 使用 std::string 参数
}

// 测试 AddConstToPointer 和 StoreT
void testAddConstToPointer() {
  static_assert(std::is_same_v<impl::AddConstToPointerT<int*>, const int*>,
                "Should add const to pointer type");
  static_assert(std::is_same_v<impl::AddConstToPointerT<int>, int>,
                "Non-pointer type should remain unchanged");
}

// 测试 subtuple 和 takeTuple
void testSubtuple() {
  std::tuple<int, double, char> t = {1, 2.0, 'a'};
  auto sub = subtuple<1, 3>(t);
  static_assert(std::is_same_v<decltype(sub), std::tuple<double, char>>,
                "Subtuple type should be correct");

  auto taken = takeTuple<2>(t);
  static_assert(std::is_same_v<decltype(taken), std::tuple<int, double>>,
                "TakeTuple type should be correct");
}

// 测试 Maybe, Just, Nothing
void testMaybe() {
  data::Maybe<int> m1(10);
  data::Maybe<int> m2;
  assert(m1.hasValue() && "m1 should have a value");
  assert(!m2.hasValue() && "m2 should not have a value");

  data::Maybe<int> m3 = data::just(20);
  assert(m3.hasValue() && "m3 should have a value from Just");

  data::Maybe<int> m4 = data::nothing<int>;
  assert(!m4.hasValue() && "m4 should not have a value from Nothing");
}

void testToGFunc() {
  constexpr auto isAlphaNum = data::toGFunc<1> | [](auto x) -> bool {
    return std::isalnum(static_cast<unsigned char>(x));
  };

  expectEq(isAlphaNum | 'a', true);
  expectEq(isAlphaNum('a'), true);
}

using namespace hspp;
using namespace hspp::parser;
using namespace hspp::doN;
using namespace std::literals;

enum class Op { kADD, kSUB, kMUL, kDIV };

class OpFunc {
  Op mOp;

 public:
  constexpr OpFunc(Op op) : mOp{op} {}
  template <typename T>
  constexpr auto operator()(T x, T y) const {
    switch (mOp) {
      case Op::kADD:
        return x + y;
      case Op::kSUB:
        return x - y;
      case Op::kMUL:
        return x * y;
      case Op::kDIV:
        return x / y;
    }
    throw std::runtime_error{"Never reach here!"};
  }
};

namespace op {
constexpr auto add = toGFunc<2> | OpFunc{Op::kADD};
constexpr auto sub = toGFunc<2> | OpFunc{Op::kSUB};
constexpr auto mul = toGFunc<2> | OpFunc{Op::kMUL};
constexpr auto div = toGFunc<2> | OpFunc{Op::kDIV};

static_assert((add | 1 | 2) == 3);
static_assert((sub | 1 | 2) == -1);
static_assert((mul | 1 | 2) == 2);
static_assert((div | 4 | 2) == 2);

auto const addOp =
    do_(symb | "+", return_ | add)<alt> do_(symb | "-", return_ | sub);
auto const mulOp =
    do_(symb | "*", return_ | mul)<alt> do_(symb | "/", return_ | div);
}  // namespace op

using op::addOp;
using op::mulOp;

constexpr auto isDigit = toFunc<> | [](char x) { return isdigit(x); };

Id<char> x;
auto const digit = do_(x <= (token || sat | isDigit), return_ | (x - '0'));

extern TEParser<int> const expr;

Id<int> n;
auto const factor =
    digit<alt> do_(symb | "("s, n <= expr, symb | ")"s, return_ | n);

auto const term = factor<chainl1> mulOp;

TEParser<int> const expr = toTEParser || (term<chainl1> addOp);

int test_parser() {
  {
    auto const rawResult = apply || many | digit || " 1  2 34";
    auto const& result = std::get<0>(rawResult.at(0));
    auto const expected = std::vector{1, 2, 3, 4};
    expectTrue(std::equal(result.begin(), result.end(), expected.begin()));
  }

  {
    auto const result = apply || addOp || " +  * /-";
    expectEq(std::get<0>(result.at(0)) | 1 | 2, 3);

    auto const result2 = apply || mulOp || "   * /-";
    expectEq(std::get<0>(result2.at(0)) | 1 | 2, 2);
  }

  {
    auto const p = digit<chainl1> addOp;
    auto const result = runParser | p | "1 + 2";
    auto const expected = 3;
    expectEq(std::get<0>(result.at(0)), expected);
  }

  {
    auto const result = apply | expr | "1 - 2 * 3 + 4";
    auto const expected = -1;
    expectEq(std::get<0>(result.at(0)), expected);
  }
  return 0;
}

int main() {
  testTypeTraits();
  testOverload();
  testAddConstToPointer();
  testSubtuple();
  testMaybe();
  testToGFunc();
  test_parser();
  return 0;
}

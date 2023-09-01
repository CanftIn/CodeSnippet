#ifndef JSONRPC_UTILS_HPP
#define JSONRPC_UTILS_HPP

#include <string>
#include <string_view>
#include <variant>

namespace jsonrpc {

///-----------------------------------------------------------------------------
/// Arg
class Arg {
 public:
  template <typename T>
  struct with_value {
    std::string name;
    T value;
  };

  explicit constexpr Arg(std::string_view name) : name_(name) {}

  std::string_view name() const { return name_; }

  template <typename T>
  constexpr with_value<T> operator=(T&& value) {
    return {std::string(name_), std::forward<T>(value)};
  }

 private:
  std::string_view name_;
};

template <typename T>
struct is_arg_impl : std::false_type {};

template <typename T>
struct is_arg_impl<Arg::with_value<T>> : std::true_type {};

template <typename T>
struct is_arg : is_arg_impl<std::decay_t<T>> {};

template <typename T>
constexpr bool is_arg_v = is_arg<T>::value;

namespace arg_literals {

constexpr Arg operator"" _arg(const char* str, std::size_t) { return Arg{str}; }

}  // namespace arg_literals

///-----------------------------------------------------------------------------
/// Expect
namespace internal {

template <typename Error>
struct Unexpected {
 public:
  explicit constexpr Unexpected(Error error) : error_(std::move(error)) {}

  Error& error() { return error_; }

 private:
  Error error_;
};

template <typename T, typename Error>
class Expected {
 public:
  template <typename G>
  Expected(Unexpected<G> unexpected)
      : data_(Error(std::move(unexpected.error()))) {}

  Expected(T value) : data_(std::move(value)) {}

  Error& error() { return std::get<Error>(data_); }
  T& value() { return std::get<T>(data_); }

  explicit operator bool() const { return std::holds_alternative<T>(data_); }
  T& operator*() { return value(); }
  T* operator->() { return &value(); }

 private:
  std::variant<T, Error> data_;
};

}  // namespace internal

}  // namespace jsonrpc

#endif  // JSONRPC_UTILS_HPP
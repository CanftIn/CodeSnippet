#ifndef JSONRPC_UTILS_HPP
#define JSONRPC_UTILS_HPP

#include <string>
#include <string_view>
#include <variant>
#include <optional>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <vector>

#include <boost/asio.hpp>

#define PACKIO_TRACE(...) (void)0
#define PACKIO_DEBUG(...) (void)0
#define PACKIO_INFO(...) (void)0
#define PACKIO_WARN(...) (void)0
#define PACKIO_ERROR(...) (void)0

namespace jsonrpc {

namespace internal {

template <typename, typename = void>
struct func_traits : std::false_type {
};

template <typename T>
struct func_traits<T, std::void_t<decltype(&std::decay_t<T>::operator())>>
    : func_traits<decltype(&std::decay_t<T>::operator())> {
};

template <typename C, typename R, typename... Args>
struct func_traits<R (C::*)(Args...)> : func_traits<R (*)(Args...)> {
};

template <typename C, typename R, typename... Args>
struct func_traits<R (C::*)(Args...) const> : func_traits<R (*)(Args...)> {
};

template <typename R, typename... Args>
struct func_traits<R (*)(Args...)> : std::true_type {
    using result_type = R;
    using args_type = std::tuple<Args...>;
    static constexpr auto args_count = std::tuple_size_v<args_type>;
};

template <typename T>
constexpr bool func_traits_v = func_traits<T>::value;

template <typename>
struct is_awaitable : std::false_type {
};

#if defined(PACKIO_HAS_CO_AWAIT)
template <typename... Args>
struct is_awaitable<net::awaitable<Args...>> : std::true_type {
};
#endif // defined(PACKIO_HAS_CO_AWAIT)

template <typename, typename = void>
struct is_coroutine : std::false_type {
};

template <typename T>
struct is_coroutine<T, std::enable_if_t<func_traits_v<T>>>
    : is_awaitable<typename func_traits<T>::result_type> {
};

template <typename T>
constexpr bool is_coroutine_v = is_coroutine<T>::value;

template <typename T, typename = void>
struct is_tuple : std::false_type {
};

template <typename T>
struct is_tuple<T, std::void_t<decltype(std::tuple_size<std::decay_t<T>>::value)>>
    : std::true_type {
};

template <typename T>
constexpr auto is_tuple_v = is_tuple<T>::value;

template <typename T>
struct left_shift_tuple;

template <typename A, typename... Bs>
struct left_shift_tuple<std::tuple<A, Bs...>> {
    using type = std::tuple<Bs...>;
};

template <typename T>
using left_shift_tuple_t = typename left_shift_tuple<T>::type;

template <template <typename...> class Map, typename T>
struct map_tuple;

template <template <typename...> class Map, typename... Args>
struct map_tuple<Map, std::tuple<Args...>> {
    using type = std::tuple<Map<Args>...>;
};

template <template <typename...> class Map, typename T>
using map_tuple_t = typename map_tuple<Map, T>::type;

template <typename T>
using decay_tuple_t = map_tuple_t<std::decay_t, T>;

template <typename... Args>
struct always_false : std::false_type {
};

template <typename... Args>
constexpr auto always_false_v = always_false<Args...>::value;

template <typename T>
void set_no_delay(T&)
{
}

template <>
inline void set_no_delay(boost::asio::ip::tcp::socket& socket)
{
    boost::system::error_code ec;
    socket.set_option(boost::asio::ip::tcp::no_delay{true}, ec);
    if (ec) {
        PACKIO_WARN("error setting tcp nodelay option: {}", ec.message());
    }
}

template <typename T>
std::unique_ptr<std::decay_t<T>> to_unique_ptr(T&& value)
{
    return std::make_unique<std::decay_t<T>>(std::forward<T>(value));
}

template <typename Executor, typename Obj>
auto bind_executor(Executor&& executor, Obj&& obj)
{
    return boost::asio::bind_executor(
        boost::asio::any_io_executor(std::forward<Executor>(executor)),
        std::forward<Obj>(obj));
}

} // internal

///-----------------------------------------------------------------------------
/// Arg
class arg {
 public:
  template <typename T>
  struct with_value {
    std::string name;
    T value;
  };

  explicit constexpr arg(std::string_view name) : name_(name) {}

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
struct is_arg_impl<arg::with_value<T>> : std::true_type {};

template <typename T>
struct is_arg : is_arg_impl<std::decay_t<T>> {};

template <typename T>
constexpr bool is_arg_v = is_arg<T>::value;

namespace arg_literals {

constexpr arg operator"" _arg(const char* str, std::size_t) { return arg{str}; }

}  // namespace arg_literals

///-----------------------------------------------------------------------------
/// handler

//! The completion_handler class
//! @tparam Rpc RPC protocol implementation
//!
//! First argument of @ref traits::AsyncProcedure "AsyncProcedure", the
//! completion_handler is a callable used to notify the completion of an
//! asynchronous procedure. You must only call @ref set_value or
//! @ref set_error once.
template <typename Rpc>
class completion_handler {
public:
    using id_type = typename Rpc::id_type;
    using response_buffer_type =
        decltype(Rpc::serialize_response(std::declval<id_type>()));
    using function_type = std::function<void(response_buffer_type&&)>;

    template <typename F>
    completion_handler(const id_type& id, F&& handler)
        : id_(id), handler_(std::forward<F>(handler))
    {
    }

    //! The destructor will notify an error if the completion_handler has not been used
    ~completion_handler()
    {
        if (handler_) {
            set_error("call finished with no result");
        }
    }

    completion_handler(const completion_handler&) = delete;
    completion_handler& operator=(const completion_handler&) = delete;

    //! Move constructor
    completion_handler(completion_handler&& other)
        : id_(other.id_), handler_(std::move(other.handler_))
    {
        other.handler_ = nullptr;
    }

    //! Move assignment operator
    completion_handler& operator=(completion_handler&& other)
    {
        if (handler_) {
            set_error("call finished with no result");
        }
        id_ = other.id_;
        handler_ = std::move(other.handler_);
        other.handler_ = nullptr;
        return *this;
    }

    //! Notify successful completion of the procedure and set the return value
    //! @param return_value The value that the procedure will return to the client
    template <typename T>
    void set_value(T&& return_value)
    {
        complete(Rpc::serialize_response(id_, std::forward<T>(return_value)));
    }

    //! @overload
    void set_value() { complete(Rpc::serialize_response(id_)); }

    //! Notify erroneous completion of the procedure with an associated error
    //! @param error_value Error value
    template <typename T>
    void set_error(T&& error_value)
    {
        complete(Rpc::serialize_error_response(id_, std::forward<T>(error_value)));
    }

    //! @overload
    void set_error()
    {
        complete(Rpc::serialize_error_response(id_, "unknown error"));
    }

    //! Same as @ref set_value
    template <typename T>
    void operator()(T&& return_value)
    {
        set_value(std::forward<T>(return_value));
    }

    //! Same as @ref set_value
    void operator()() { set_value(); }

private:
    void complete(response_buffer_type&& buffer)
    {
        handler_(std::move(buffer));
        handler_ = nullptr;
    }

    id_type id_;
    function_type handler_;
};

template <typename>
struct is_completion_handler : std::false_type {
};

template <typename T>
struct is_completion_handler<completion_handler<T>> : std::true_type {
};

template <typename T>
constexpr auto is_completion_handler_v = is_completion_handler<T>::value;

template <typename...>
struct is_async_procedure_args;

template <>
struct is_async_procedure_args<std::tuple<>> : std::false_type {
};

template <typename T0, typename... Ts>
struct is_async_procedure_args<std::tuple<T0, Ts...>>
    : is_completion_handler<T0> {
};

template <typename F>
struct is_async_procedure
    : is_async_procedure_args<typename internal::func_traits<F>::args_type> {
};

template <typename T>
constexpr auto is_async_procedure_v = is_async_procedure<T>::value;


///-----------------------------------------------------------------------------
/// Expect
namespace internal {

template <typename Error>
struct unexpected {
 public:
  explicit constexpr unexpected(Error error) : error_(std::move(error)) {}

  Error& error() { return error_; }

 private:
  Error error_;
};

template <typename T, typename Error>
class expected {
 public:
  template <typename G>
  expected(unexpected<G> unexpected)
      : data_(Error(std::move(unexpected.error()))) {}

  expected(T value) : data_(std::move(value)) {}

  Error& error() { return std::get<Error>(data_); }
  T& value() { return std::get<T>(data_); }

  explicit operator bool() const { return std::holds_alternative<T>(data_); }
  T& operator*() { return value(); }
  T* operator->() { return &value(); }

 private:
  std::variant<T, Error> data_;
};

}  // namespace internal

///-----------------------------------------------------------------------------
/// args_spec
namespace internal {

template <typename DefaultType>
class arg_spec {
public:
    explicit arg_spec(std::string name) : name_(std::move(name)) {}
    explicit arg_spec(const arg& arg) : name_(arg.name()) {}
    explicit arg_spec(arg::with_value<DefaultType> arg)
        : name_(std::move(arg.name)), default_value_(std::move(arg.value))
    {
    }

    const std::string& name() const { return name_; }
    const std::optional<DefaultType>& default_value() const
    {
        return default_value_;
    }

private:
    std::string name_;
    std::optional<DefaultType> default_value_;
};

template <typename F>
using arg_specs_tuple_for_sync_procedure_t =
    map_tuple_t<arg_spec, decay_tuple_t<typename func_traits<F>::args_type>>;

template <typename F>
using arg_specs_tuple_for_async_procedure_t =
    left_shift_tuple_t<arg_specs_tuple_for_sync_procedure_t<F>>;

template <typename, bool>
struct arg_specs_tuple_for;

template <typename F>
struct arg_specs_tuple_for<F, true> {
    using type = arg_specs_tuple_for_async_procedure_t<F>;
};

template <typename F>
struct arg_specs_tuple_for<F, false> {
    using type = arg_specs_tuple_for_sync_procedure_t<F>;
};

template <typename F>
using arg_specs_tuple_for_t =
    typename arg_specs_tuple_for<F, is_async_procedure_v<F>>::type;

template <typename T>
struct args_specs_maker;

template <typename... Specs>
struct args_specs_maker<std::tuple<Specs...>> {
    template <typename... Args>
    static std::tuple<Specs...> make(Args&&... args)
    {
        if constexpr (sizeof...(Args) == 0) {
            // default arg specs are arguments called "0", "1", ... and no default value
            return iota(std::make_index_sequence<sizeof...(Specs)>());
        }
        else {
            static_assert(
                sizeof...(Args) == sizeof...(Specs),
                "arguments specification must either match the number of "
                "arguments or be empty");
            return {Specs{std::forward<Args>(args)}...};
        }
    }

    template <std::size_t... Idxs>
    static std::tuple<Specs...> iota(std::index_sequence<Idxs...>)
    {
        return {Specs{std::to_string(Idxs)}...};
    }
};

//! Options available for the argument specifications
//!
//! You are never expected to construct this structure yourself
//! but rather construct them by combining options such as
//! @ref packio::allow_extra_arguments "allow_extra_arguments"
//! with operator|
struct args_specs_options {
    bool allow_extra_arguments = false;

    constexpr args_specs_options operator|(const args_specs_options& other)
    {
        auto ret = *this;
        ret.allow_extra_arguments |= other.allow_extra_arguments;
        return ret;
    }
};

template <typename SpecsTuple>
class args_specs {
public:
    args_specs() : args_specs(args_specs_options{}){};

    template <
        typename T,
        typename... Args,
        typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, args_specs_options>>>
    args_specs(T&& arg0, Args&&... args)
        : args_specs(
            args_specs_options{},
            std::forward<T>(arg0),
            std::forward<Args>(args)...)
    {
    }

    template <typename... Args>
    args_specs(args_specs_options opts, Args&&... args)
        : specs_{args_specs_maker<SpecsTuple>::make(std::forward<Args>(args)...)},
          opts_{std::move(opts)}
    {
    }

    constexpr const args_specs_options& options() const { return opts_; }

    template <std::size_t I>
    constexpr decltype(auto) get() const
    {
        return std::get<I>(specs_);
    }

    static constexpr std::size_t size()
    {
        return std::tuple_size_v<SpecsTuple>;
    }

private:
    SpecsTuple specs_;
    args_specs_options opts_{};
};
} // internal

//! Procedure arguments specifications
//! @tparam The procedure
//!
//! CLass that describes the arguments of the procedure
//! They each have a name and optionally a default value
//! This is a tuple-like class where each element can be
//! constructured from:
//! - a string, defining the name of the argument
//! - a @ref arg, defining the name of the argument
//! - a @ref arg::with_value, defining the name of the argyment
//!   and its default value
//! Optionally, accepts
//! @ref packio::internal::args_specs_options "args_specs_options"
//! as first argument to customize the behavior of argument handling
template <typename Procedure>
class args_specs
    // Using the real implementation as the base class reduces
    // the number of templates instanciation
    : public internal::args_specs<internal::arg_specs_tuple_for_t<Procedure>> {
public:
    using base = internal::args_specs<internal::arg_specs_tuple_for_t<Procedure>>;
    using base::base;
};

//! Option to allo extra arguments, ignoring them
constexpr auto allow_extra_arguments = internal::args_specs_options{true};
}  // namespace jsonrpc

#endif  // JSONRPC_UTILS_HPP
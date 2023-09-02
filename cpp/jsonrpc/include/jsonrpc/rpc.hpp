#ifndef JSONRPC_RPC_HPP
#define JSONRPC_RPC_HPP

#include <array>
#include <optional>

#include "jsonrpc/call_type.hpp"
#include "jsonrpc/incremental_buffers.hpp"
#include "jsonrpc/json.hpp"
#include "jsonrpc/utils.hpp"

namespace jsonrpc {

namespace internal {

template <typename... Args>
constexpr bool positional_args_v = (!is_arg_v<Args> && ...);

template <typename... Args>
constexpr bool named_args_v = sizeof...(Args) > 0 && (is_arg_v<Args> && ...);

using id_type = nlohmann::json;
using native_type = nlohmann::json;
using jsonrpc::internal::expected;
using jsonrpc::internal::unexpected;

/// 代表客户端的请求
struct request {
  call_type type;
  internal::id_type id;
  std::string method;
  native_type args;
};

/// 代表服务端的响应
struct response {
  id_type id;
  native_type result;
  native_type error;
};

/// jsonrpc增量解析器
class increment_parser {
 public:
  expected<request, std::string> get_request() {
    try_parse_object();
    if (!parsed_) {
      return unexpected{"no request parsed"};
    }
    auto object = std::move(*parsed_);
    parsed_.reset();
    return parse_request(std::move(object));
  }

  expected<response, std::string> get_response() {
    try_parse_object();
    if (!parsed_) {
      return unexpected{"no response parsed"};
    }
    auto object = std::move(*parsed_);
    parsed_.reset();
    return parse_response(std::move(object));
  }

  char* buffer() {  //
    return incremental_buffers_.in_place_buffer();
  }

  std::size_t buffer_capacity() const {  //
    return incremental_buffers_.in_place_buffer_capacity();
  }

  void buffer_consumed(std::size_t bytes) {  //
    incremental_buffers_.in_place_buffer_consumed(bytes);
  }

  void reserve_buffer(std::size_t bytes) {  //
    incremental_buffers_.reserve_in_place_buffer(bytes);
  }

 private:
  void try_parse_object() {
    if (parsed_) {
      return;
    }
    auto buffer = incremental_buffers_.get_parsed_buffer();
    if (buffer) {
      parsed_ = nlohmann::json::parse(*buffer);
    }
  }

  static expected<response, std::string> parse_response(nlohmann::json&& res) {
    auto id_it = res.find("id");
    auto result_it = res.find("result");
    auto error_it = res.find("error");

    if (id_it == end(res)) {
      return unexpected{"missing id field"};
    }
    if (result_it == end(res) && error_it == end(res)) {
      return unexpected{"missing error and result field"};
    }

    response parsed;
    parsed.id = std::move(*id_it);
    if (error_it != end(res)) {
      parsed.error = std::move(*error_it);
    }
    if (result_it != end(res)) {
      parsed.result = std::move(*result_it);
    }
    return {std::move(parsed)};
  }

  static expected<request, std::string> parse_request(nlohmann::json&& req) {
    auto id_it = req.find("id");
    auto method_it = req.find("method");
    auto params_it = req.find("params");

    if (method_it == end(req)) {
      return unexpected{"missing method field"};
    }
    if (!method_it->is_string()) {
      return unexpected{"method field is not a string"};
    }

    request parsed;
    parsed.method = method_it->get<std::string>();
    if (params_it == end(req) || params_it->is_null()) {
      parsed.args = nlohmann::json::array();
    } else if (!params_it->is_array() && !params_it->is_object()) {
      return unexpected{"non-structured arguments are not supported"};
    } else {
      parsed.args = std::move(*params_it);
    }

    if (id_it == end(req) || id_it->is_null()) {
      parsed.type = call_type::notification;
    } else {
      parsed.type = call_type::request;
      parsed.id = std::move(*id_it);
    }
    return {std::move(parsed)};
  }

  std::optional<nlohmann::json> parsed_;
  incremental_buffers incremental_buffers_;
};

}  // namespace internal

/// Rpc类型：具体Rpc协议。
class Rpc {
 public:
  using id_type = internal::id_type;
  using native_type = internal::native_type;
  using request_type = internal::request;
  using response_type = internal::response;
  using incremental_parser_type = internal::increment_parser;

  static std::string format_id(const id_type& id) { return id.dump(); }

  template <typename... Args>
  static auto serialize_notification(std::string_view method, Args&&... args)
      -> std::enable_if_t<internal::positional_args_v<Args...>, std::string> {
    return nlohmann::json({
                              {"jsonrpc", "2.0"},
                              {"method", method},
                              {"params", nlohmann::json::array({nlohmann::json(
                                             std::forward<Args>(args))...})},
                          })
        .dump();
  }

  template <typename... Args>
  static auto serialize_notification(std::string_view method, Args&&... args)
      -> std::enable_if_t<internal::named_args_v<Args...>, std::string> {
    return nlohmann::json({
                              {"jsonrpc", "2.0"},
                              {"method", method},
                              {"params", {{args.name, args.value}...}},
                          })
        .dump();
  }

  template <typename... Args>
  static auto serialize_notification(std::string_view, Args&&...)
      -> std::enable_if_t<!internal::positional_args_v<Args...> &&
                              !internal::named_args_v<Args...>,
                          std::string> {
    static_assert(
        internal::positional_args_v<Args...> || internal::named_args_v<Args...>,
        "JSON-RPC does not support mixed named and unnamed arguments");
  }

  template <typename... Args>
  static auto serialize_request(const id_type& id, std::string_view method,
                                Args&&... args)
      -> std::enable_if_t<internal::positional_args_v<Args...>, std::string> {
    return nlohmann::json({
                              {"jsonrpc", "2.0"},
                              {"method", method},
                              {"params", nlohmann::json::array({nlohmann::json(
                                             std::forward<Args>(args))...})},
                              {"id", id},
                          })
        .dump();
  }

  template <typename... Args>
  static auto serialize_request(const id_type& id, std::string_view method,
                                Args&&... args)
      -> std::enable_if_t<internal::named_args_v<Args...>, std::string> {
    return nlohmann::json({
                              {"jsonrpc", "2.0"},
                              {"method", method},
                              {"params", {{args.name, args.value}...}},
                              {"id", id},
                          })
        .dump();
  }

  template <typename... Args>
  static auto serialize_request(const id_type&, std::string_view, Args&&...)
      -> std::enable_if_t<!internal::positional_args_v<Args...> &&
                              !internal::named_args_v<Args...>,
                          std::string> {
    static_assert(
        internal::positional_args_v<Args...> || internal::named_args_v<Args...>,
        "JSON-RPC does not support mixed named and unnamed arguments");
  }

  static std::string serialize_response(const id_type& id) {
    return serialize_response(id, nlohmann::json{});
  }

  template <typename T>
  static std::string serialize_response(const id_type& id, T&& value) {
    return nlohmann::json{
        {"jsonrpc", "2.0"},
        {"id", id},
        {"result", std::forward<T>(value)},
    }
        .dump();
  }

  template <typename T>
  static std::string serialize_error_response(const id_type& id, T&& value) {
    return nlohmann::json{
        {"jsonrpc", "2.0"},
        {"id", id},
        {"error",
         [&]() {
           nlohmann::json error = {
               {"code", -32000},  // -32000 is an implementation-defined error
               {"data", std::forward<T>(value)},
           };
           if (error["data"].is_string()) {
             error["message"] = error["data"];
           } else {
             error["message"] = "unknown error";
           }
           return error;
         }()},
    }
        .dump();
  }

  static boost::asio::const_buffer buffer(const std::string& buf) {
    return boost::asio::const_buffer(buf.data(), buf.size());
  }

  template <typename T, typename F>
  static internal::expected<T, std::string> extract_args(
      const nlohmann::json& args, const args_specs<F>& specs) {
    try {
      if (args.is_array()) {
        return convert_positional_args<T>(args, specs);
      } else if (args.is_object()) {
        return convert_named_args<T>(args, specs);
      } else {
        throw std::runtime_error{"arguments are not a structured type"};
      }
    } catch (const std::exception& exc) {
      return internal::unexpected{std::string{"cannot convert arguments: "} +
                                  exc.what()};
    }
  }

 private:
  template <typename T, typename F>
  static constexpr T convert_positional_args(const nlohmann::json& array,
                                             const args_specs<F>& specs) {
    return convert_positional_args<T>(
        array, specs, std::make_index_sequence<args_specs<F>::size()>());
  }

  template <typename T, typename F, std::size_t... Idxs>
  static constexpr T convert_positional_args(const nlohmann::json& array,
                                             const args_specs<F>& specs,
                                             std::index_sequence<Idxs...>) {
    if (!specs.options().allow_extra_arguments &&
        array.size() > std::tuple_size_v<T>) {
      throw std::runtime_error{"too many arguments"};
    }
    return {[&]() {
      if (Idxs < array.size()) {
        try {
          return array.at(Idxs).get<std::tuple_element_t<Idxs, T>>();
        } catch (const ::nlohmann::json::type_error&) {
          throw std::runtime_error{"invalid type for argument " +
                                   specs.template get<Idxs>().name()};
        }
      }
      if (const auto& value = specs.template get<Idxs>().default_value()) {
        return *value;
      }
      throw std::runtime_error{"no value for argument " +
                               specs.template get<Idxs>().name()};
    }()...};
  }

  template <typename T, typename F>
  static T convert_named_args(const nlohmann::json& args,
                              const args_specs<F>& specs) {
    return convert_named_args<T>(
        args, specs, std::make_index_sequence<args_specs<F>::size()>{});
  }

  template <typename T, typename F, std::size_t... Idxs>
  static T convert_named_args(const nlohmann::json& args,
                              const args_specs<F>& specs,
                              std::index_sequence<Idxs...>) {
    if (!specs.options().allow_extra_arguments) {
      const std::array<const std::string*, sizeof...(Idxs)>
          available_arguments = {&specs.template get<Idxs>().name()...};
      for (auto it = args.begin(); it != args.end(); ++it) {
        auto arg_it = std::find_if(
            available_arguments.begin(), available_arguments.end(),
            [&](const std::string* arg) { return *arg == it.key(); });
        if (arg_it == available_arguments.end()) {
          throw std::runtime_error{"unexpected argument " + it.key()};
        }
      }
    }

    return T{[&]() {
      auto it = args.find(specs.template get<Idxs>().name());
      if (it != args.end()) {
        try {
          return it->template get<std::tuple_element_t<Idxs, T>>();
        } catch (const ::nlohmann::json::type_error&) {
          throw std::runtime_error{"invalid type for argument " +
                                   specs.template get<Idxs>().name()};
        }
      }
      if (const auto& value = specs.template get<Idxs>().default_value()) {
        return *value;
      }
      throw std::runtime_error{"no value for argument " +
                               specs.template get<Idxs>().name()};
    }()...};
  }
};

}  // namespace jsonrpc

#endif  // JSONRPC_RPC_HPP
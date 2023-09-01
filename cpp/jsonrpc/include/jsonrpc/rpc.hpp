#ifndef JSONRPC_RPC_HPP
#define JSONRPC_RPC_HPP

#include <array>
#include <optional>

#include "jsonrpc/call_type.hpp"
#include "jsonrpc/json.hpp"
#include "jsonrpc/utils.hpp"

namespace jsonrpc {

namespace internal {

template <typename... Args>
constexpr bool positional_args_v = (!is_arg_v<Args> && ...);

using id_type = nlohmann::json;
using native_type = nlohmann::json;
using jsonrpc::internal::Expected;
using jsonrpc::internal::Unexpected;

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
      -> std::enable_if_t<internal::positional_args_v<Args...>, std::string> {}
};

}  // namespace jsonrpc

#endif  // JSONRPC_RPC_HPP
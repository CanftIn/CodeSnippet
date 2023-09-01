#ifndef JSONRPC_CALLTYPE_HPP
#define JSONRPC_CALLTYPE_HPP

namespace jsonrpc {

enum class call_type {
  request = 0,
  notification = 1,
};

}  // namespace jsonrpc

#endif  // JSONRPC_CALLTYPE_HPP
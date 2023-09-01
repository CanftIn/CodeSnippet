#ifndef JSONRPC_DISPATCHER_HPP
#define JSONRPC_DISPATCHER_HPP

#include "jsonrpc/config.hpp"

namespace jsonrpc {

/// Rpc类型对应Rpc协议，jsonrpc就是json。
/// Map类型用于关联rpc过程和命名。
/// Lockable类型用于map的处理加锁。
template <typename Rpc, template <class...> class Map = default_map,
          typename Lockable = default_mutex>
class dispatcher {
  using rpc_type = Rpc;
  using mutex_type = Lockable;
  using args_type = decltype(typename rpc_type::request_type{}.args);
};


}

#endif  // JSONRPC_DISPATCHER_HPP
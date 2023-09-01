#ifndef JSONRPC_SERVER_HPP
#define JSONRPC_SERVER_HPP

namespace jsonrpc {

/// Rpc类型：具体Rpc协议。
/// Accpetor类型：Server接收端类型。
/// Dispatcher类型：分发类型用于存储和调度。
template <typename Rpc, typename Acceptor, typename Dispatcher>
class Server {
 public:
  using rpc_type = Rpc;
  using acceptor_type = Acceptor;
  using protocol_type = typename Acceptor::protocol_type;
  using dispatcher_type = Dispatcher;
  
};

}  // namespace jsonrpc

#endif  // JSONRPC_SERVER_HPP
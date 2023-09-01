#ifndef JSONRPC_CONFIG_HPP
#define JSONRPC_CONFIG_HPP

#include <mutex>
#include <unordered_map>

namespace jsonrpc {

template <typename... Args>
using default_map = std::unordered_map<Args...>;
using default_mutex = std::mutex;

}  // namespace jsonrpc

#endif  // JSONRPC_CONFIG_HPP
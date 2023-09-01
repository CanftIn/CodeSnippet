#ifndef FIBER_FIBER_HPP
#define FIBER_FIBER_HPP

#include <sys/socket.h>
#include <sys/types.h>

namespace fiber {

typedef enum {
  FIBER_EVENT_T_KERNEL,  // Linux: epoll
  FIBER_EVENT_T_POLL,
  FIBER_EVENT_T_SELECT,
  FIBER_EVENT_T_WMSG,
} fiber_event_t;

/// @brief Fiber class
class Fiber {
 public:
  /// running为true表面协程已经启动，禁止调用start，
  /// 为false时则需要调用start启动协程。
  Fiber(bool running = false);

  virtual ~Fiber();

  /// stack_size为协程栈大小，单位为字节。
  void start(size_t stack_size = 320000);

  /// 通知协程退出。
  bool kill();

  /// 判断协程是否被通知退出。
  bool killed() const;


 private:
  
};

}  // namespace fiber

#endif  // FIBER_FIBER_HPP
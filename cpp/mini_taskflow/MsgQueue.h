#ifndef MINI_TASKFLOW_MSGQUEUE_H
#define MINI_TASKFLOW_MSGQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

namespace mini_taskflow {

class Task;

enum class TaskState : uint8_t {
  Finish = 0,
};

struct Msg {
  Task* task = nullptr;
  TaskState task_state = TaskState::Finish;
};

class MsgQueue {
 public:
  void push(const Msg& msg);
  Msg pop();
  Msg front();
  bool empty();
  void wait();
  void stopWait();

 private:
  std::condition_variable condition_;
  std::mutex mtx_;
  std::queue<Msg> queue_;
  bool stop_ = false;
};

}  // namespace mini_taskflow

#endif  // MINI_TASKFLOW_MSGQUEUE_H
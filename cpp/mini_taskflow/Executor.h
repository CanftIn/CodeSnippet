#ifndef MINI_TASKFLOW_EXECUTOR_H
#define MINI_TASKFLOW_EXECUTOR_H

#include <thread>

#include "MsgQueue.h"

namespace mini_taskflow {

class ThreadPool;

class Executor {
 public:
  Executor();
  ~Executor();

  void run(Task* task);
  void spawn(Task* task);
  void notify(const Msg& msg);

 protected:
  size_t total_unfinished_task_num_ = 0;
  std::condition_variable condition_;
  ThreadPool* pool_ = nullptr;
  MsgQueue queue_;
};

}  // namespace mini_taskflow

#endif  // MINI_TASKFLOW_EXECUTOR_H
#ifndef MINI_TASKFLOW_TASK_H
#define MINI_TASKFLOW_TASK_H

#include <cstdint>
#include <functional>
#include <vector>

namespace mini_taskflow {

class Executor;

enum class TaskType : uint8_t {
  Task = 0,
  TaskFlow = 1,
};

class Task {
 public:
  Task() = default;

  Task(std::function<void()>&& func, size_t id = 0);

  size_t getTaskNum();

  void addChild(Task* task);
  void precede(Task* task);
  void succeed(Task* task);
  void run();

 private:
  Task* parent_ = nullptr;
  size_t id_ = 0;
  TaskType parent_type_ = TaskType::Task;
  Executor* executor_;
  std::function<void()> func_;
  std::vector<Task*> child_;
  int unfinished_child_num_ = 0;
  int unfinished_depend_num_ = 0;
  std::vector<Task*> successors_;
  std::vector<Task*> dependents_;
};

}  // namespace mini_taskflow

#endif  // MINI_TASKFLOW_TASK_H
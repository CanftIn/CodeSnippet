#include "Task.h"

namespace mini_taskflow {

Task::Task(std::function<void()>&& func, size_t id) : func_(func), id_(id) {}

size_t Task::getTaskNum() {
  size_t task_num = 1;
  for (auto& child : child_) {
    task_num += child->getTaskNum();
  }
  return task_num;
}

void Task::addChild(Task* task) {
  child_.push_back(task);
  task->parent_ = this;
  task->parent_type_ = TaskType::Task;
  unfinished_child_num_++;
}

void Task::precede(Task* task) {
  successors_.push_back(task);
  task->dependents_.push_back(this);
  unfinished_depend_num_++;
}

void Task::succeed(Task* task) {
  dependents_.push_back(task);
  task->successors_.push_back(this);
  unfinished_depend_num_++;
}

void Task::run() {
  func_();
}

}  // namespace mini_taskflow
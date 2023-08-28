#ifndef MINI_WORKFLOW_SUBTASK_H
#define MINI_WORKFLOW_SUBTASK_H

#include <cstddef>

class ParallelTask;

class SubTask {
 public:
  SubTask() {
    this->parent_ = nullptr;
    this->entry_ = nullptr;
    this->pointer_ = nullptr;
  }

  virtual ~SubTask() {}

  virtual void dispatch() = 0;

  ParallelTask* get_parent_task() const { return this->parent_; }
  void* get_pointer() const { return this->pointer_; }
  void set_pointer(void* pointer) { this->pointer_ = pointer; }

 private:
  virtual SubTask* done() = 0;

 protected:
  void subtask_done();

 private:
  friend class ParallelTask;

  ParallelTask* parent_;
  SubTask** entry_;
  void* pointer_;
};

class ParallelTask : public SubTask {
 public:
  ParallelTask(SubTask** subtasks, size_t n) {
    this->subtasks_ = subtasks;
    this->subtasks_num_ = n;
  }

  SubTask** get_subtasks(size_t* n) const {
    *n = this->subtasks_num_;
    return this->subtasks_;
  }

  void set_subtasks(SubTask** subtasks, size_t n) {
    this->subtasks_ = subtasks;
    this->subtasks_num_ = n;
  }

  virtual void dispatch();

 protected:
  SubTask** subtasks_;
  size_t subtasks_num_;

 private:
  friend class SubTask;
  size_t left_num_;
};

#endif  // MINI_WORKFLOW_SUBTASK_H
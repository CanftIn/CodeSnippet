#include "SubTask.h"

void SubTask::subtask_done() {
  SubTask* curr = this;
  ParallelTask* parent;
  SubTask** entry;

  while (true) {
    parent = curr->parent_;
    entry = curr->entry_;
    curr = curr->done();
    if (curr) {
      curr->parent_ = parent;
      curr->entry_ = entry;
      if (parent) {
        *entry = curr;
      }
      curr->dispatch();
    } else if (parent) {
      if (__sync_sub_and_fetch(&parent->left_num_, 1) == 0) {
        curr = parent;
        continue;
      }
    }
    break;
  }
}

void ParallelTask::dispatch() {
  SubTask** end = this->subtasks_ + this->subtasks_num_;
  SubTask** p = this->subtasks_;
  this->left_num_ = this->subtasks_num_;

  if (this->left_num_ != 0) {
    do {
      (*p)->parent_ = this;
      (*p)->entry_ = p;
      (*p)->dispatch();
    } while (++p != end);
  } else {
    this->subtask_done();
  }
}
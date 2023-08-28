#include "MsgQueue.h"

namespace mini_taskflow {

void MsgQueue::push(const Msg& msg) {
  std::unique_lock<std::mutex> lock(mtx_);
  queue_.push(msg);
  condition_.notify_one();
}

Msg MsgQueue::front() {
  std::unique_lock<std::mutex> lock(mtx_);
  return queue_.front();
}

Msg MsgQueue::pop() {
  std::unique_lock<std::mutex> lock(mtx_);
  Msg msg = queue_.front();
  queue_.pop();
  return msg;
}

bool MsgQueue::empty() {
  std::unique_lock<std::mutex> lock(mtx_);
  return queue_.empty();
}

void MsgQueue::wait() {
  std::unique_lock<std::mutex> lock(mtx_);
  condition_.wait(lock, [this] { return !queue_.empty(); });
}

void MsgQueue::stopWait() {
  std::unique_lock<std::mutex> lock(mtx_);
  stop_ = true;
  condition_.notify_all();
}

}  // namespace mini_taskflow
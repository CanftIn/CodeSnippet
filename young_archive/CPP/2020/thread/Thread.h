#ifndef __THREAD_H__
#define __THREAD_H__

#include "Atomic.h"

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pthread.h>

class Thread : boost::noncopyable {
public:
  typedef boost::function<void ()> ThreadFunc;

  explicit Thread(const ThreadFunc&, const std::string& name = std::string());
  ~Thread();

  void start();
  void join();

  bool started() const {
    return _started;
  }

  pid_t tid() const {
    return *_tid;
  }

  const std::string& name() {
    return _name;
  }

private:
  bool _started;
  bool _joined;
  pthread_t _pthread_id;
  boost::shared_ptr<pid_t> _tid;
  ThreadFunc _func;
  std::string _name;
};

namespace CurrentThread {
  pid_t tid();
  const char* name();
  bool isMainThread();
}


#endif
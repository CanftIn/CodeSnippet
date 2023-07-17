#include "Thread.h"

#include <boost/weak_ptr.hpp>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/unistd.h>

namespace CurrentThread {
  __thread const char* t_threadName = "unknown";
}

namespace {
  __thread pid_t t_cacheTid = 0;

  pid_t gettid() {
    return static_cast<pid_t>(::syscall(SYS_gettid));
  }

  void afterFork() {
    t_cacheTid = gettid();
    CurrentThread::t_threadName = "main";
  }

  class ThreadNameInitializer {
  public:
    ThreadNameInitializer() {
      CurrentThread::t_threadName = "main";
      pthread_atfork(nullptr, nullptr, &afterFork);
    }
  };

  ThreadNameInitializer init;

  struct ThreadData {
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc _func;
    std::string _name;
    boost::weak_ptr<pid_t> _wk_tid;

    ThreadData(const ThreadFunc& func,
               const std::string& name,
               const boost::shared_ptr<pid_t>& tid)
      : _func(func),
        _name(name),
        _wk_tid(tid)
    { }

    
  };
  
}



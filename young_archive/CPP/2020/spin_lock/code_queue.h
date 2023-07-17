#ifndef __CODEQUEUE_H__
#define __CODEQUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <assert.h>
#include <string>

using std::string;

#include "spin_lock.h"

#define QUEUE_RESERVE_LENGTH 8 // reserve length
#define MAX_LOCK_STRUCT_SIZE 1024

#define CQ_ERR_QUEUE_FULL (-3)

class CodeQueue {
public:
  typedef enum {
    Init = 0,
    Recover = 1
  } EMInitType;

  typedef enum {
    NoLock = 0,
    SpinLock,
    PthreadMutexLock,
  } EMLockType;

  static int CreateMQByFile(const char* mq_file, CodeQueue* code_queue, int shm_key = 0, int max_attach_num = 0);

  CodeQueue(const char* name = "");
  ~CodeQueue();

  const string& GetName();
  void SetName(const char* name);

  bool CanWrite();

private:
  CodeQueue(const CodeQueue&);
  CodeQueue(CodeQueue&);

  
};



#endif
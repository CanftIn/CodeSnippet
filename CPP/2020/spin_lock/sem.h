#ifndef __SEM_H__
#define __SEM_H__

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string>

// Semaphore encapsulation
class Sem {
public:
  Sem() : _sem_id(-1), _sem_num(0) {}
  int Open(int sem_key, int sem_num = 1, int init_res_num = 1);

  int GetSemID() {
    return _sem_id;
  }

  void Post(unsigned index = 0);
  void Wait(unsigned index = 0);
  bool TryWait(unsigned index = 0);
  bool TimeWait(unsigned index, unsigned& sec, unsigned& nano_sec);

  time_t LastOperaTime();
  time_t CreateTime();

private:
  void SetVal(unsigned index = 0, unsigned short value = 1);
  int GetVal(unsigned index = 0);
  void Destroy();
  int _sem_id;
  int _sem_num;
};


#endif
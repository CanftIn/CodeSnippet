#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include "sem.h"

int Sem::Open(int sem_key, int sem_num/* = 1 */, int init_res_num/* = 1*/) {
  _sem_id = semget(sem_key, sem_num, 0600 | IPC_CREAT | IPC_EXCL);
  
  if (_sem_id < 0) {
    _sem_id = semget(sem_key, sem_num, 0600);

    if (_sem_id < 0)
      return -1;
    
    for (int i = 0; i < _sem_num; ++i) {
      if (GetVal(i) == ((i << 16) - 1)) {
        SetVal(i, init_res_num);
      }
    }
  } else {
    unsigned short* init_array = new unsigned short[sem_num];

    for (int i = 0; i < sem_num; ++i) {
      init_array[i] = init_res_num;
    }
    semctl(_sem_id, 0, SETALL, init_array);
    delete[] init_array;
  }
  _sem_num = sem_num;
  return 0;
}

void Sem::Post(unsigned index /* = 0 */) {
  if (_sem_id == -1)
    return;
  
  struct sembuf _buf;
  _buf.sem_num = index;
  _buf.sem_op = 1;
  _buf.sem_flg = SEM_UNDO;

  semop(_sem_id, &_buf, 1);
}

void Sem::Wait(unsigned index /* = 0 */) {
  if (_sem_id == -1)
    return;
  
  struct sembuf _buf;
  _buf.sem_num = index;
  _buf.sem_num = -1;
  _buf.sem_flg = SEM_UNDO;

  semop(_sem_id, &_buf, 1);
}

bool Sem::TryWait(unsigned index /* = 0 */) {
  if (_sem_id == -1)
    return false;
  
  errno = 0;
  struct sembuf _buf;
  _buf.sem_num = index;
  _buf.sem_op = -1;
  _buf.sem_flg = SEM_UNDO | IPC_NOWAIT;

  int ret = semop(_sem_id, &_buf, 1);

  if (ret)
    return false;
  else
    return true;
}

bool Sem::TimeWait(unsigned index, unsigned& sec, unsigned& nano_sec) {
  if (_sem_id == -1)
    return false;
  
  struct timespec ts;
  ts.tv_sec = sec;
  ts.tv_nsec = nano_sec;

  struct sembuf _buf;
  _buf.sem_num = index;
  _buf.sem_op = -1;
  _buf.sem_flg = SEM_UNDO;

  for (unsigned i = 0; i < 5; ++i) {
    errno = 0;
    int ret = semtimedop(_sem_id, &_buf, 1, &ts);

    if (ret) {
      if (errno == EAGAIN)
        return false;
      else if (errno == EINTR)
        continue;
      else
        return false;
    } else {
      return true;
    }
  }

  return false;
}

time_t Sem::LastOperaTime() {
  if (_sem_id == -1)
    return 0;
  
  struct semid_ds buf;

  int ret = semctl(_sem_id, 0, IPC_STAT, &buf);

  if (ret < 0)
    return 0;
  return buf.sem_otime;
}

time_t Sem::CreateTime() {
  if (_sem_id == -1)
    return 0;
  
  struct semid_ds buf;

  int ret = semctl(_sem_id, 0, IPC_STAT, &buf);

  if (ret < 0)
    return 0;
  return buf.sem_ctime;
}

void Sem::SetVal(unsigned index /* = 0 */, unsigned short value /* = 1 */) {
  if (_sem_id == -1)
    return;
  semctl(_sem_id, index, SETVAL, value);
}

int Sem::GetVal(unsigned index /* = 0 */) {
  if (_sem_id == -1)
    return 0;
  
  return semctl(_sem_id, index, GETVAL);
}

void Sem::Destroy() {
  if (_sem_id == -1)
    return;
  
  semctl(_sem_id, 0, IPC_RMID);
}

#if 0
int main() {
  Sem _sem;
  if (_sem.Open(123456, 2, 3)) {
    return -3;
  }

  _sem.Wait(0);
  _sem.Wait(0);
  _sem.Wait(0);
  
  return 0;
}

#endif
#ifndef __SPIN_LOCK_H__
#define __SPIN_LOCK_H__
#include <sys/shm.h>
#include <sched.h>
#include <errno.h>

template<typename T1, typename T2, typename T3>
static inline bool cas(T1& val, T2 old_val, T3 new_val) {
  return __sync_val_compare_and_swap(&val, old_val, new_val) == old_val;
}

template<typename T1, typename T2>
static inline T1 inc(T1& val, T2 delta) {
  return __sync_add_and_fetch(&val, delta);
}

# if false
#include <pthread.h>
typedef pthread_spinlock_t spinlock_t;

#define spin_lock_init(lock) pthread_spin_init(lock, PTHREAD_PROCESS_SHARED)
#define spin_lock(lock) pthread_spin_lock(lock)
#define spin_trylock(lock) pthread_spin_trylock(lock)
#define spin_unlock(lock) pthread_spin_unlock(lock)
#else

typedef volatile int spinlock_t;

#define SPIN_LOCK_INITIALIZER 1

static inline int spin_lock_init(spinlock_t* lock) {
  *lock = 1;
  return 0;
}

static inline int spin_lock(spinlock_t* lock) {
  while (inc(*lock, -1) < 0) {
    inc(*lock, 1);
    sched_yield();
  }
  return 0;
}

static inline int spin_trylock(spinlock_t* lock) {
  if (inc(*lock, -1) < 0) {
    inc(*lock, 1);
    return EBUSY;
  }
  return 0;
}

static inline int spin_unlock(spinlock_t* lock) {
  inc(*lock, 1);
  return 0;
}

#endif

const static int MAX_RDLOCK = 10000;

#define SPIN_RWLOCK_INITIALIZER { MAX_RDLOCK, 0, 0 }

typedef struct {
  volatile int count;
  char type;
  char wait;
} spin_rwlock_t;

static inline int spin_rwlock_init(spin_rwlock_t* lock, void* unused) {
  lock->count = MAX_RDLOCK;
  lock->type = 0;
  lock->wait = 0;
  return 0;
}

static inline int spin_rwlock_rdlock(spin_rwlock_t* lock) {
  while (lock->wait) {
    sched_yield();
  }

  while (inc(lock->count, -1) < 0) {
    inc(lock->count, 1);
    sched_yield();
  }
  lock->type = 0;
  return 0;
}

static inline int spin_rwlock_tryrdlock(spin_rwlock_t* lock) {
  if (inc(lock->count, -1) < 0) {
    inc(lock->count, 1);
    return EBUSY;
  }
  lock->type = 0;
  return 0;
}

static inline int spin_rwlock_wrlock(spin_rwlock_t* lock) {
  bool waited = false;
  while (inc(lock->count, -MAX_RDLOCK) < 0) {
    if (!waited) {
      inc(lock->wait, 1);
      waited = true;
    }
    inc(lock->count, MAX_RDLOCK);
    sched_yield();
  }
  if (waited) {
    inc(lock->wait, -1);
  }
  lock->type = 1;
  return 0;
}

static inline int spin_rwlock_trywrlock(spin_rwlock_t* lock) {
  if (inc(lock->count, -MAX_RDLOCK) < 0) {
    inc(lock->count, MAX_RDLOCK);
    return EBUSY;
  }
  lock->type = 1;
  return 0;
}

static inline int spin_rwlock_unlock(spin_rwlock_t* lock) {
  inc(lock->count, lock->type ? MAX_RDLOCK : 1);
  return 0;
}

static inline int spin_rwlock_destroy(spin_rwlock_t* lock) {
  return 0;
}

static inline spinlock_t* shm_spin_lock_init(key_t shm_key, int& out_shm_id) {
  int first_create = 1;
  int shm_id = shmget(shm_key, sizeof(spinlock_t), IPC_CREAT | IPC_EXCL | 06666);

  if (shm_id < 0) {
    first_create = 0;
    shm_id =  shmget(shm_key, sizeof(spinlock_t), 0666);
  }

  if (shm_id < 0) {
    return 0;
  }

  out_shm_id = shm_id;

  spinlock_t* shm_spinlock_t = (spinlock_t*)shmat(shm_id, 0, 0);

  if (shm_spinlock_t == (spinlock_t*)(-1)) {
    return 0;
  }

  if (first_create) {
    spin_lock_init(shm_spinlock_t);
  } else {
    struct shmid_ds s_ds;
    shmctl(shm_id, IPC_STAT, &s_ds);

    if (s_ds.shm_nattch == 1) {
      spin_lock_init(shm_spinlock_t);
    }
  }
  return shm_spinlock_t;
}


#endif
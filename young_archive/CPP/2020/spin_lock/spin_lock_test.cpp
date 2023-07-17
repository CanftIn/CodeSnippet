#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "spin_lock.h"

int main() {
  spinlock_t lock;
  spin_lock_init(&lock);

  timeval t1, t2;
  gettimeofday(&t1, NULL);

  for (int i = 0; i < 10000000; ++i) {
    spin_lock(&lock);
    spin_unlock(&lock);
  }

  gettimeofday(&t2, NULL);
  int cost = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
  printf("spin lock cost %dms\n", cost);

  pthread_mutex_t mp1 = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_init(&mp1, NULL);

  gettimeofday(&t1, NULL);

  for (int i = 0; i < 10000000; ++i) {
    pthread_mutex_lock(&mp1);
    pthread_mutex_unlock(&mp1);
  }

  gettimeofday(&t2, NULL);
  cost = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
  printf("pthread_mutex cost %dms\n", cost);

  return 0;
}
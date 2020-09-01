#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define WORK_SIZE 5000000
#define WORKER_COUNT 10

int g_iFlagAtom = 1;
pthread_t g_tWorkerID[WORKER_COUNT];
int g_iSum = 0;

void* thread_worker(void* arg) {
  printf("WORKRE THREAD %08X START UP\n", (unsigned int)pthread_self());
  for (int i = 0; i < WORK_SIZE; ++i) {
    if (g_iFlagAtom) {
      __sync_fetch_and_add(&g_iSum, 1);
    } else {
      g_iSum++;
    }
  }
  return NULL;
}

void* thread_management(void* arg) {
  printf("MANAGEMENT THREAD %08X START UP\n", (unsigned int)pthread_self());
  for (int i = 0; i < WORKER_COUNT; ++i) {
    pthread_join(g_tWorkerID[i], NULL);
  }
  printf("ALL WORKER THREADS FINISHED.\n");
  return NULL;
}

int main(int argc, char* argv[]) {
  pthread_t tManagmentID;
  pthread_create(&tManagmentID, NULL, thread_management, NULL);
  for (int i = 0; i < WORKER_COUNT; ++i) {
    pthread_create(&g_tWorkerID[i], NULL, thread_worker, NULL);
  }
  printf("CREATED %d WORKER THREADS\n", WORKER_COUNT);
  pthread_join(tManagmentID, NULL);
  printf("THE SUM: %d\n", g_iSum);

  return 0;
}
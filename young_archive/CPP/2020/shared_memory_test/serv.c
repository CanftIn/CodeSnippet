#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct shared_msg {
  int update; // update data flag, 1: update, 0: dont update
  char text[BUFSIZ];
};

int main() {
  key_t key; // shared memory key
  int shmid; // shared memory id
  char buf[BUFSIZ];
  struct shared_msg* msg; // shared memory address

  key = (key_t)1234;

  // create shared memory
  shmid = shmget(key, sizeof(struct shared_msg), IPC_CREAT | 0666);
  if (shmid < 0) {
    fprintf(stderr, "create shared memory failed\n");
    exit(EXIT_FAILURE);
  }

  // map shared memory to data frame
  msg = (struct shared_msg*)shmat(shmid, NULL, 0);
  if (msg < (struct shared_msg*)0) {
    fprintf(stderr, "map shared memory to process failed\n");
    exit(EXIT_FAILURE);
  }

  printf("shared memory address: %X\n", (int)msg);

  while (1) {
    printf("input message: ");
    fgets(buf, BUFSIZ, stdin);
    strncpy(msg->text, buf, BUFSIZ);
    msg->update = 1;
    printf("finish data updating\n");

    if (strncmp(buf, "EOF", 3) == 0) {
      break;
    }
  }

  if (shmdt(msg) < 0) {
    fprintf(stderr, "failed to detach shared memory and process\n");
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
}
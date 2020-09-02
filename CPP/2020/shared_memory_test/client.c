#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct shared_msg {
  int update;
  char text[BUFSIZ];
};

void main() {
  key_t key;
  int shmid;
  char buf[BUFSIZ];
  struct shared_msg* msg;

  key = (key_t)1234;

  shmid = shmget(key, sizeof(struct shared_msg), IPC_CREAT | 0666);
  if (shmid < 0) {
    fprintf(stderr, "create shared memory failed\n");
    exit(EXIT_FAILURE);
  }

  msg = (struct shared_msg*)shmat(shmid, NULL, 0);
  if (msg < (struct shared_msg*)0) {
    fprintf(stderr, "map shared memory to process failed\n");
    exit(EXIT_FAILURE);
  }

  printf("shared memory address: %X\n", (int)msg);

  while (1) {
    while (msg->update == 1) {
      sprintf(buf, "%s", msg->text);
      printf("read message: %s", buf);
      msg->update = 0;
    }

    if (strncmp(buf, "EOF", 3) == 0) {
      break;
    }
  }

  if (shmdt(msg) < 0) {
    fprintf(stderr, "failed to detach shared memory and process\n");
    exit(EXIT_FAILURE);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    fprintf(stderr, "delete shared memory failed\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
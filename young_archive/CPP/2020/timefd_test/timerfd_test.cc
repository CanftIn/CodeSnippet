#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int
main(int argc, char *argv[])
{
  struct itimerspec new_value;
  int max_exp, fd;
  struct timespec now;
  uint64_t exp, tot_exp;
  ssize_t s;

  if (clock_gettime(CLOCK_REALTIME, &now) == -1)
    handle_error("clock_gettime");
  
  new_value.it_value.tv_sec = now.tv_sec + 1;
  new_value.it_value.tv_nsec = now.tv_nsec;

  new_value.it_interval.tv_sec = 0;
  new_value.it_interval.tv_nsec = 500000000;
  max_exp = 5;

  fd = timerfd_create(CLOCK_REALTIME, 0);
  if (fd == -1)
    handle_error("timerfd_create");
  
  if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
    handle_error("timerfd_settime");
  
  printf("timer started\n");
  for (tot_exp = 0; tot_exp < max_exp;) {
    s = read(fd, &exp, sizeof(uint64_t));
    if (s != sizeof(uint64_t))
      handle_error("read");
    tot_exp += exp;
    printf("read: %llu; total=%llu\n",
      (unsigned long long) exp,
      (unsigned long long) tot_exp);
  }

  return 0;
}
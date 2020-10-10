#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>

using namespace std;

const int EPOLL_SIZE = 10;

int main(int argc, char* argv[]) {
  int tfd, epfd, nfds;
  struct epoll_event event;
  struct epoll_event events[EPOLL_SIZE];

  tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
  if (tfd < 0) {
    cerr << "timerfd_create error!" << endl;
    return -1;
  }
  struct timespec startTime, intervalTime;
  startTime.tv_sec = 0;
  startTime.tv_nsec = 1;
  intervalTime.tv_sec = 3;
  intervalTime.tv_nsec = 0;
  struct itimerspec newValue;
  newValue.it_value = startTime;
  newValue.it_interval = intervalTime;
  if (timerfd_settime(tfd, 0, &newValue, NULL) < 0) {
    cerr << "timerfd_settime error!" << endl;
    return -1;
  }
  epfd = epoll_create(EPOLL_SIZE);
  if (epfd < 0) {
    cerr << "epoll_create error!" << endl;
    return -1;
  }

  event.data.fd = tfd;
  event.events = EPOLLIN;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, tfd, &event) < 0) {
    cerr << "epoll_ctl error!" << endl;
    return -1;
  }
  uint64_t count = 0;
  while (1) {
    nfds = epoll_wait(epfd, events, EPOLL_SIZE, 0);
    if (nfds == 0) continue;
    for (int i = 0; i < nfds; ++i) {
      if (events[i].events & EPOLLIN) {
        uint64_t data;
        read(events[i].data.fd, &data, sizeof(uint64_t));
        count += data;
        cout << "read: " << data << ", timer count: " << count << endl;
      }
    }
  }
  return 0;
}
#ifndef __EPOLL_H__
#define __EPOLL_H__

#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#include <string>
#include <stdexcept>
#include <iostream>

#include "spin_lock.h"

#define EPOLL_ENKEY(pos, id) ((uint64_t)(((uint64_t)pos << 32) | (uint32_t)id))
#define EPOLL_DEKEY(key, pos, id) (pos = (uint64_t)(key) >> 32,id = (uint32_t)(key))

class Epoll {
public:
  Epoll();
  ~Epoll();

  int Create(int max_fd, int epoll_fd = -1, bool need_lock = false);
  int Wait(int time_ms);
  int GetEvents(long long& ll_key, unsigned int& event);

  int Add(int fd, long long ll_key, int flag);
  int Modify(int fd, long long ll_key, int flag);
  int Del(int fd);

private:
  int Ctl(int fd, long long ll_key, int epoll_action, int flag);

  int _epoll_fd;
  int _max_fd;
  bool _is_close_epoll_fd;
  bool _is_lock;

  typedef struct tagEpollStat {
    epoll_event* _epoll_events;
    int _event_num;
    int _curr_event_index;
    spin_rwlock_t _rwlock;
  } EpollStat;
  EpollStat _stat[2];
  EpollStat *volatile _point_stat;
};


#endif
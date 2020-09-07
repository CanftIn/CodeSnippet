#include <unistd.h>
#include <sys/time.h>
#include "epoll_flow.h"

Epoll::Epoll() {
  _is_lock = false;
  _epoll_fd = -1;
  _is_close_epoll_fd = true;

  for (int i = 0; i < 2; ++i) {
    _stat[i]._epoll_events = NULL;
    _stat[i]._event_num = 0;
    _stat[i]._curr_event_index = 0;
    spin_rwlock_init(&_stat[i]._rwlock, NULL);
  }

  _point_stat = &_stat[0];
}

Epoll::~Epoll() {
  if (_is_close_epoll_fd && _epoll_fd >= 0) {
    close(_epoll_fd);
  }

  for (int i = 0; i < 2; ++i) {
    if (_stat[i]._epoll_events) {
      delete[] _stat[i]._epoll_events;
      _stat[i]._epoll_events = NULL;
    }
    _stat[i]._event_num = 0;
    _stat[i]._curr_event_index = 0;
    spin_rwlock_destroy(&_stat[i]._rwlock);
  }
}

int Epoll::Create(int max_fd, int epoll_fd, bool need_lock) {
  _max_fd = max_fd;
  _is_lock = need_lock;

  if (_epoll_fd < 0) {
    _epoll_fd = epoll_create(max_fd);
    if (_epoll_fd < 0)
      return -1;
  } else {
    _epoll_fd = epoll_fd;
    _is_close_epoll_fd = false;
  }

  _stat[0]._epoll_events = new epoll_event[max_fd];
  if (need_lock) {
    _stat[1]._epoll_events = new epoll_event[max_fd];
  }
  return _epoll_fd;
}

int Epoll::Add(int fd, long long ll_key, int flag) {
  return Ctl(fd, ll_key, EPOLL_CTL_ADD, flag);
}

int Epoll::Del(int fd) {
  return Ctl(fd, 0, EPOLL_CTL_DEL, 0);
}

int Epoll::Modify(int fd, long long ll_key, int flag) {
  return Ctl(fd, ll_key, EPOLL_CTL_MOD, flag);
}

// single thread access
int Epoll::Wait(int time_ms) {
  EpollStat* p_stat;
  if (_is_lock && _point_stat == &_stat[0])
    p_stat = &_stat[1];
  else
    p_stat = &_stat[0];

  if (_is_lock) {
    if (spin_rwlock_trywrlock(&p_stat->_rwlock))
      spin_rwlock_wrlock(&p_stat->_rwlock);
  }

  p_stat->_event_num = 0;
  p_stat->_curr_event_index = 0;

  do {
    struct timeval before;
    if (time_ms > 0) {
      gettimeofday(&before, NULL);
    }

    p_stat->_event_num = epoll_wait(_epoll_fd, p_stat->_epoll_events, _max_fd, time_ms);

    if (time_ms > 0) {
      struct timeval after;
      gettimeofday(&after, NULL);
    }
  }
  while (p_stat->_event_num == -1 && errno == EINTR);

  _point_stat = p_stat;
  if (_is_lock)
    spin_rwlock_unlock(&p_stat->_rwlock);
  
  return p_stat->_event_num;
}

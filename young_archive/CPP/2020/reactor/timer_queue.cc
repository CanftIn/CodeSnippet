#include <unistd.h>
#include <strings.h>
#include <pthread.h>
#include <sys/timerfd.h>
#include "timer_queue.h"
#include "utils.h"

timer_queue::timer_queue() 
  : _count(0), _next_timer_id(0), _pioneer(-1) {
  _timerfd = ::timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK | TFD_CLOEXEC);
  exit_if(_timerfd == -1, "timefd_create()");
}

timer_queue::~timer_queue() {
  ::close(_timerfd);
}

int timer_queue::add_timer(timer_event &te) {
  te.timer_id = _next_timer_id++;
  heap_add(te);

  if (_event_list[0].ts < _pioneer) {
    _pioneer = _event_list[0].ts;
    reset_time();
  }
  return te.timer_id;
}

void timer_queue::del_timer(int timer_id) {
  mit it = _position.find(timer_id);
  if (it == _position.end()) {
    error_log("no such a timerid %d", timer_id);
    return ;
  }

}

void timer_queue::get_time(std::vector<timer_event> &fired_evs) {
  std::vector<timer_event> _reuse_list;
  while (_count != 0 && _pioneer == _event_list[0].ts) {
    timer_event te = _event_list[0];
    fired_evs.push_back(te);
    if (te.interval) {
      te.ts += te.interval;
      _reuse_list.push_back(te);
    }
    heap_pop();
  }
  for (vit it = _reuse_list.begin();)
}

void timer_queue::reset_time() {
  struct itimerspec old_ts, new_ts;
  ::bzero(&new_ts, sizeof(new_ts));
  if (_pioneer != (uint64_t)-1) {
    new_ts.it_value.tv_sec = _pioneer / 1000;
    new_ts.it_value.tv_nsec = (_pioneer % 1000) * 1000000;
  }
  ::timerfd_settime(_timerfd, TFD_TIMER_ABSTIME, &new_ts, &old_ts);
}

void timer_queue::heap_add(timer_event &te) {
  _event_list.push_back(te);
  _position[te.timer_id] = _count;

  int curr_pos = _count;
  ++_count;

  int prt_pos = (curr_pos - 1) / 2;
  while (prt_pos >= 0 && _event_list[curr_pos].ts < _event_list[prt_pos].ts) {
    timer_event tmp = _event_list[curr_pos];
    _event_list[curr_pos] = _event_list[prt_pos];
    _event_list[prt_pos] = tmp;

    _position[_event_list[curr_pos].timer_id] = curr_pos;
    _position[tmp.timer_id] = prt_pos;

    curr_pos = prt_pos;
    prt_pos = (curr_pos - 1) / 2;
  }
}

void timer_queue::heap_del(int pos) {
  timer_event to_del = _event_list[pos];
  _position.erase(to_del.timer_id);

  timer_event tmp = _event_list[_count - 1];
  _event_list[pos] = tmp;
  _position[tmp.timer_id] = pos;

  --_count;
  _event_list.pop_back();

  heap_hold(pos);
}

void timer_queue::heap_pop() {
  if (_count <= 0) return;
  _position.erase(_event_list[0].timer_id);

  if (_count > 1) {
    timer_event tmp = _event_list[_count - 1];
    _event_list[0] = tmp;
    _position[tmp.timer_id] = 0;

    _event_list.pop_back();
    --_count;
    heap_hold(0);
  } else if (_count == 1) {
    _event_list.clear();
    _count = 0;
  }
}

void timer_queue::heap_hold(int pos) {
  int left = 2 * pos + 1;
  int right = 2 * pos + 2;
  int min_pos = pos;
  if (left < _count && _event_list[min_pos].ts > _event_list[left].ts) {
    min_pos = left;
  }
  if (right < _count && _event_list[min_pos].ts > _event_list[right].ts) {
    min_pos = right;
  }
  if (min_pos != pos) {
    timer_event tmp = _event_list[min_pos];
    _event_list[min_pos] = _event_list[pos];
    _event_list[pos] = tmp;

    _position[_event_list[min_pos].timer_id] = min_pos;
    _position[tmp.timer_id] = pos;

    heap_hold(min_pos);
  }
}

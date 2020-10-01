#ifndef __EVENT_BASE_H__
#define __EVENT_BASE_H__

#include <stdint.h>
#include <stdio.h>

class event_loop;

typedef void io_callback(event_loop *loop, int fd, void *args);
typedef void timer_callback(event_loop *loop, void *usr_data);

typedef void (*pendingFunc)(event_loop*, void*);

// 注册 io 事件
struct io_event {
  io_event();
  int mask;           // EPOLLIN EPOLLOUT
  io_callback *read_cb;     // callback when EPOLLIN coming
  io_callback *write_cb;    // callback when EPOLLOUT coming
  void *rcb_args;   // extra arguments for read_cb
  void *wcb_args;   // extra arguments for write_cb
};

// 注册Timer事件
struct timer_event {
  timer_event(timer_callback *time_cb, void *data, uint16_t arg_ts, uint32_t arg_int = 0) :
    cb(time_cb), cb_data(data), ts(arg_ts), interval(arg_int)
  {}

  timer_callback *cb;
  void *cb_data;
  uint64_t ts;
  uint32_t interval;  // interval millis
  int timer_id;
};

#endif
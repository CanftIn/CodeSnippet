#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define exit_if(r, ...) if (r) { printf(__VA_ARGS__); printf("error no: %d error msg %s\n", errno, strerror(errno)); exit(1); }

void set_nonblock(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  exit_if(flags < 0, "fcntl failed");
  int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  exit_if(r < 0, "fcntl failed");
}

void update_events(int efd, int fd, int events, int op) {
  struct epoll_event ev;
  memset(&ev, 0, sizeof(ev));
  ev.events = events;
  ev.data.fd = fd;
  printf("%s fd %d events read %d write %d\n",
        op == EPOLL_CTL_MOD ? "mod" : "add", ev.events & EPOLLIN, ev.events & EPOLLOUT);
  int r = epoll_ctl(efd, op, fd, &ev);
  exit_if(r, "epoll_ctl failed");
}

void handle_accept(int efd, int fd) {
  struct sockaddr_in raddr;
  socklen_t rsz = sizeof(raddr);
  int cfd = accept(fd, (struct sockaddr *)&raddr, &rsz);
  exit_if(cfd < 0, "accept failed");
  struct sockaddr_in peer, local;
  socklen_t alen = sizeof(peer);
  int r = getpeername(cfd, (sockaddr*)&peer, &alen);
  exit_if(r < 0, "getpeername failed");
  printf("accept a connection from %s\n", inet_ntoa(raddr.sin_addr));
  set_nonblock(cfd);
  update_events(efd, cfd, EPOLLIN|EPOLLOUT, EPOLL_CTL_ADD);
}

void handle_read(int efd, int fd) {
  char buf[4096];
  int n = 0;
  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    printf("read %d bytes\n", n);
    int r = write(fd, buf, n);
    exit_if(r <= 0, "write error");
  }
  if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
    return;
  exit_if(n < 0, "read error");
  printf("fd %d closed\n", fd);
  close(fd);
}

void handle_write(int efd, int fd) {
  update_events(efd, fd, EPOLLIN, EPOLL_CTL_MOD);
}

void loop_once(int efd, int lfd, int waitms) {
  const k_max_events = 20;
  struct epoll_event active_events[100];
  int n = epoll_wait(efd, active_events, k_max_events, waitms);
  printf("epoll_wait return %d\n", n);
  for (int i = 0; i < n; ++i) {
    int fd = active_events[i].data.fd;
    int events = active_events[i].events;
    if (events & (EPOLLIN | EPOLLERR)) {
      if (fd == lfd) {
        handle_accept(efd, fd);
      } else {
        handle_read(efd, fd);
      }
    } else if (events & EPOLLOUT) {
      handle_write(efd, fd);
    } else {
      exit_if(1, "unknown event");
    }
  }
}

int main() {
  short port = 10055;
  int epollfd = epoll_create(1);
  exit_if(epollfd < 0, "epoll_create failed");
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  exit_if(listenfd < 0, "scoket failed");
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  int r = bind(listenfd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
  exit_if(r, "bind to 0.0.0.0:%d failed %d %s", port, errno, strerror(errno));
  r = listen(listenfd, 20);
  exit_if(r, "listen failed %d %s", errno, strerror(errno));
  printf("fd %d listening at %d\n", listenfd, port);
  set_nonblock(listenfd);
  update_events(epollfd, listenfd, EPOLLIN, EPOLL_CTL_ADD);
  for (;;) {
    loop_once(epollfd, listenfd, 10000);
  }
  return 0;
}
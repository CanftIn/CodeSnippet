#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

void setnonblocking(int sock) {
  int opts = fcntl(sock, F_GETFL);
  if (opts < 0) {
    perror("fcntl(socket, GETFL");
    exit(1);
  }
  opts = opts | O_NONBLOCK;
  if (fcntl(sock, F_SETFL, opts) < 0) {
    perror("fcntl(sock, SETFL, opts)");
    exit(1);
  }
}

int main(int argc, char* argv[]) {
  int port_num;
  if (argc == 2) {
    if ((port_num == atoi(argv[1])) < 0) {
      fprintf(stderr, "Usage: %s port_num\n", argv[0]);
      return 1;
    }
  } else {
    fprintf(stderr, "Usage: %s port_num\n", argv[0]);
    return 1;
  }

  // ev to regist event, events to call back event which need to deal
  struct epoll_event ev, events[20];
  int epoll_fd = epoll_create(256);
  struct sockaddr_in client_addr;
  struct sockaddr_in serv_addr;

  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

  // set socket to non blocking
  // setnonblocking(listen_fd);

  // set file fd associated with event to be processed
  ev.data.fd = listen_fd;
  ev.events = EPOLLIN | EPOLLET;
  // ev.events =  EPOLLIN;

  // regist epoll event
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  char* local_addr = "127.0.0.1";
  inet_aton(local_addr, &(serv_addr.sin_addr));

  serv_addr.sin_port = htons(port_num);
  bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  listen(listen_fd, LISTENQ);

  int maxi = 0;
  socklen_t client_len;
  for (;;) {
    // waiting for epoll event
    int nfds = epoll_wait(epoll_fd, events, 20, 500);

    // process with all event
    for (int i = 0; i < nfds; ++i) {
      if (events[i].data.fd == listen_fd) {
        int conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        if (conn_fd < 0) {
          perror("conn_fd < 0");
          exit(1);
        }
        // setnonblocking(conn_fd);
        char* str = inet_ntoa(client_addr.sin_addr);
        printf("accept a connection from \n");
        ev.data.fd = conn_fd;
        ev.events = EPOLLIN | EPOLLET;

        // regist ev
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev);
      }
      // TODO
    }
  }

  
}





#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main() {
  int s;
  struct sockaddr_in peer;
  socklen_t peer_len;
  peer_len = sizeof(peer);
  if (getpeername(s, (sockaddr*)&peer, &peer_len) == -1) {
    perror("getpeername() failed");
    return -1;
  }
  printf("Peer's IP address is: %s\n", inet_ntoa(peer.sin_addr));
  printf("Peer's port is: %d\n", (int)ntohs(peer.sin_port));
}
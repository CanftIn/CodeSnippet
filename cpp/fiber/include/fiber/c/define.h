#ifndef FIBER_C_DEFINE_H
#define FIBER_C_DEFINE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef intptr_t fiber_handle_t;

#include <errno.h>
#include <netdb.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define INVALID_SOCKET -1
typedef int socket_t;

#define FIBER_ETIMEDOUT    ETIMEDOUT
#define FIBER_ENOMEM       ENOMEM
#define FIBER_EINVAL       EINVAL
#define FIBER_ECONNREFUSED ECONNREFUSED
#define FIBER_ECONNRESET   ECONNRESET
#define FIBER_EHOSTDOWN    EHOSTDOWN
#define FIBER_EHOSTUNREACH EHOSTUNREACH
#define FIBER_EINTR        EINTR
#define FIBER_EAGAIN       EAGAIN
#define FIBER_ENETDOWN     ENETDOWN
#define FIBER_ENETUNREACH  ENETUNREACH
#define FIBER_ENOTCONN     ENOTCONN
#define FIBER_EISCONN      EISCONN
#define FIBER_EWOULDBLOCK  EWOULDBLOCK
#define FIBER_ENOBUFS      ENOBUFS
#define FIBER_ECONNABORTED ECONNABORTED
#define FIBER_EINPROGRESS  EINPROGRESS

typedef struct FIBER FIBER;

#ifdef __cplusplus
}
#endif

#endif  // FIBER_C_DEFINE_H
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#include "net.h"

#define BUFFER_SIZE 4096
#define MAX_CONNECTIONS 32

void net_send_message(net_context *ctx, int peer, net_string message) {
  write(peer, message.str, message.len); /* Making FD the peer identifier */
                                         /* wasn't that bad idea, was it? */
}

int net_connect(net_context *ctx, char *hostname) {
  int sock;
  struct sockaddr_in name;
  struct hostent *hostinfo;

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    return -1;
  }

  hostinfo = gethostbyname(hostname);
  if(hostinfo == NULL) {
    return -1;
  }

  name.sin_family = AF_INET;
  name.sin_port = htons(NET_PORT);
  name.sin_addr = *(struct in_addr *) hostinfo->h_addr;

  if(connect(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
    return -1;
  }

  FD_ZERO(&(ctx->fds)); /* Just in case */
  ctx->socket = sock;
  return sock;
}

int net_prepare_server(net_context *ctx) {
  int sock;
  struct sockaddr_in name;

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    return -1;
  }

  int enable = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
    return -2;
  }

#ifdef SO_REUSEPORT
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) {
    return -2;
  }
#endif

  name.sin_family = AF_INET;
  name.sin_port = htons(NET_PORT);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
    return -1;
  }

  if(listen(sock, MAX_CONNECTIONS) < 0) {
    return -1;
  }

  ctx->socket = sock;

  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(sock, &fds);

  ctx->fds = fds;

  return 0;
}

net_string net_wait(net_context *ctx, int *from) {
  fd_set fds = ctx->fds;
  net_string out;
  if(select(FD_SETSIZE, &fds, NULL, NULL, NULL) < 1) {
    *from = -1;
    out.len = 0;
    out.str = NULL;
    return out;
  }

  for(int i = 0; i < FD_SETSIZE; i++) {
    if(FD_ISSET(i, &fds)) {
      if(i == ctx->socket) {
        int new = accept(i, NULL, NULL);

        if(new >= 0) {
          FD_SET(new, &(ctx->fds));
        }

        *from = -2;
        out.len = 0;
        out.str = NULL;
        return out;
      }

      char buffer[BUFFER_SIZE];
      int r = read(i, buffer, BUFFER_SIZE);
      if(r <= 0) {
        net_close(ctx, i);
      } else {
        out.len = r;
        out.str = realloc(out.str, sizeof(char) * (r + 1));
        memcpy(out.str, &(buffer[0]), r);
        out.str[out.len] = '\0';
        *from = i;
        return out;
      }
    }
  }

  *from = -1;
  out.len = 0;
  out.str = NULL;
  return out;
}

void net_close(net_context *ctx, int peer) {
  close(peer); /* Actually, the identifier is just a file descriptor */
  FD_CLR(peer, &(ctx->fds));
}
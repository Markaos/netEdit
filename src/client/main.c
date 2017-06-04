#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <text.h>
#include <str.h>
#include <net.h>
#include <commands.h>

int main(int argc, char *argv[]) {
  if(argc < 3) {
    return -1;
  }

  int server;
  net_context *ctx = malloc(sizeof(net_context));
  if((server = net_connect(ctx, argv[1])) < 0) {
    fputs("Cannot connect to server!\n", stderr);
    return -2;
  }

  net_cmd cmd;
  cmd.cmd = NET_CMD_SET_NAME;
  cmd.message = net_make_str_c(argv[2]);

  net_send_message(ctx, server, net_cmd_bake_message(cmd));
  sleep(10);
  net_close(ctx, server);
}
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <text.h>
#include <str.h>
#include <net.h>
#include <commands.h>

#include "load.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    return -1;
  }

  net_context *ctx = malloc(sizeof(net_context));
  net_string msg;

  int res = net_server_load_file(ctx, net_make_str_c(argv[1]));
  if(res < 0) {
    fputs("Cannot open file!\n", stderr);
    return -2;
  }

  res = net_prepare_server(ctx);
  if(res < 0) {
    fputs("Cannot initiate server!\n", stderr);
    return -3;
  }

  while(1) {
    msg = net_wait(ctx, &res);
    if(res < 0) {
      continue;
    }

    if(msg.len < 2) {
      continue;
    }

    net_cmd cmd = net_cmd_from_message(msg);
    net_cmd c;
    switch(cmd.cmd) {
      case NET_CMD_SET_NAME:
        c.cmd = NET_CMD_NAME_CHANGED;
        c.message = net_str_from_raw(&(cmd.message.len), sizeof(size_t));
        net_str_append(&(c.message), cmd.message);
        net_str_append(&(c.message), net_str_from_raw(&res, sizeof(int)));
        net_broadcast(ctx, net_cmd_bake_message(c), -1);
        printf("Name for peer %d has been set to %s\n", res, cmd.message.str);
        break;
      default:
        printf("Unknown command: %d\n", cmd.cmd);
        break;
    }

    res = net_server_save_file(ctx, net_make_str_c(argv[2]));
    if(res < 0) {
      fputs("Cannot save file!", stderr);
      return -2;
    }
  }
}
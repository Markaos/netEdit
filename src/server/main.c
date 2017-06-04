#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <text.h>
#include <str.h>
#include <net.h>

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

    printf("Message lenght: %d; Message: %s\n", msg.len, msg.str);

    res = net_server_save_file(ctx, net_make_str_c(argv[2]));
    if(res < 0) {
      fputs("Cannot save file!", stderr);
      return -2;
    }
  }
}
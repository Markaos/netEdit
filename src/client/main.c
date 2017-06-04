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

  int server, id, quit = 0;
  net_context *ctx = malloc(sizeof(net_context));
  if((server = net_connect(ctx, argv[1])) < 0) {
    fputs("Cannot connect to server!\n", stderr);
    return -2;
  }

  net_string msg = net_wait(ctx, &server);
  net_cmd cmd = net_cmd_from_message(msg);
  if(cmd.cmd != NET_CMD_ID_ASSIGNED) {
    fputs("Server sent wrong message!\n", stderr);
    net_close(ctx, server);
    return -3;
  }
  net_str_extract_raw(&(cmd.message), &id, sizeof(int));

  cmd.cmd = NET_CMD_SET_NAME;
  cmd.message = net_make_str_c(argv[2]);
  net_send_message(ctx, server, net_cmd_bake_message(cmd));

  while(quit == 0) {
    msg = net_wait(ctx, &server);
    cmd = net_cmd_from_message(msg);
    if(cmd.cmd == NET_CMD_NAME_CHANGED) {
      size_t slen;
      net_str_extract_raw(&(cmd.message), &slen, sizeof(size_t));
      net_string name = net_substr(cmd.message, 0, slen);
      net_str_remove_from(&(cmd.message), 0, slen);
      int cid;
      net_str_extract_raw(&(cmd.message), &cid, sizeof(int));
      if(cid == id) {
        puts("Name set successfuly!");
      } else {
        printf("Peer %d has changed its name to %s\n", cid, name.str);
      }
    }
  }
  net_close(ctx, server);
}
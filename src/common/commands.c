#include <stdlib.h>
#include <string.h>
#include "commands.h"

net_cmd net_cmd_from_message(net_string message) {
  net_cmd out;
  out.message.str = malloc(sizeof(char) * message.len - sizeof(net_command));
  memcpy(&out.cmd, message.str, sizeof(net_command));
  memcpy(out.message.str, message.str + sizeof(net_command), sizeof(char) * message.len - sizeof(net_command));
  return out;
}

net_string net_cmd_bake_message(net_cmd cmd) {
  net_string out;
  out.str = malloc(sizeof(char) * cmd.message.len + sizeof(net_command) + 1);
  memcpy(out.str, &(cmd.cmd), sizeof(net_command));
  memcpy(out.str + sizeof(net_command), cmd.message.str, sizeof(char) * cmd.message.len);
  out.len = cmd.message.len + sizeof(net_command) / sizeof(char);
  return out;
}
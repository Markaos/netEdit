#ifndef NET_S_LOAD_H_
#define NET_S_LOAD_H_ 1

#include <structs.h>

int net_server_load_file(net_context *ctx, net_string filename);
int net_server_save_file(net_context *ctx, net_string filename);

#endif
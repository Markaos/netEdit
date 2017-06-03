#ifndef NET_TEXT_H_
#define NET_TEXT_H_ 1

#include "structs.h"

void net_text_append_line(net_context *ctx, net_string line);

net_string net_text_one_string(net_context *ctx);

#endif
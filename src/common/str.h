#ifndef NET_STR_H_
#define NET_STR_H_ 1

#include "structs.h"

net_string net_make_str_c(char *contents);
net_string net_make_str(char *contents, int lenght);
int net_strlen(net_string str);
void net_str_append(net_string *dst, net_string src);

#endif
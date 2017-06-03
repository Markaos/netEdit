#include <string.h>
#include <stdlib.h>

#include "str.h"

net_string net_make_str_c(char *contents) {
  net_string str;
  str.len = strlen(contents);
  str.str = contents;
  return str;
}

net_string net_make_str(char *contents, int lenght) {
  net_string str;
  str.len = lenght;
  str.str = contents;
  return str;
}

int net_strlen(net_string str) {
  return str.len;
}

void net_str_append(net_string *dst, net_string src) {
  dst->str = realloc(dst->str, sizeof(char) * (dst->len + src.len + 1));
  memcpy(dst->str + dst->len, src.str, src.len);
  dst->len += src.len;
  dst->str[dst->len] = '\0';
}
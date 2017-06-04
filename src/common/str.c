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

net_string net_substr(net_string str, off_t start, size_t len) {
  net_string out;
  out.len = len;
  out.str = malloc(sizeof(char) * (len + 1));
  memcpy(out.str, str.str + start, len);
  out.str[len] = '\0';
  return out;
}

void net_str_remove_from(net_string *str, off_t offset, size_t len) {
  str->len -= len;
  memmove(str->str + offset, str->str + offset + len, str->len - offset);
  str->str = realloc(str->str, sizeof(char) * (str->len + 1));
  str->str[str->len] = '\0';
}

void net_str_append(net_string *dst, net_string src) {
  dst->str = realloc(dst->str, sizeof(char) * (dst->len + src.len + 1));
  memcpy(dst->str + dst->len, src.str, src.len);
  dst->len += src.len;
  dst->str[dst->len] = '\0';
}

net_string net_str_from_raw(void *data, size_t len) {
  net_string out;
  out.len = len;
  out.str = malloc(len + 1);
  memcpy(out.str, data, len);
  out.str[len] = '\0';
  return out;
}

void net_str_extract_raw(net_string *str, void *data, size_t len) {
  memcpy(data, str->str, len);
  net_str_remove_from(str, 0, len);
}
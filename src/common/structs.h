#ifndef NET_STRUCTS_H_
#define NET_STRUCTS_H_ 1

#include <stdio.h>
#include <sys/types.h>

typedef struct {
  size_t len;
  char *str;
} net_string;

struct net_user;
typedef struct net_user {
  struct net_user *next;
  int id;
  net_string name;
} net_user;

typedef struct {
  int line;
  int col;
} net_pos;

typedef struct {
  net_user *user;
  net_pos pos;
} net_cursor;

struct net_text;

typedef struct net_text {
  struct net_text *prev;
  struct net_text *next;
  int id;
  net_string line;
} net_text;

typedef struct net_cmd net_cmd;
#include "commands.h"

struct net_cmd {
  unsigned short cmd;
  net_string message;
};

typedef struct {
  FILE *file;
  net_string filename;
  net_text *contents;
  net_text *last;
  int socket;
  fd_set fds;
  net_user *users;
} net_context;

#endif
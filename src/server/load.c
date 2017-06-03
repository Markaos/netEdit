#include "load.h"

#include <structs.h>
#include <text.h>
#include <str.h>

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int net_server_load_file(net_context *ctx, net_string filename) {
  FILE *fd = fopen(filename.str, "r+");
  ssize_t read;
  size_t len = 0;
  char *line = NULL;
  if (fd == NULL) {
    return -1;
  }

  ctx->filename = filename;
  ctx->file = fd;

  while ((read = getline(&line, &len, fd)) != -1) {
    net_text_append_line(ctx, net_make_str(line, read));
  }
  return 0;
}

int net_server_save_file(net_context *ctx, net_string filename) {
  FILE *fd = NULL;
  int written = 0, total = 0, towrite = 0;
  if (!strncmp(ctx->filename.str, filename.str, filename.len)) {
    fd = ctx->file;
  } else {
    fd = fopen(filename.str, "w");
  }

  if(fd == NULL) {
    return -1;
  }

  net_string s = net_text_one_string(ctx);
  while(total < s.len) {
    towrite = 4096;
    if(s.len - total < 4096) {
      towrite = s.len - total;
    }

    if((written = fwrite(s.str + total, 1, towrite, fd)) == -1) {
      return -1;
    }

    total += written;
  }
  
  fflush(fd);
}
#include "text.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void net_text_append_line(net_context *ctx, net_string line) {
  net_text *text = malloc(sizeof(net_text));
  if (ctx->last != NULL) {
    ctx->last->next = text;
    text->id = ctx->last->id + 1;
  } else {
    text->id = 0;
  }
  text->prev = ctx->last;
  text->line = line;
  ctx->last = text;

  if(ctx->contents == NULL) {
    ctx->contents = text;
  }
}

net_string net_text_one_string(net_context *ctx) {
  net_string out;
  out.len = 0;
  out.str = NULL;
  net_text *text = ctx->contents;

  if (text == NULL) {
    puts("TROLL");
  }

  while (text != NULL) {
    net_str_append(&out, text->line);
    text = text->next;
  }

  return out;
}
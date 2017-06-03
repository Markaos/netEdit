#ifndef NET_TEXT_H_
#define NET_TEXT_H_ 1

#include "structs.h"

/*
 * Function: net_text_append_line
 * ------------------------------
 * Append line to the end of text in given context
 * 
 * line: line to append
 */
void net_text_append_line(net_context *ctx, net_string line);

/*
 * Function: net_text_one_string
 * -----------------------------
 * Converts text in given contexts to one long string
 *
 * returns: string representing contents of current context
 */
net_string net_text_one_string(net_context *ctx);

#endif
#ifndef NET_STR_H_
#define NET_STR_H_ 1

#include "structs.h"

/*
 * Function: net_make_str_c
 * ------------------------
 * Make net_string from classic zero-delimited C string. Memory pointed to by
 * "contents" will be used for net_string
 *
 * contents: C string to be wrapped
 *
 * returns: net_string representing the string
 */
net_string net_make_str_c(char *contents);

/*
 * Function: net_make_str
 * ----------------------
 * Make net_string from classic C string with known lenght. Memory pointed to
 * by "contents" will be used in net_string
 *
 * contents: C string to be wrapped
 * lenght: lenght of the string
 *
 * returns: net_string representing the string
 */
net_string net_make_str(char *contents, int lenght);

/*
 * Function: net_strlen
 * --------------------
 * Get lenght of given string
 *
 * str: string to be meassured
 *
 * returns: lenght of given string
 */
int net_strlen(net_string str);

/*
 * Function: net_str_append
 * ------------------------
 * Append one string to another
 *
 * dst: string to append to
 * src: string to be appended
 */
void net_str_append(net_string *dst, net_string src);

#endif
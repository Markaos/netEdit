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
 * Function: net_substr
 * --------------------
 * Make a substring from string (original string will be left intact)
 *
 * str: string to shorten
 * start: where the new string should start
 * len: how long the new string should be
 *
 * returns: new string
 */
net_string net_substr(net_string str, off_t start, size_t len);

/*
 * Function: net_str_remove_from
 * -----------------------------
 * Remove _len_ bytes from string, starting at offset _offset_, adjacent string
 * parts will be joined
 *
 * str: string to remove data from
 * offset: where data to be deleted start
 * len: how long the region being deleted is
 */
void net_str_remove_from(net_string *str, off_t offset, size_t len);

/*
 * Function: net_str_append
 * ------------------------
 * Append one string to another
 *
 * dst: string to append to
 * src: string to be appended
 */
void net_str_append(net_string *dst, net_string src);

/*
 * Function: net_str_from_raw
 * --------------------------
 * Save raw data into net_string
 *
 * data: data to be saved
 * len: lenght of data in bytes
 *
 * returns: net_string representing the data
 */
net_string net_str_from_raw(void *data, size_t len);

/*
 * Function: net_str_extract_raw
 * -----------------------------
 * Extract raw data from string (data will be deleted from the string)
 *
 * str: string from which data should be exracted
 * data: pointer to allocated memory where extracted data should be stored
 * len: number of bytes to extract
 */
void net_str_extract_raw(net_string *str, void *data, size_t len);

#endif
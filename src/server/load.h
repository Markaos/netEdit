#ifndef NET_S_LOAD_H_
#define NET_S_LOAD_H_ 1

#include <structs.h>

/*
 * Function: net_server_load_file
 * ------------------------------
 * Load file from filesystem and save its contents to given context
 *
 * filename: name of the file you want to load, dummy
 *
 * returns: zero on success, non-zero value otherwise
 */
int net_server_load_file(net_context *ctx, net_string filename);

/*
 * Function: net_server_save_file
 * ------------------------------
 * Save contents of given context to file
 *
 * filename: filename under which the contents should be saved
 *
 * returns: zero on success, non-zero on failure
 */
int net_server_save_file(net_context *ctx, net_string filename);

#endif
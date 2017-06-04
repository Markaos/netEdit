#ifndef NET_NET_H_
#define NET_NET_H_ 1

#include "structs.h"

#define NET_PORT 1234

/*
 * Function: net_send_message
 * --------------------------
 * Send message to peer
 *
 * to: peer identifier obtained by calling net_connect() or net_listen()
 * message: message to be sent
 */
void net_send_message(net_context *ctx, int to, net_string message);

/*
 * Function: net_connect
 * ---------------------
 * Connect to server
 *
 * hostname: server hostname or IP address
 *
 * returns: peer identifier to be used with net_send_message() or net_close()
 *          or -1 on failure
 */
int net_connect(net_context *ctx, char *hostname);

/*
 * Function: net_prepare_server
 * ----------------------------
 * Prepare server socket for its job
 *
 * returns: zero on success, -1 on failure
 */
int net_prepare_server(net_context *ctx);

/*
 * Function: net_wait
 * ------------------
 * Wait for message from any peer
 *
 * from: pointer to integer to be filled with peer identifier
 *
 * returns: message from peer identified by "from"
 */
net_string net_wait(net_context *ctx, int *from);

/*
 * Function: net_close
 * -------------------
 * Close connection to the peer
 * 
 * peer: identifier of peer whose connection is to be closed
 */
void net_close(net_context *ctx, int peer);

/*
 * Function: net_broadcast
 * -----------------------
 * Send message to all peers (server-only)
 * 
 * message: message to be sent
 * except: message won't be sent to this peer; use -1 to send to all
 */
void net_broadcast(net_context *ctx, net_string message, int except);

#endif
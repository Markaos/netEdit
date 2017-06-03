#ifndef NET_NET_H_
#define NET_NET_H_ 1

/*
 * Function: net_send_message
 * --------------------------
 * Send message to peer
 *
 * to: peer identifier obtained by calling net_connect() or net_listen()
 * message: message to be sent
 */
void net_send_message(net_context *ctx, int to, net_text message);

/*
 * Function: net_connect
 * ---------------------
 * Connect to server
 *
 * hostname: server hostname or IP address
 *
 * returns: peer identifier to be used with net_send_message() or net_close()
 */
int net_connect(net_context *ctx, char *hostname);

/*
 * Function: net_prepare_server
 * ----------------------------
 * Prepare server socket for its job
 */
int net_prepare_server(net_context *ctx);

/*
 * Function: net_wait
 * ------------------
 * Wait for message from any peer
 */
net_text net_wait(net_context *ctx);

#endif
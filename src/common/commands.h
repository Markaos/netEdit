#ifndef NET_COMMANDS_H_
#define NET_COMMANDS_H_ 1

#include "structs.h"

typedef unsigned short net_command;

/*    0x0000 - 0x006f    */
/*    User management    */
#define NET_CMD_SET_NAME      0x0000
#define NET_CMD_MOVE_CURSOR   0x0001
#define NET_CMD_ID_ASSIGNED   0x0002
#define NET_CMD_ADD_USER      0x0003
#define NET_CMD_USER_ADDED    0x0004
#define NET_CMD_NAME_CHANGED  0x0005

/*    0x0070 - 0x00ff    */
/*   Standard  replies    */
#define NET_CMD_ACK           0x0070

/*    0x0100 - 0x01ff    */
/*   Text modification   */

/*    0x0100 - 0x010f    */
/*    Insert commands    */
#define NET_CMD_INSERT_LINE   0x0100
#define NET_CMD_INSERT_AT     0x0101

/*    0x0110 - 0x011f    */
/*    Remove commands    */
#define NET_CMD_REMOVE_LINE   0x0110
#define NET_CMD_REMOVE_AT     0x0111

/*
 * Function: net_cmd_from_message
 * ------------------------------
 * Make net_cmd from message
 */
net_cmd net_cmd_from_message(net_string message);

/*
 * Function: net_cmd_bake_message
 * ------------------------------
 * Create net_string from net_cmd
 */
net_string net_cmd_bake_message(net_cmd cmd);

#endif
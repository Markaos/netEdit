#ifndef NET_NET_H_
#define NET_NET_H_ 1

void net_send_message(int to, net_text message);
void net_send_command(int to, short command, net_text payload);
int net_connect(char *hostname);
int net_listen();
net_text net_wait();

#endif
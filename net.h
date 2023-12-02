#ifndef NET_H
#define NET_H

// this program will be in using tcp/ip 
int create_socket(struct addrinfo *p, int *sockfd);
int get_socket(char *port);

#endif

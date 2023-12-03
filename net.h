#ifndef NET_H
#define NET_H

// this program will be in using tcp/ip
int create_socket(struct addrinfo *p, int *sockfd, struct addrinfo **selected);
int get_socket(int *sockf, struct addrinfo *res, struct addrinfo **selected);
int get_server_socket(char *port);
int get_client_socket(char *targethost, char *port);

#endif

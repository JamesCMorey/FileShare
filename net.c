#include <sys/types.h>
#include <sys/socket.h>
#include<netdb.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "net.h"


int create_socket(struct addrinfo *p, int *sockfd)
{
	int on = 1;

	if ((*sockfd = socket(p->ai_family, p->ai_socktype,
						p->ai_protocol)) == -1) {
		perror("socket");
		return -1;
	}

/* potential security risk */
#ifndef PROD
	if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR,
						&on, sizeof on) == -1) {
		perror("setsockopt");
		return -2;
	}
#endif

	if (bind(*sockfd, p->ai_addr, p->ai_addrlen) == -1) {
		perror("bind");
		return -3;
	}

	return 0;
}

/* returns a  */
int get_socket (char *port)
{
	struct addrinfo hints, *res, *p;
	int sockfd, rv = 0;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, port, &hints, &res)) != 0) {
		/* this error handling is special due to getaddrinfo */
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rv));
		exit(1);
	}

	for (p = res; p != NULL; p = p->ai_next) {
		if (create_socket(p, &sockfd) < 0)
			continue;

		break;
	}

	freeaddrinfo(res);

	return sockfd;
}


#include <sys/types.h>
#include <sys/socket.h>
#include<netdb.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "net.h"


int create_socket(struct addrinfo *p, int *sockfd, struct addrinfo **selected)
{
	int on = 1;
	if (selected != NULL)
		*selected = p;


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
		return -1;
	}
#endif
/*
	if (bind(*sockfd, p->ai_addr, p->ai_addrlen) == -1) {
		perror("bind");
		return -1;
	}
*/
	return 0;
}

int get_socket(int *sockfd, struct addrinfo *res, struct addrinfo **selected)
{
	int rv;

	for (; res != NULL; res = res->ai_next) {
		if ((rv = create_socket(res, sockfd, selected)) < 0)
			continue;

		return rv;
	}

	return rv;
}

int get_server_socket (char *port)
{
	struct addrinfo hints, *res, *p, *selected;
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

	get_socket(&sockfd, res, &selected);
	if (bind(sockfd, selected->ai_addr, selected->ai_addrlen) == -1) {
		perror("bind");
		return -1;
	}

	freeaddrinfo(res);
	return sockfd;
}

int get_client_socket(char *targethost, char *port)
{
	int sockfd, rv;
	struct addrinfo hints, *res, *selected;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(targethost, port, &hints, &res)) == -1) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}

	if ((rv = get_socket(&sockfd, res, &selected)) == -1) {
		// TODO: Write code to handle a failed get
	}

	if (connect(sockfd, selected->ai_addr, selected->ai_addrlen) == -1) {
		perror("connect");
		return -1;
	}

	freeaddrinfo(res);

	return sockfd;
}

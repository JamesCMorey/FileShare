#ifndef CLIENT_H
#define CLIENT_H

void *client_init();

struct target {
	char *hostname;
	char *port;
};

#endif

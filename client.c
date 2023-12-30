#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "net.h"
#include "thread.h"
#include "client.h"

#define MESSAGESIZE 4096

void *client_init(struct target *target_host)
{

	while (lock)
		;

	int connector;
	char message[MESSAGESIZE] = "Hello, me.";

	// TODO: fix clientsocket "bind: Address already in use"
	// probably because the socket is being bound to the same
	// port that the listener is on before being connected
	// to the same port the listener is on
	// client socket is binding and sending a message to the listener,
	// which is on the same exact port as the client socket
	connector = get_client_socket(target_host->hostname, target_host->port);
	send(connector, message, sizeof message, 0);
	puts("Message sent.");

	close(connector);
	pthread_exit(0);
}


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "net.h"
#include "server.h"

#define BACKLOG 10
#define PORT "10000"
#define BUFFERSIZE 4096

int server_init()
{
	int listener, client;
	char buffer[4096];

	listener = get_server_socket(PORT);

	if (listen(listener, BACKLOG) == -1) {
		perror("listener");
		return -1;
	}

	puts("starting listener...");

	while (1) {
		client = accept(listener, NULL, NULL);

		puts("new connection");
		recv(client, buffer, BUFFERSIZE, 0);

		printf("msg: %s\n", buffer);

		close(client);
		close(listener);
		exit(0);
	}

	return 0;
}

int main()
{
	server_init();
	return 0;
}

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "net.h"

#define MESSAGESIZE 4096

int client_init()
{
	int connector;
	char message[MESSAGESIZE] = "Hello, me.";
	printf("message: %s\n", message);

	connector = get_client_socket("127.0.0.1", "10000");

	puts("before send");

	send(connector, message, sizeof message, 0);	// make sure this is
							// working
	puts("after send");

	close(connector);

	return 0;
}

int main()
{
	client_init();
	return 0;
}

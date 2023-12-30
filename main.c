#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "thread.h"
#include "server.h"
#include "client.h"
#include "display.h"


int main()
{
	pthread_t server_t, client_t;
	struct target *homeserver = malloc(sizeof(struct target));
	// ip of dev homeserver
	homeserver->hostname = "192.168.50.22";
	homeserver->port = "10000";

	pthread_create(&server_t, NULL, server_init, NULL);
	pthread_create(&client_t, NULL, client_init, homeserver);

	// do not use &pthread_t for pthread_join
	pthread_join(client_t, NULL);
	pthread_join(server_t, NULL);
	menu();

	return 0;
}

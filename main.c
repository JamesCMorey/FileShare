#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "thread.h"
#include "server.h"
#include "client.h"


int main ()
{
	pthread_t server_t, client_t;
	struct target *homeserver = malloc(sizeof(struct target));

	homeserver->hostname = "192.168.50.190";
	homeserver->port = "10000";

	pthread_create(&server_t, NULL, server_init, NULL);
	pthread_create(&client_t, NULL, client_init, homeserver);

	pthread_join(&server_t, NULL);


	puts("complete"); // this doesn't run for some reason
	return 0;
}

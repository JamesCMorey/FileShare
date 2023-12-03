#include <stdio.h>
#include <pthread.h>
#include "thread.h"
#include "server.h"
#include "client.h"


int main ()
{
	pthread_t server_t, client_t;

	pthread_create(&server_t, NULL, server_init, NULL);
	pthread_create(&client_t, NULL, client_init, NULL);

	pthread_join(&server_t, NULL);


	puts("complete"); // this doesn't run for some reason
	return 0;
}

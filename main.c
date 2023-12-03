#include <stdio.h>
#include "server.h"
#include "client.h"

#ifndef PROD
#include "net.h"
#endif

int main ()
{
	//server_init();
	printf("socket reserved: %d\n", get_server_socket("10000"));
	return 0;
}

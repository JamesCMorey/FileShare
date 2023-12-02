#include <stdio.h>
#include <unistd.h>
#include "net.h"

#define BACKLOG 10
#define PORT "10000"

int main ()
{
	int sockfd;
	sockfd = get_socket(PORT);

	printf("Socket Reserved: %d\n", sockfd);
	close(sockfd);

	return 0;
}

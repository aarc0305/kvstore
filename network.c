#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "network.h"

#define BACKLOG 10
/* 
	Create the TCP socket using the address and the port.
	After that, return the file descriptor of the socket.
*/
int initTCPServer(char* address, int port) {

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( fd < 0) {
		printf("There are something wrong when creating socket\n");
	}
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, "127.0.0.1", &(saddr.sin_addr)) < 0) {
		printf("inet_pton failed!\n");
	}
	saddr.sin_port = htons(port);
	printf("saddr.sin_port: %d\n", saddr.sin_port);
	if (bind(fd, (struct sockaddr*) &saddr, sizeof(struct sockaddr_in)) == -1) {
		printf("Fail to bind the address!\n");
	}
	if (listen(fd, BACKLOG) < 0) {
		printf("Fail to listen.\n");
	}
	return fd;
}

void acceptTCPHandler(Eventloop* el, int fd, void* data) {

    int cfd = accept(fd, NULL, NULL);
    printf("There is one client: %d\n", cfd);

    
    // Check if the number of clients is larger than the max of clients.
    (server -> current_clients_count)++;
    if (server -> current_clients_count > server -> max_clients_count) {
    	printf("There could not be more clients with this server.\n");
    	return;
    }

    // Create the client and add the cfd to the eventloop.
    Client* client = malloc(sizeof(Client));
    addEvent(el, cfd, EL_READABLE, queryCommandHandler, client);
    return;

}

void queryCommandHandler(Eventloop* el, int fd, void* data) {
	Client* client = (Client*) data;
	printf("This is queryCommandHandler\n");
	char buff[1024] = {0};
	while(recvfrom(fd, buff, 1, 0, NULL, NULL) > 0) {
      printf("%s\n", buff);
    }
    Ds_string* ds_string = Ds_string_new(buff);
    
}
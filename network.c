#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include "network.h"
#include "compiler.h"

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

    /*
    	1. Create the client
    	2. Add the client to the client table of the server
    	3. Add the cfd to the eventloop.
    */ 
    if (server -> current_clients_count >= server -> max_clients_count) {
    	printf("The server is full of clients!\n");
    	return;
    }
    Client* new_client = (server -> clients)[server -> current_clients_count] = malloc(sizeof(Client));
    new_client -> current_database = (server -> databases)[0];
    addEvent(el, cfd, EL_READABLE, queryCommandHandler, new_client);
    return;

}

void queryCommandHandler(Eventloop* el, int fd, void* data) {
	Client* client = (Client*) data;
	char buff[1024] = {0};

	// Set the file descriptor to non-blocking.
	int flags= fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	// Read the command from the client socket
	while(recvfrom(fd, buff, 1024, 0, NULL, NULL) > 0) {
	}

    Ds_string* ds_string = Ds_string_new(buff);

    // store the command in the querybuf of the client and process it.
    client -> queryBuf = ds_string;
    if (ds_string -> length <= 0) {
    	// nop
    } else {
        // Use the compiler to parse the input command
        tokenizer(ds_string);
        parser(client);
    }
}


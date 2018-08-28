#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "network.h"

// Global variable
struct Server* server;

void initServer() {

	server = malloc(sizeof(*server));

	/*
		By default, the maximum number of clients is 100.
	*/
	server -> max_clients_count = 0;
	server -> current_clients_count = 0;

	/* 
		By default, the binding address is 127.0.0.1 and the 
		binding port is 3000.
	*/
	server -> bind_address_count = 1;
	(server -> bind_addresses)[0] = "127.0.0.1";
	server -> bind_port = 3000;

	server -> el = createEventloop(server -> bind_address_count);
	for (int i = 0; i < server -> bind_address_count; i++) {
		(server -> serverfds)[i] = initTCPServer((server -> bind_addresses)[i], server -> bind_port);
	}

	// Add the event of the serverfd to the eventloop
	for (int i = 0; i < (server -> bind_address_count); i++) {
		addEvent(server -> el, (server -> serverfds)[i], EL_READABLE, acceptTCPHandler, NULL);
	}
}

int main(int argc, char* argv[]) {

	printf("This is a simple kvstore server!\n");
	printf("Initiate the server.......\n");
	initServer();
	while(1) {
		processEvent(server -> el);
	}

}
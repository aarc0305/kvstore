#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "server.h"
#include "network.h"

// Global variable
struct Server* server;

// Signal handler
static void ctrlCSignalHandler() {

	printf("Ctrl C signal handling ......\n");
	exit(0);
	
}

void initServer() {

	server = malloc(sizeof(*server));

	/*
		By default, the maximum number of clients is 100.
	*/
	server -> max_clients_count = 100;
	server -> current_clients_count = 0;

	/* 
		By default, the binding address is 127.0.0.1 and the 
		binding port is 3000.
	*/
	server -> bind_address_count = 1;
	(server -> bind_addresses)[0] = "127.0.0.1";
	server -> bind_port = 3000;

	server -> el = createEventloop(server -> max_clients_count);
	for (int i = 0; i < server -> bind_address_count; i++) {
		(server -> serverfds)[i] = initTCPServer((server -> bind_addresses)[i], server -> bind_port);
	}

	// Add the event of the serverfd to the eventloop
	for (int i = 0; i < (server -> bind_address_count); i++) {
		addEvent(server -> el, (server -> serverfds)[i], EL_READABLE, acceptTCPHandler, NULL);
	}

}

void setSignalHandler() {

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ctrlCSignalHandler;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		printf("Sigaction fails!\n");
	}

}

int main(int argc, char* argv[]) {

	printf("This is a simple kvstore server!\n");
	printf("Initiate the server.......\n");
	setSignalHandler();
	initServer();
	while(1) {
		processEvent(server -> el);
	}

}
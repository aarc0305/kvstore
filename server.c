#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "server.h"
#include "command_handler.h"

// Global variable
struct Server* server;

// All of the commands are stored in this command table
KVCommand commad_table[] = {
	{"set", setHandler},
	{"get", getHandler},
	{"update", updateHandler},
	{"delete", deleteHandler},
	{"select", NULL}
};

// Signal handler
static void ctrlCSignalHandler() {

	printf("Ctrl C signal handling ......\n");
	exit(0);
	
}

void initServer() {

	server = malloc(sizeof(*server));
	
	/*
		Initialize the database:
		By default, the number of database is 16 
		and the size of each database is 4.
	*/
	server -> num_database = 16;
	server -> databases = malloc(sizeof(KVDatabase*) * (server -> num_database));
	for (int i = 0; i < server -> num_database; i++) {
		(server -> databases)[i] = malloc(sizeof(KVDatabase));
		(server -> databases)[i] -> dict = Dictionary_new(4);
	}
	
	/*
		By default, the maximum number of clients is 100.
	*/
	server -> max_clients_count = 100;
	server -> current_clients_count = 0;
	server -> clients = malloc(sizeof(Client*) * server -> max_clients_count);

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

// Return NULL if there are any errors.
KVCommand* lookupCommand(char* commandName) {
	KVCommand* result = NULL;
	size_t table_size = sizeof(commad_table) / sizeof(KVCommand);
	for (int i = 0; i < table_size; i++) {
		if (strcmp(commandName, commad_table[i].commandName) == 0) {
			result = &(commad_table[i]);
			break;
		}
	}
	return result;
}

// Return -1 if there are any errors and return 0 if successful.
int processCommand(Client* client) {
	if (client -> argc == 0) {
		printf("There are no commands to be executed!\n");
		return -1;
	}
	KVCommand* command = lookupCommand((client -> argv)[0]);
	(command -> commanHandler)(client);
	return 0;
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
#ifndef SERVER_H
#define SERVER_H
#include "eventloop.h"
#include "network.h"
#include "datastructure.h"

#define MAX_BIND_COUNT 100

typedef struct Server Server;
struct Server {
	Eventloop* el;
	int bind_address_count;
	char* bind_addresses[MAX_BIND_COUNT];
	int bind_port;
	int serverfds[MAX_BIND_COUNT];
	int current_clients_count;
	int max_clients_count;
};

typedef struct Client Client;
struct Client {
	Ds_string* queryBuf;
	int argc;
	char* argv;
};

// Extern declaarations
extern struct Server* server;

void initServer();

#endif
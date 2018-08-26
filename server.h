#ifndef SERVER_H
#define SERVER_H
#include "eventloop.h"
#include "network.h"

#define MAX_BIND_COUNT 100

typedef struct Server Server;
struct Server {
	Eventloop* el;
	int bind_address_count;
	char* bind_addresses[MAX_BIND_COUNT];
	int bind_port;
	int serverfds[MAX_BIND_COUNT];
};

void initServer();

#endif
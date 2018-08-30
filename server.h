#ifndef SERVER_H
#define SERVER_H
#include "eventloop.h"
#include "network.h"
#include "datastructure.h"

#define MAX_BIND_COUNT 100
#define MAX_CLIENTS_COUNT 100

typedef struct Server Server;
typedef struct Client Client;
typedef struct KVCommand KVCommand;
typedef struct KVDatabase KVDatabase;

typedef void KVCommandHandler(Client* client);

struct Server {
	Eventloop* el;
	int bind_address_count;
	char* bind_addresses[MAX_BIND_COUNT];
	int bind_port;
	int serverfds[MAX_BIND_COUNT];
	int current_clients_count;
	int max_clients_count;
	Client* clients[MAX_CLIENTS_COUNT];

};

typedef struct Client Client;
struct Client {
	Ds_string* queryBuf;
	int argc;
	char* argv;
	KVCommand* command;
};

struct KVDatabase {

};

struct KVCommand {
	char* commandName;
	KVCommandHandler* commanHandler;
};

// Extern declaarations
extern struct Server* server;

void initServer();
void setSignalHandler();

#endif
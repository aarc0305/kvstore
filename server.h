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

	// The network information of the server
	int bind_address_count;
	char* bind_addresses[MAX_BIND_COUNT];
	int bind_port;
	int serverfds[MAX_BIND_COUNT];

	// The information of the connected clients
	int current_clients_count;
	int max_clients_count;
	Client** clients;

	// The information of databases
	KVDatabase** databases;
	int num_database;

	// This the period of the server time handler
	int period;

};

typedef struct Client Client;
struct Client {
	Ds_string* queryBuf;
	int argc;
	char** argv;
	KVCommand* command;
	KVDatabase* current_database;
};

struct KVDatabase {
	Dictionary* dict;
};

struct KVCommand {
	char* commandName;
	KVCommandHandler* commanHandler;
};

// Extern declaarations
extern struct Server* server;
extern KVCommand commad_table[];

void initServer();
void serverTimeHandler(Eventloop* el, void* data);
KVCommand* lookupCommand(char* commandName);
int processCommand(Client* client);
void setSignalHandler();

#endif
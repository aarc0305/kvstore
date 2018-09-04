#include <stdio.h>
#include <stdlib.h>
#include "command_handler.h"

void setHandler(Client* client) {
	printf("This is a setHandler\n");
	KVDatabase* current_database = client -> current_database;
}

void getHandler(Client* client) {
	printf("This is a getHandler\n");
}

void updateHandler(Client* client) {
	printf("This is a updateHandler\n");
}

void deleteHandler(Client* client) {
	printf("This is a deleteHandler\n");
}

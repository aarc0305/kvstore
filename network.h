#ifndef NETWORK_H
#define NETWORK_H
#include "server.h"

int initTCPServer(char* address, int port);
void acceptTCPHandler();

#endif
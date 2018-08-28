#ifndef NETWORK_H
#define NETWORK_H
#include "server.h"

int initTCPServer(char* address, int port);
void acceptTCPHandler(Eventloop* el, int fd, void* data);
void queryCommandHandler(Eventloop* el, int fd, void* data);

#endif
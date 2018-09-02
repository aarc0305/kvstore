#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include "server.h"

void setHandler(Client* client);
void getHandler(Client* client);
void updateHandler(Client* client);
void deleteHandler(Client* client);

#endif
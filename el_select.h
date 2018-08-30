#ifndef EL_SELECT_H
#define EL_SELECT_H
#include "eventloop.h"

void apiCreate(Eventloop* el);
void apiAddEvent(Eventloop* el, int fd, int mask);
int apiPoll(Eventloop* el);

#endif
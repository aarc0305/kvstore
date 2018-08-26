#ifndef EL_KQUEUE_H
#define EL_KQUEUE_H
#include "eventloop.h"

void apiCreate(Eventloop* el);
void apiAddEvent(Eventloop* el, int fd, int mask);
int apiPoll(Eventloop* el);

#endif
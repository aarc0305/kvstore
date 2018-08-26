#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include "el_kqueue.h"

typedef struct Api_state Api_state;
struct Api_state {
	int kqfd;
	struct kevent *events;
};

void apiCreate(Eventloop* el) {
	printf("Create a kqueue!\n");
	int kqfd = kqueue();
	Api_state* state = el -> state = malloc(sizeof(Api_state));
	state -> events = malloc(sizeof(struct kevent) * (el -> setSize));
	state -> kqfd = kqfd;
}

void apiAddEvent(Eventloop* el, int fd, int mask) {

	struct kevent ke;

	/* 
		Initiate the kevent accordidng to the mask
		mask: 
			EL_READABLE --> EVFILT_READ
			EL_WRITABLE --> EVFILT_WRITE
	*/
	if (mask == EL_READABLE) {
		EV_SET(&ke, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}
	if (mask == EL_WRITABLE) {
		EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}

	// Register the ke to the kqueue
	Api_state* state = el -> state;
	kevent(state -> kqfd, &ke, 1, NULL, 0, NULL);
}

int apiPoll(Eventloop* el) {
	Api_state* state = el -> state;
	int kqfd = state -> kqfd;
	struct kevent* events = state -> events;
	int evtNums = kevent(state -> kqfd, NULL, 0, events, el -> setSize, NULL);

	for (int i = 0; i < evtNums; i++) {
		(el -> fired_events)[i] -> fd = events[i].ident;
		if (events[i].filter == EVFILT_READ) {
			(el -> fired_events)[i] -> mask = EL_READABLE;
		}
		if (events[i].filter == EVFILT_WRITE) {
			(el -> fired_events)[i] -> mask = EL_WRITABLE;
		}
	}
	return evtNums;
}
#include <stdio.h>
#include <stdlib.h>
#include "el_kqueue.h"
#include "eventloop.h"

Eventloop* createEventloop(int setSize) {
	
	Eventloop* el = malloc(sizeof(struct Eventloop));
	el -> setSize = setSize;

	// Create the setSize events for the eventloop
	for (int i = 0; i < MAX_EVNET_COUNT; i++) {

		// El_event
		(el -> events)[i] = malloc(sizeof(struct El_event));
		(el -> events)[i] -> mask = EL_NONE;

		// El_fired_event
		el -> fired_events[i] = malloc(sizeof(struct El_fired_event));
	}
	apiCreate(el);
	return el;
}

void addEvent(Eventloop* el, int fd, int mask, event_handler *handler, void* data) {
	el -> events[fd] -> mask = mask;
	el -> events[fd] -> data = data;
	if (mask & EL_READABLE) {
		el -> events[fd] -> r_handler = handler;
	}
	if (mask & EL_WRITABLE) {
		el -> events[fd] -> w_handler = handler;
	}
	apiAddEvent(el, fd, mask);
}

void processEvent(Eventloop* el) {
	int evtNum = apiPoll(el);
	for (int i = 0; i < evtNum; i++) {
		int fired_fd = (el -> fired_events)[i] -> fd;
		void* data = (el -> events[fired_fd]) -> data;
		printf("Fired fd: %d\n", fired_fd);
		if ((el -> fired_events)[i] -> mask == EL_READABLE) {
			(el -> events[fired_fd]) -> r_handler(el, fired_fd, data);
		}
	}
}
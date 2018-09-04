#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "el_select.h"
#include "eventloop.h"
#include "server.h"

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

	// Initialize the time event related attributes
	el -> max_time_event_id = 0;
	el -> time_event_head = NULL;

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

void addTimeEvent(Eventloop* el, time_event_handler* handler, long time_offset) {
	El_time_event* time_event = malloc(sizeof(El_time_event));
	time_event -> id = (el -> max_time_event_id)++;
	/* 
		Get the current time and add the time_offset to the current time.
		By doing so, this time event is expected to be executed in "time_offset" seconds.
	*/
	time_t now = time(0);
	time_event -> when_sec = now + time_offset;

	time_event -> handler = handler;

	// Add the event to the head of double linked-list of the eventloop.
	time_event -> next = el -> time_event_head;
	time_event -> previous = NULL;
	if (time_event -> next != NULL) {
		time_event -> next -> previous = time_event;
	}
	el -> time_event_head = time_event;

}

void processEvent(Eventloop* el) {

	// process the time events
	time_t now = time(0);
	El_time_event* time_event = el -> time_event_head;
	while (time_event) {
		if ((time_event -> when_sec) <= now) {
			// This time event is triggered.
			(time_event -> handler)(el, NULL);
			time_event -> when_sec = now + (server -> period);
		}
		time_event = time_event -> next;
	}
	
	// process the gerneral events
	int evtNum = apiPoll(el);
	for (int i = 0; i < evtNum; i++) {
		int fired_fd = (el -> fired_events)[i] -> fd;
		void* data = (el -> events[fired_fd]) -> data;
		if ((el -> fired_events)[i] -> mask == EL_READABLE) {
			(el -> events[fired_fd]) -> r_handler(el, fired_fd, data);
		}
	}
}
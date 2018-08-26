#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#define EL_NONE 0
#define EL_READABLE 1
#define EL_WRITABLE 2

#define MAX_EVNET_COUNT 200
#define MAX_FIRED_EVENT_COUNT 200

typedef void event_handler();

typedef struct El_event El_event;
struct El_event {
	int mask;
	int fd;
	event_handler *r_handler;
	event_handler *w_handler;
};

typedef struct El_fired_event El_fired_event;
struct El_fired_event {
	int fd;
	int mask;
};

typedef struct Eventloop Eventloop;
struct Eventloop {
	void* state;
	int setSize;
	El_event* events[MAX_EVNET_COUNT];
	El_fired_event* fired_events[MAX_FIRED_EVENT_COUNT];
};

Eventloop* createEventloop(int setSize);
void addEvent(Eventloop* el, int fd, int mask, event_handler *handler);
void processEvent(Eventloop* el);

#endif
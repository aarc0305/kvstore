#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#define EL_NONE 0
#define EL_READABLE 1
#define EL_WRITABLE 2

#define MAX_EVNET_COUNT 200
#define MAX_FIRED_EVENT_COUNT 200

typedef struct Eventloop Eventloop;
typedef struct El_event El_event;
typedef struct El_fired_event El_fired_event;
typedef struct El_time_event El_time_event;

typedef void event_handler(Eventloop* el, int fd, void* data);
typedef void time_event_handler(Eventloop* el, void* data);

struct El_event {
	int mask;
	int fd;
	event_handler *r_handler;
	event_handler *w_handler;
	// Store the data which would be processed later, such as the pointer of client.
	void* data;
};

struct El_fired_event {
	int fd;
	int mask;
};

struct El_time_event {
	int id;
	long when_sec;
	long when_msec;
	time_event_handler* handler;
	/* 
		The sets of time events would be stored in a datastructure of double linked-list.
		Therefore, there are "next" and "previous" nodes in a time event.
	*/
	El_time_event* next;
	El_time_event* previous;
};

typedef struct Eventloop Eventloop;
struct Eventloop {

	// The general event related attributes
	void* state;
	int setSize;
	El_event* events[MAX_EVNET_COUNT];
	El_fired_event* fired_events[MAX_FIRED_EVENT_COUNT];

	// The time event related attributes
	int max_time_event_id;
	El_time_event* time_event_head;

};

Eventloop* createEventloop(int setSize);
void addEvent(Eventloop* el, int fd, int mask, event_handler *handler, void* data);
void addTimeEvent(Eventloop* el, time_event_handler* handler, long time_offset);
void processEvent(Eventloop* el);

#endif
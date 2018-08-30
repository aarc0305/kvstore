#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>
#include "el_select.h"

typedef struct Api_state Api_state;
struct Api_state {
	fd_set* readfds;
	fd_set* writefds;
	fd_set* _readfds;
	fd_set* _writefds;
};

void apiCreate(Eventloop* el) {
	
	el -> state = malloc(sizeof(Api_state));
	Api_state* state = (Api_state*) el -> state;

	// Initialize the readfds and writefds
	state -> readfds = malloc(sizeof(fd_set));
	state -> writefds = malloc(sizeof(fd_set));
	state -> _readfds = malloc(sizeof(fd_set));
	state -> _writefds = malloc(sizeof(fd_set));
	FD_ZERO(state -> readfds);
	FD_ZERO(state -> writefds);
}

void apiAddEvent(Eventloop* el, int fd, int mask) {

	Api_state* state = (Api_state*) el -> state;
	/* 
		Initiate the fd_set accordidng to the mask
		mask: 
			EL_READABLE --> fd is added to readfds
			EL_WRITABLE --> fd is added to writefds
	*/
	if (mask == EL_READABLE) {
		FD_SET(fd, state -> readfds);
	}
	if (mask == EL_WRITABLE) {
		FD_SET(fd, state -> writefds);
	}
}

int apiPoll(Eventloop* el) {
	int numEvents = 0; 
	int returnVal = 0;
	int nfds = el -> setSize + 1;
	Api_state* state = (Api_state*) el -> state;

	memcpy(state -> _readfds, state -> readfds, sizeof(fd_set));
	memcpy(state -> _writefds, state -> writefds, sizeof(fd_set));
	sleep(2);
	returnVal = select(nfds, state -> _readfds, state -> _writefds, NULL, NULL);
	if (returnVal > 0) {
		for (int i = 0; i < nfds; i++) {
			if (FD_ISSET(i, state -> _readfds)) {
				(el -> fired_events)[numEvents] -> fd = i;
				(el -> fired_events)[numEvents] -> mask = EL_READABLE;
				numEvents++;
			}
			if (FD_ISSET(i, state -> _writefds)) {
				(el -> fired_events)[numEvents] -> fd = i;
				(el -> fired_events)[numEvents] -> mask = EL_WRITABLE;
				numEvents++;
			}
		}
	}
	return numEvents;
}
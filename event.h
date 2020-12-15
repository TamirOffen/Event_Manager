#ifndef EVENT_H_
#define EVENT_H_

#include <stdbool.h>
#include "date.h"
#include "member.h"
#include "priority_queue.h"

typedef struct Event_t *Event;

typedef enum EventResult_t {
    EVENT_SUCCESS,
    EVENT_INVALID_ID,
    EVENT_NULL_ARGUMENT,
    EVENT_OUT_OF_MEMORY
} EventResult;

// returns the event if succesful, NULL otherwise
Event eventCreate(char* event_name, int event_id);

//returns a pointer to an event struct
//(Event)event
PQElement copy_event(PQElement event);
void free_event(PQElement event);

// return true if the event have the same id //TODO: maybe wrong
bool equal_events(PQElement event1, PQElement event2);

/*      priority funcs for date     */
PQElementPriority copyDate(PQElementPriority n);
void freeDate(PQElementPriority n);
int compareDate(PQElementPriority n1, PQElementPriority n2);

/*
PQ events;
// E1, 1.1.2020
// E2, 1.2.2020
to get the date of E1:
pqGetName("E1").priority = 1.1.2020
*/


void printEvent(Event event);












#endif


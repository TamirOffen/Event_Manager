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
Event eventCreate(char* event_name, int event_id, Date date);

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

// basically just pqInserts member into event->members_queue
PriorityQueueResult linkMemberToEvent(Event event, Member member);

bool isMemberLinkedToEvent(Event event, Member member);

PriorityQueueResult removeMemberFromEvent(Event event, Member member);


// returns a pointer to the event_name
char* getEventName(Event event);

// sets the event's name
void setEventName(Event event, char* event_name);

// returns a pointer to the date of the "event"
Date getEventDate(Event event);

// set the event's date
void setEventDate(Event event, Date date);

int getEventID(Event event);

void printEvent(Event event);
void printEventMembers(Event event);


char* getEventMembersName (Event event);








#endif


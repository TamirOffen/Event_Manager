#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "priority_queue.h"
#include "strings.h"


struct Event_t {
    char* event_name;
    int event_id;
    PriorityQueue members_queue; //the list of members that manage the event
};

Event eventCreate(char* event_name, int event_id) {
    if(event_name == NULL) {
        return NULL;
    }
    if(event_id <= 0) {
        return NULL;
    }

    Event event = malloc(sizeof(event));
    if(event == NULL) {
        return NULL;
    }

    PriorityQueue members_queue = pqCreate(copy_member, free_member, equal_members, copy_member_id, free_member_id, compare_members_id);
    if(members_queue == NULL) {
        free(event);
        return NULL;
    }
    event->members_queue = members_queue;

    event->event_name = malloc(sizeof(char) * strlen(event_name) + 1);
    if(event->event_name == NULL) {
        pqDestroy(members_queue);
        free(event);
        return NULL;
    }
    strcpy(event->event_name, event_name);

    event->event_id = event_id;

    return event;
}

PQElement copy_event(PQElement event) {
    if(event == NULL) {
        return NULL; //event that was passed in is NULL
    }

    Event copy_of_event = malloc(sizeof(copy_of_event));
    if(copy_of_event == NULL) {
        return NULL; //memory allocation of copy_of_event failed
    }

    Event event_paramater = (Event)event; //???? does this cast PQElement event to an Event????

    PriorityQueue members_queue_copy = pqCopy(event_paramater->members_queue);
    if(members_queue_copy == NULL) {
        free(copy_of_event); //allocation of the new pq failed
    }
    copy_of_event->members_queue = members_queue_copy;

    copy_of_event->event_id = event_paramater->event_id;
    // copy_of_event->event_id = ((Event)event)->event_id;   Maybe this also works????

    copy_of_event->event_name = malloc(sizeof(char) * strlen(event_paramater->event_name) + 1);
    if(copy_of_event->event_name == NULL) {
        pqDestroy(members_queue_copy);
        free(copy_of_event);
        return NULL;
    }
    strcpy(copy_of_event->event_name, event_paramater->event_name);

    return copy_of_event;
}

void free_event(PQElement event) {
    return;
}

// return true if the event have the same id //TODO: maybe wrong
bool equal_events(PQElement event1, PQElement event2){
    return false;
}

/*      priority funcs for date     */
PQElementPriority copyDate(PQElementPriority n){
    return NULL;
}
void freeDate(PQElementPriority n) {
    return;
}

int compareDate(PQElementPriority n1, PQElementPriority n2) {
    return 0;
}



void printEvent(Event event) {
    printf("Event Name: %s,\tEvent ID: %d\n", event->event_name, event->event_id);
}


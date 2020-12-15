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

// i think we need an eventCreate() or something

PQElement copy_event(PQElement event) {
    if(event == NULL) {
        return NULL; //event that was passed in is NULL
    }

    Event copy_of_event = malloc(sizeof(Event));
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



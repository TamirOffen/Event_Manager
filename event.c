#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "priority_queue.h"


struct Event_t {
    char* event_name;
    int event_id;
    PriorityQueue members_queue; //the list of members that manage the event
};


PQElement copy_event(PQElement event) {
    return NULL;
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



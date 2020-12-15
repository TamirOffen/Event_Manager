#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "member.h"
#include "priority_queue.h"
#include "event_manager.h"


struct EventManager_t {
    PriorityQueue events; //the event is the element, and the priority is the date.
    Date current_date;

    //the member is the element, the number of events that they manage is the priority (by most events to least events)
    PriorityQueue total_members; 
};


EventManager createEventManager(Date date) {

    EventManager em = malloc(sizeof(em)); //TODO if doesnt work, check this
    if(em == NULL) {
        return NULL;
    }

    PriorityQueue events = pqCreate(copy_event, free_event, equal_events, copyDate, freeDate, compareDate);
    if(events == NULL) {
        free(em);
        return NULL;
    }
    em->events = events;

    em->current_date = dateCopy(date); //TODO if doesnt work, check this

    // the priority represents how many events the member manages
    PriorityQueue total_members = pqCreate(copy_member, free_member, equal_members, copyInt, freeInt, compareInts);
    if(total_members == NULL) {
        pqDestroy(events);
        dateDestroy(em->current_date);
        free(em);
        return NULL;
    }
    em->total_members = total_members;

    return em;
}



int emGetEventsAmount(EventManager em) {
    if(em == NULL) {
        return -1;
    }

    return pqGetSize(em->events);
}



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

void destroyEventManager(EventManager em){
    if (em == NULL){
        return;
    }

    pqDestroy(em->events);
    pqDestroy(em->total_members);
    dateDestroy(em->current_date);

    free(em);
}

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id){
    //We should make functions for name and id validations and use them here.
    Event new_event = eventCreate(event_name, event_id);
    if(new_event == NULL){
        return EM_OUT_OF_MEMORY;
    }

    Date copied_date = dateCopy(date);

    pqInsert(em->events, new_event, date);

    return EM_SUCCESS;
}

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id){

    Date date = dateCopy(em->current_date);
    if(date == NULL){
        return EM_OUT_OF_MEMORY;
    }

    for (int i = 0 ; i < days ; i++){ // Increase the current time by (date) days using Tick function
        dateTick(date);
    }

    emAddEventByDate(em, event_name, date, event_id); // Used the previous function.
    return EM_SUCCESS;
}

EventManagerResult emRemoveEvent(EventManager em, int event_id){

    //TODO

    return EM_SUCCESS;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date){
    //Event event = malloc(sizeof(event));//????
    //event = eventSearchByID(em->events, event_id);//TODO
    //TODO

    return EM_SUCCESS;
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id){
    //Member member = memberCreate (member_name, member_id);//TODO in member.c and member.h
    //Check if a member is in the total_members ... TODO
    //pqInsert(em->total_members, member, 0);

    return EM_SUCCESS;
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id){
    // Member member = malloc (sizeof(member));
    // if(member == NULL){
    //     return EM_OUT_OF_MEMORY;
    // }
    // Event event = malloc (sizeof(event));
    // if(event == NULL){
    //     return EM_OUT_OF_MEMORY;
    // }

    //member = memberSearchByID(em->total_members, member_id);
    //event = eventSearchByID(em->events, event_id);
    //How to access members pq in event.... TODO.

    return EM_SUCCESS;
}

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id){
    //     Member member = malloc (sizeof(member));
    // if(member == NULL){
    //     return EM_OUT_OF_MEMORY;
    // }
    // Event event = malloc (sizeof(event));
    // if(event == NULL){
    //     return EM_OUT_OF_MEMORY;
    // }

    // member = memberSearchByID(em->total_members, member_id);
    // event = eventSearchByID(em->events, event_id);
        // We need to use pqRemoveElement, how to access the members pq in event? TODO.

        return EM_SUCCESS;
}

EventManagerResult emTick(EventManager em, int days){
    for (int i = 0 ; i < days ; i++){
        dateTick(em->current_date);
    }

    //EMRemoveOutDatedEvents (em);//TODO

    return EM_SUCCESS;
}

char* emGetNextEvent(EventManager em){
    //Event event = malloc (sizeof(event));
    //event = pqGetNext(em->events); 
    //return (eventGetName(event));//TODO in event
}

int emGetEventsAmount(EventManager em) {
    if(em == NULL) {
        return -1;
    }

    return pqGetSize(em->events);
}



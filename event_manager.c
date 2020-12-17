#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "member.h"
#include "priority_queue.h"
#include "event_manager.h"
#include "string.h"


struct EventManager_t {
    PriorityQueue events; //the event is the element, and the priority is the date.
    Date current_date;

    //the member is the element, the number of events that they manage is the priority (by most events to least events)
    PriorityQueue total_members; 
};


EventManager createEventManager(Date date) {
    EventManager em = malloc(sizeof(*em));
    if(em == NULL) {
        return NULL;
    }

    PriorityQueue events = pqCreate(copy_event, free_event, equal_events, copyDate, freeDate, compareDate);
    if(events == NULL) {
        free(em);
        return NULL;
    }
    em->events = events;

    em->current_date = dateCopy(date); 

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

    // PQ_FOREACH(Event, current_event, em->events) {
    //     free_event(current_event);
    // }

    pqDestroy(em->events);
    pqDestroy(em->total_members);
    dateDestroy(em->current_date);

    free(em);
    em = NULL;
}

//TODO: Memory issues here
//NOTE: pqInsert seems to be the problem, the free funcs for event work
EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id){
    if(em == NULL || event_name == NULL || date == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    // if dateCompare returns a pos num, that means that current date comes after date.
    if(dateCompare(em->current_date, date) > 0) {
        return EM_INVALID_DATE;
    }

    Event new_event = eventCreate(event_name, event_id, date);
    if(new_event == NULL) {
        return EM_OUT_OF_MEMORY;
    }

    // the comparison func of PQ events is comparing the ids of the events
    if(pqContains(em->events, new_event) == true) {
        free_event(new_event);
        return EM_EVENT_ID_ALREADY_EXISTS;
    }

    // checking that there isn't another event_name on the same date 
    PQ_FOREACH(Event, current_event, em->events) {
        if(strcmp(getEventName(current_event), event_name) == 0) {
            if(dateCompare(getEventDate(current_event), date) == 0) {
                free_event(new_event);
                return EM_EVENT_ALREADY_EXISTS;
            }
        }
    }

    pqInsert(em->events, new_event, date);
    free_event(new_event);

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
    dateDestroy(date);
    return EM_SUCCESS;
}

EventManagerResult emRemoveEvent(EventManager em, int event_id){
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }
    
    Date temp_date = dateCreate(1,1,1);
    Event temp_event = eventCreate("temp event", event_id, temp_date); //TODO: terrible programming, Maybe replace with NULL
    if(pqContains(em->events, temp_event) == false) {
        free_event(temp_event);
        dateDestroy(temp_date);
        return EM_EVENT_NOT_EXISTS;
    }

    pqRemoveElement(em->events, temp_event);

    free_event(temp_event);
    dateDestroy(temp_date);

    return EM_SUCCESS;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date){
    if(em == NULL || new_date == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }
    if(dateCompare(em->current_date, new_date) > 0) {
        return EM_INVALID_DATE;
    }

    // get the event with event_id
    Date temp_date = dateCreate(1,1,1); //TODO add NULL check
    Event event = eventCreate("temp event", event_id, temp_date); //TODO: terrible programming, Maybe replace with NULL- DOESN'T WORK
    bool found_event = false;
    PQ_FOREACH(Event, current_event, em->events) {
        if(equal_events(current_event, event) == true) {
            free_event(event);
            dateDestroy(temp_date); 
            event = copy_event(current_event);
            // setEventName(event, getEventName(current_event)); 
            // setEventDate(event, getEventDate(current_event)); 
            found_event = true;
        }
    }
    if(found_event == false) {
        free_event(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }
    

    // checking that there isn't another event_name on the same date 
    PQ_FOREACH(Event, current_event, em->events) {
        if(strcmp(getEventName(current_event), getEventName(event)) == 0) {
            if(dateCompare(getEventDate(current_event), getEventDate(event)) == 0) {
                free_event(event);
                dateDestroy(temp_date);
                return EM_EVENT_ALREADY_EXISTS; //same event_name on the same date
            }
        }
    }

    if(pqChangePriority(em->events, event, getEventDate(event), new_date) == PQ_OUT_OF_MEMORY) {
        free_event(event);
        dateDestroy(temp_date);
        return EM_OUT_OF_MEMORY;
    }

    free_event(event);
    dateDestroy(temp_date);

    return EM_SUCCESS;

}


EventManagerResult emAddMember(EventManager em, char* member_name, int member_id){
    if(em == NULL || member_name == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0) {
        return EM_INVALID_MEMBER_ID;
    }

    Member new_member = createMember(member_name, member_id);
    if(new_member == NULL) {
        return EM_OUT_OF_MEMORY;
    }

    // checking for if the id already exists in the em
    if(pqContains(em->total_members, new_member) == true) {
        free_member(new_member);
        return EM_MEMBER_ID_ALREADY_EXISTS;
    }

    int starting_priority_of_member = 0; //i.e. how many events the member is in charge of at first
    pqInsert(em->total_members, new_member, &starting_priority_of_member);

    free_member(new_member);

    // PQ_FOREACH(Member, m, em->total_members) {
    //     printMember(m);
    // }

    return EM_SUCCESS;
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id){
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0) {
        return EM_INVALID_MEMBER_ID;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    //TODO: Code Duplication! here and getDateID bellow
    // get the event with event_id
    Date temp_date = dateCreate(1,1,1); //TODO add NULL check
    Event event = eventCreate("temp event", event_id, temp_date); //TODO: terrible programming, Maybe replace with NULL- DOESN'T WORK
    bool found_event = false;
    PQ_FOREACH(Event, current_event, em->events) {
        if(equal_events(current_event, event) == true) {
            free_event(event);
            dateDestroy(temp_date);
            event = copy_event(current_event);
            found_event = true;
            // break;
        }
    }
    if(found_event == false) {
        free_event(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }


    // get the member with member_id
    Member member = createMember("temp member", member_id);
    bool found_member = false;
    PQ_FOREACH(Member, current_member, em->total_members) {
        if(equal_members(current_member, member) == true) {
            free_member(member);
            member = copy_member(current_member);
            found_member = true;
            break;
        }
    }
    if(found_member == false) {
        free_member(member);
        free_event(event);
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    //tests get member and get event here:
    // printEvent(event);
    // printMember(member);

    // check if member_id is already linked with event_id
    if(isMemberLinkedToEvent(event, member) == true) {
        printf("linked\n");
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    
    printf("%d\n", linkMemberToEvent(event, member));
    // if(linkMemberToEvent(event, member) == PQ_OUT_OF_MEMORY) {
    //     return EM_OUT_OF_MEMORY;
    // }

    // printEvent(event);


    free_event(event);
    free_member(member);

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
    return NULL;
}

int emGetEventsAmount(EventManager em) {
    if(em == NULL) {
        return -1;
    }

    return pqGetSize(em->events);
}





//FOR TESTING:
void printAllEventsAndTheirMembers(EventManager em) {
    PQ_FOREACH(Event, e, em->events) {
        printEvent(e);
    }
}
void printAllMembers(EventManager em) {
    PQ_FOREACH(Member, m, em->total_members) {
        printMember(m);
    }
}



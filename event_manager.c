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

    PriorityQueue eventsCopy = pqCopy(em->events);
    // checking that there isn't another event_name on the same date 
    PQ_FOREACH(Event, current_event, eventsCopy) {
        if(strcmp(getEventName(current_event), event_name) == 0) {
            if(dateCompare(getEventDate(current_event), date) == 0) {
                free_event(new_event);
                pqDestroy(eventsCopy);
                return EM_EVENT_ALREADY_EXISTS;
            }
        }
    }
    pqDestroy(eventsCopy);

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

    EventManagerResult result = emAddEventByDate(em, event_name, date, event_id); // Used the previous function.
    dateDestroy(date);
    return result;
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

//DOESN"T WORK
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
    PriorityQueue eventsCopy = pqCopy(em->events);
    PQ_FOREACH(Event, current_event, em->events) {
        if(equal_events(current_event, event) == true) {
            free_event(event);
            dateDestroy(temp_date); 
            // event = copy_event(current_event);
            event = current_event;
            found_event = true;
        }
    }
    pqDestroy(eventsCopy);
    if(found_event == false) {
        free_event(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }
    
    // checking that there isn't another event_name on the same date 
    PriorityQueue copy_of_events = pqCopy(em->events);
    PQ_FOREACH(Event, current_event, copy_of_events) {
        if(strcmp(getEventName(current_event), getEventName(event)) == 0) {
            if(dateCompare(getEventDate(current_event), new_date) == 0) {
                printf("same\n");
                printEvent(event);
                // free_event(event);
                // dateDestroy(temp_date);
                pqDestroy(copy_of_events);
                return EM_EVENT_ALREADY_EXISTS; //same event_name on the same date
            }
        }
    }
    pqDestroy(copy_of_events);

    Event copy_of_event = copy_event(event);
    setEventDate(event, new_date);


    //change the date of the event in pq events
    // PriorityQueue copy_of_events = pqCopy(em->events);
    
    // pqDestroy(copy_of_events);

    if(pqChangePriority(em->events, copy_of_event, getEventDate(copy_of_event), new_date) == PQ_OUT_OF_MEMORY) {
        // free_event(event);
        // dateDestroy(temp_date);
        free_event(copy_of_event);
        return EM_OUT_OF_MEMORY;
    }
    free_event(copy_of_event);
    
    PQ_FOREACH(Event, current_event, em->events) {
        if(equal_events(current_event, event) == true) {
            setEventDate(current_event, new_date);
        }
    }

    // free_event(event);
    // dateDestroy(temp_date);

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
    PriorityQueue eventsPQ = pqCopy(em->events);  //TODO: kinda weird, if errors than come back here
    PQ_FOREACH(Event, current_event, em->events) {
        if(equal_events(current_event, event) == true) {
            free_event(event);
            dateDestroy(temp_date);
            // event = copy_event(current_event);
            event = current_event; //TODO: kinda weird, if errors than come back here
            found_event = true;
            break;
        }
    }
    pqDestroy(eventsPQ);
    if(found_event == false) {
        free_event(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }

    // get the member with member_id
    PriorityQueue membersPQ = pqCopy(em->total_members);
    Member member = createMember("temp member", member_id);
    bool found_member = false;
    PQ_FOREACH(Member, current_member, membersPQ) {
        if(equal_members(current_member, member) == true) {
            free_member(member);
            member = copy_member(current_member);
            found_member = true;
            break;
        }
    }
    pqDestroy(membersPQ);
    if(found_member == false) {
        free_member(member);
        // free_event(event);
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    //tests get member and get event here:
    // printEvent(event);
    // printMember(member);

    // check if member_id is already linked with event_id
    if(isMemberLinkedToEvent(event, member) == true) {
        free_member(member);
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    
    // printf("%d\n", linkMemberToEvent(event, member));
    if(linkMemberToEvent(event, member) == PQ_OUT_OF_MEMORY) {
        return EM_OUT_OF_MEMORY;
    }

    //TODO: in total_members pq, increase by one the number of events managed by the member

    // printEvent(event);

    // free_event(event);
    free_member(member);

    return EM_SUCCESS;
}

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id){  
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0) {
        return EM_INVALID_MEMBER_ID;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    PriorityQueue em_members_queue = pqCopy(em->total_members); //TODO: add NULL check
    Member member = createMember("temp member", member_id); //TODO: add NULL check
    bool member_found = false;
    PQ_FOREACH(Member, m, em_members_queue) {
        if(equal_members(m, member) == true) {
            free_member(member);
            member = copy_member(m);
            member_found = true;
            break;
        }
    }
    pqDestroy(em_members_queue);
    if(member_found == false) {
        free_member(member);
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    // printMember(member);

    PriorityQueue em_events = pqCopy(em->events);
    Date temp_date = dateCreate(1,1,1); //TODO bad programming
    Event event = eventCreate("temp event", event_id, temp_date); //TODO bad programming
    bool event_found = false;
    PQ_FOREACH(Event, e, em->events) {
        if(equal_events(e, event) == true) {
            free_event(event);
            dateDestroy(temp_date);
            // event = copy_event(e);
            event = e;
            event_found = true;
            break;
        }
    }
    pqDestroy(em_events);
    if(event_found == false) {
        free_event(event);
        dateDestroy(temp_date);
        free_member(member);
        return EM_EVENT_ID_NOT_EXISTS;
    }
    // printEvent(event);

    if(isMemberLinkedToEvent(event, member) == false) {
        // printf("not linked\n");
        // free_event(event);
        free_member(member);
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }

    // printf("linked\n");

    removeMemberFromEvent(event, member);

    // free_event(event);
    free_member(member);
    return EM_SUCCESS;
}

EventManagerResult emTick(EventManager em, int days){
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }

    if(days <= 0) {
        return EM_INVALID_DATE;
    }

    for (int i = 0 ; i < days ; i++){
        dateTick(em->current_date); //TODO: doesn't take into account different #days in each month
    }

    PriorityQueue pq_events = pqCopy(em->events);
    PQ_FOREACH(Event, e, pq_events) {
        if(dateCompare(getEventDate(e), em->current_date) < 0) {
            if(emRemoveEvent(em, getEventID(e)) == EM_OUT_OF_MEMORY) {
                pqDestroy(pq_events);
                return EM_OUT_OF_MEMORY;
            }
        }
    }
    pqDestroy(pq_events);

    return EM_SUCCESS;
}

char* emGetNextEvent(EventManager em){
    if(em == NULL) {
        return NULL;
    }

    //TODO: might need to create a copy of pq events
    return getEventName(pqGetFirst(em->events));
}

int emGetEventsAmount(EventManager em) {
    if(em == NULL) {
        return -1;
    }

    return pqGetSize(em->events);
}





//FOR TESTING:
void printEM(EventManager em) {
    int day = -1, month = -1, year = -1;
    dateGet(em->current_date, &day, &month, &year);
    printf("Current Day of the EM:\t%d.%d.%d\n", day, month, year);
    PriorityQueue copyPQ = pqCopy(em->events);
    PQ_FOREACH(Event, e, copyPQ) {
        printEvent(e);
    }
    pqDestroy(copyPQ);
}
void printAllEventsAndTheirMembers(EventManager em) {
    PriorityQueue copyPQ = pqCopy(em->events);
    PQ_FOREACH(Event, e, copyPQ) {
        printEvent(e);
    }
    pqDestroy(copyPQ);
}
void getFirstMember(EventManager em) {
    Member m = (Member)pqGetFirst(em->total_members);
    printMember(m);
}
void getNextMember(EventManager em) {
    Member m = (Member)pqGetNext(em->total_members);
    printMember(m);
}
void printAllMembers(EventManager em) {
    PriorityQueue copyPQ = pqCopy(em->total_members);
    PQ_FOREACH(Member, m, copyPQ) {
        printMember(m);
    }
    pqDestroy(copyPQ);
}



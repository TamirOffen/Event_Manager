#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "member.h"
#include "priority_queue.h"
#include "event_manager.h"
#include "string.h"

#define TEMP_DATE dateCreate(1,1,1)

struct EventManager_t {
    // the event is the element, and the priority is the date.
    PriorityQueue events; 

    // the current date of the em
    Date current_date;

    // the member is the element, 
    // the num of events that they manage is their priority (by most events to least events)
    PriorityQueue total_members; 
};

// Create an Event Manager object.
EventManager createEventManager(Date date) {
    if(date == NULL) {
        return NULL;
    }

    // allocates space for an EventManager struct
    EventManager em = malloc(sizeof(*em));
    if(em == NULL) {
        return NULL;
    }

    // creates an events pq, whose elements are Event, and priority is Date
    PriorityQueue events = pqCreate(copyEvent, freeEvent, equalEvents, copyDate, freeDate, compareDate);
    if(events == NULL) {
        free(em);
        return NULL;
    }
    em->events = events;

    // sets (copies) the em's current date to the date from the user
    em->current_date = dateCopy(date); 

    // the priority represents how many events the member manages
    PriorityQueue total_members = pqCreate(copyMember, freeMember, equalMembers, copyInt, freeInt, compareInts);
    if(total_members == NULL) {
        pqDestroy(events);
        dateDestroy(em->current_date);
        free(em);
        return NULL;
    }
    em->total_members = total_members;

    return em;
}

// frees the event manager, including anything that was used by it.
void destroyEventManager(EventManager em) {
    if (em == NULL){
        return;
    }

    // frees the priority queues inside em, and its date
    pqDestroy(em->events);
    pqDestroy(em->total_members);
    dateDestroy(em->current_date);

    free(em);
    em = NULL;
}

// adds an event into the em on date "date".
EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id) {
    if(em == NULL || event_name == NULL || date == NULL) {
        return EM_NULL_ARGUMENT;
    }
    // if dateCompare returns a pos num, that means that current date comes after date.
    if(dateCompare(em->current_date, date) > 0) {
        return EM_INVALID_DATE;
    }
    // user can enter an event_id >= 0
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    // creates a new event with the name, date, and event_id given by the user
    Event new_event = eventCreate(event_name, event_id, date);
    if(new_event == NULL) {
        return EM_OUT_OF_MEMORY;
    }

    // checking that there isn't another event_name on the same date 
    PriorityQueue eventsCopy = pqCopy(em->events);
    PQ_FOREACH(Event, current_event, eventsCopy) {
        if(strcmp(getEventName(current_event), event_name) == 0) {
            if(dateCompare(getEventDate(current_event), date) == 0) {
                // if there is, we free new_event and pq we use for iterating
                freeEvent(new_event);
                pqDestroy(eventsCopy);
                return EM_EVENT_ALREADY_EXISTS;
            }
        }
    }
    pqDestroy(eventsCopy);

    // the comparison func of PQ events is comparing the ids of the events
    if(pqContains(em->events, new_event) == true) {
        freeEvent(new_event);
        return EM_EVENT_ID_ALREADY_EXISTS;
    }

    // if we got to this point, that means that we can add the event on the date into the em
    pqInsert(em->events, new_event, date);
    freeEvent(new_event);

    return EM_SUCCESS;

}

// adds a new event into the em in a number of days.
EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id) {
    if(em == NULL || event_name == NULL) {
        return EM_NULL_ARGUMENT;
    }
    // days passed by the user have to be >= 0
    if(days < 0) {
        return EM_INVALID_DATE;
    }

    // creates a copy of the date passed in to be used when adding a new event into the em
    Date date = dateCopy(em->current_date);
    if(date == NULL){
        return EM_OUT_OF_MEMORY;
    }

    // increase the current date of the em by days using the dateTick function
    for (int i = 0 ; i < days ; i++){ 
        dateTick(date);
    }

    // adds the event using emAddEventByName func and returns its return value
    EventManagerResult result = emAddEventByDate(em, event_name, date, event_id);
    dateDestroy(date);
    return result;
}

// removes the event with event_id from em.
EventManagerResult emRemoveEvent(EventManager em, int event_id) {
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    // checks if the event is not in the em
    Date temp_date = TEMP_DATE;
    Event temp_event = eventCreate("", event_id, temp_date); 
    if(pqContains(em->events, temp_event) == false) {
        freeEvent(temp_event);
        dateDestroy(temp_date);
        return EM_EVENT_NOT_EXISTS;
    }

    // if it got here, then it means the event is in the em, and it will remove it
    pqRemoveElement(em->events, temp_event);
    freeEvent(temp_event);
    dateDestroy(temp_date);

    return EM_SUCCESS;
}

// changes the date of event with event_id from its previous date to "new_date".
EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date) {
    if(em == NULL || new_date == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }
    if(dateCompare(em->current_date, new_date) > 0) {
        return EM_INVALID_DATE;
    }
    
    // finds the event with event_id inside of the em. (events pq in em)
    Date temp_date = TEMP_DATE;
    Event event = eventCreate("", event_id, temp_date); 
    bool found_event = false;
    PriorityQueue eventsCopy = pqCopy(em->events);
    if(eventsCopy == NULL) {
        return EM_OUT_OF_MEMORY;
    }
    PQ_FOREACH(Event, current_event, eventsCopy) {
        if(equalEvents(current_event, event) == true) {
            freeEvent(event);
            dateDestroy(temp_date); 
            event = copyEvent(current_event);
            found_event = true;
        }
    }
    pqDestroy(eventsCopy);

    // if the event is not in the em, free and exit the func
    if(found_event == false) {
        freeEvent(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }
    
    // checking that there isn't another event_name on the same date 
    PriorityQueue copy_of_events = pqCopy(em->events);
    if(copy_of_events == NULL) {
        return EM_OUT_OF_MEMORY;
    }
    PQ_FOREACH(Event, current_event, copy_of_events) {
        if(strcmp(getEventName(current_event), getEventName(event)) == 0) {
            if(dateCompare(getEventDate(current_event), new_date) == 0) {
                //same event_name on the same date, free and exit the func
                freeEvent(event);
                pqDestroy(copy_of_events);
                return EM_EVENT_ALREADY_EXISTS; 
            }
        }
    }
    pqDestroy(copy_of_events);

    // changes the date of the event in the events pq in the em
    if(pqChangePriority(em->events, event, getEventDate(event), new_date) == PQ_OUT_OF_MEMORY) {
        freeEvent(event);
        return EM_OUT_OF_MEMORY;
    }
    
    //finds the event in em->events pq and changes its date to new_date
    PQ_FOREACH(Event, current_event, em->events) {
        if(equalEvents(current_event, event) == true) {
            setEventDate(current_event, new_date);
        }
    }

    freeEvent(event);

    return EM_SUCCESS;

}

// adds a new memeber by the name "member_name" with "member_id" into the em.
// NOTE: this new member is in the em for life, i.e. he/she cannot be removed.
EventManagerResult emAddMember(EventManager em, char* member_name, int member_id) {
    if(em == NULL || member_name == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0) {
        return EM_INVALID_MEMBER_ID;
    }

    // creates the new member that will be in the em
    Member new_member = createMember(member_name, member_id);
    if(new_member == NULL) {
        return EM_OUT_OF_MEMORY;
    }

    // checking for if the id already exists in the em
    if(pqContains(em->total_members, new_member) == true) {
        freeMember(new_member);
        return EM_MEMBER_ID_ALREADY_EXISTS;
    }

    int starting_priority_of_member = 0; //i.e. how many events the member is in charge of at first
    pqInsert(em->total_members, new_member, &starting_priority_of_member);

    freeMember(new_member);

    return EM_SUCCESS;
}

// adds the member with "member_id" to the list of students that are in charge of event with "event_id".
EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id) {
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0) {
        return EM_INVALID_MEMBER_ID;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    // get the event with event_id
    Date temp_date = TEMP_DATE;
    Event event = eventCreate("", event_id, temp_date); 
    bool found_event = false;
    PriorityQueue eventsPQ = pqCopy(em->events);
    if(eventsPQ == NULL) {
        return EM_OUT_OF_MEMORY;
    } 
    PQ_FOREACH(Event, current_event, em->events) {
        if(equalEvents(current_event, event) == true) {
            freeEvent(event);
            dateDestroy(temp_date);
            event = current_event;
            found_event = true;
            break;
        }
    }
    pqDestroy(eventsPQ);

    // if event was not found in the em, than free and exit the func
    if(found_event == false) {
        freeEvent(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }

    // get the member with member_id
    PriorityQueue membersPQ = pqCopy(em->total_members);
    Member member = createMember("temp member", member_id);
    bool found_member = false;
    PQ_FOREACH(Member, current_member, em->total_members) {
        if(equalMembers(current_member, member) == true) {
            freeMember(member);
            member = current_member;
            found_member = true;
            break;
        }
    }
    pqDestroy(membersPQ);
    if(found_member == false) {
        freeMember(member); 
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    // check if member_id is already linked with event_id
    if(isMemberLinkedToEvent(event, member) == true) {
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }

    // stores the old priority of member before changing it
    int old_num_of_events = getMemberNumOfEvents(member) ;
    
    // links the member to event
    if(linkMemberToEvent(event, member) == PQ_OUT_OF_MEMORY) {
        return EM_OUT_OF_MEMORY;
    }

    // updates the member's number of events in charge of
    int new_num_of_events = getMemberNumOfEvents(member);
    Member member_copy = copyMember(member);
    pqChangePriority(em->total_members, member_copy, &old_num_of_events, &new_num_of_events);
    freeMember(member_copy);

    return EM_SUCCESS;
}

// removes the member with "member_id" from the students in charge of event with "event_id".
EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id) {  
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0) {
        return EM_INVALID_MEMBER_ID;
    }
    if(event_id < 0) {
        return EM_INVALID_EVENT_ID;
    }

    // looks for the member in the members pq in the em.
    PriorityQueue em_members_queue = pqCopy(em->total_members);
    if(em_members_queue == NULL) {
        return EM_OUT_OF_MEMORY;
    }
    Member member = createMember("temp member", member_id); 
    bool member_found = false;
    PQ_FOREACH(Member, m, em->total_members) {
        if(equalMembers(m, member) == true) {
            freeMember(member);
            member = m;
            member_found = true;
            break;
        }
    }
    pqDestroy(em_members_queue);

    // if it doesn't exist in the members pq, than free and exit
    if(member_found == false) {
        freeMember(member); 
        return EM_MEMBER_ID_NOT_EXISTS;
    }

    // looks for the event with event_id from the user
    PriorityQueue em_events = pqCopy(em->events);
    Date temp_date = TEMP_DATE;
    Event event = eventCreate("temp event", event_id, temp_date);
    bool event_found = false;
    PQ_FOREACH(Event, e, em->events) {
        if(equalEvents(e, event) == true) {
            freeEvent(event);
            dateDestroy(temp_date);
            event = e;
            event_found = true;
            break;
        }
    }
    pqDestroy(em_events);

    // if the event with event_id doesnt exist in the em, free and exit
    if(event_found == false) {
        freeEvent(event);
        dateDestroy(temp_date);
        return EM_EVENT_ID_NOT_EXISTS;
    }

    // checks if the member and event are linked
    if(isMemberLinkedToEvent(event, member) == false) {
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }

    int old_num_of_events = getMemberNumOfEvents(member) ;

    // remove the member from the event 
    removeMemberFromEvent(event, member);

    // update the num of events the member is in charge of
    int new_num_of_events = getMemberNumOfEvents(member);
    Member mC = copyMember(member);
    pqChangePriority(em->total_members, mC, &old_num_of_events, &new_num_of_events);
    freeMember(mC);

    return EM_SUCCESS;
}

// advances the em's current date by "days" amount of days
// NOTE: removes the events that were supposed to have happened
EventManagerResult emTick(EventManager em, int days) {
    if(em == NULL) {
        return EM_NULL_ARGUMENT;
    }
    if(days <= 0) {
        return EM_INVALID_DATE;
    }

    // forward the current date of the em using dateTick
    for (int i = 0 ; i < days ; i++){
        dateTick(em->current_date);
    }

    // look for the events that are after the new current date and remove them
    PriorityQueue pq_events = pqCopy(em->events);
    if(pq_events == NULL) {
        return EM_OUT_OF_MEMORY;
    }
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

// returns the name of the event that's supposed to occur next
// NOTE: if there are multiple events that will happen next on the same date,
//       than return the one entered first into the em. 
char* emGetNextEvent(EventManager em){
    if(em == NULL) {
        return NULL;
    }

    // returns the event that is first in the events pq
    return getEventName(pqGetFirst(em->events));
}

// returns the number of future events in the em
int emGetEventsAmount(EventManager em) {
    if(em == NULL) {
        return -1;
    }

    // returns the size of the events pq, which represent the events in the em
    return pqGetSize(em->events);
}

// prints to "file_name" in order the list of events, their dates, and the members in charge of them
// NOTE: "in order" means by their dates order
// NOTE: if multiple events are on the same date, than print by the ones entered first
// NOTE: members are printed by increasing order of their id's
void emPrintAllEvents(EventManager em, const char* file_name){
    if(em == NULL || file_name == NULL) {
        return;
    }

    // opens the file with name "file_name"
    FILE* output_file = fopen(file_name, "w");
    if(output_file == NULL){
       return;
    }

    PriorityQueue events_copy = pqCopy(em->events);
    if(events_copy == NULL){
       return;
    }

    int day = 0, month = 0, year = 0;

    // writes into the file each event from the events pq in the em 
    PQ_FOREACH(Event, current_event, events_copy){
            dateGet(getEventDate(current_event), &day, &month, &year);
            fprintf(output_file, "%s,%d.%d.%d",getEventName(current_event), day, month, year); 
            getEventMembersName (current_event, output_file);
            
    }

    // closes the file after writing to it
    fclose(output_file);
    pqDestroy(events_copy);
}

// writes into "file_name" the names of all of the members in em, and how many events they are in charge of
// NOTE: the member in charge of the most events is printed first, etc.
// NOTE: if multiple members have the same amount of events, than print by *lowest* member_id
// NOTE: if a member is in charge of 0 events, he/she will not be printed
void emPrintAllResponsibleMembers(EventManager em, const char* file_name) {
    if(em == NULL || file_name == NULL) {
        return;
    }

    // this queue will be built in according to the events queue of the em.
    // it will then be used to write to the file
    PriorityQueue emMembers = pqCreate(copyMember, freeMember, equalMembers, copyInt, freeInt, compareInts);

    // builds the emMembers queue
    PriorityQueue eventPQCopy = pqCopy(em->events);
    PQ_FOREACH(Event, e, eventPQCopy) {
        PriorityQueue eventMembers = getPQEventMembers(e);
        PQ_FOREACH(Member, m, eventMembers) {
            if(pqContains(emMembers, m) == true) {
                PriorityQueue emMemCopy = pqCopy(emMembers);
                PQ_FOREACH(Member, m2, emMemCopy) {
                    if(equalMembers(m, m2) == true) {
                        int num = getMemberNumOfEvents(m2) + 1;
                        pqRemoveElement(emMembers, m);
                        tickMemberNumOfEvents(m2);
                        pqInsert(emMembers, m2, &num);
                        pqDestroy(emMemCopy);
                        break;
                    }
                }
            }
            else {
                setMemberNumOfEvents(m, 1);
                int num = 1;
                pqInsert(emMembers, m, &num);
            }
        }
        pqDestroy(eventMembers);
    }
    pqDestroy(eventPQCopy);

    // opens file with "file_name"
    FILE* output_file = fopen(file_name, "w");
    if(output_file == NULL){
       return;
    }

    // write using the pq we created into the file
    PQ_FOREACH(Member, m, emMembers) {
        fprintf(output_file, "%s,%d\n", getMemberName(m), getMemberNumOfEvents(m));
    }

    // close the file
    fclose(output_file);

    pqDestroy(emMembers);

}



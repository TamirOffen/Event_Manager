#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "priority_queue.h"
#include "string.h"
#include "date.h"


struct Event_t {
    char* event_name;
    int event_id;
    Date date; //the date that the event will take place on
    PriorityQueue members_queue; //the list of members that manage the event
};

Event eventCreate(char* event_name, int event_id, Date date) {
    if(event_name == NULL || date == NULL || event_id < 0) {
        return NULL;
    }

    Date event_date = dateCopy(date);
    if(event_date == NULL) {
        return NULL;
    }

    Event event = malloc(sizeof(*event));
    if(event == NULL) {
        dateDestroy(event_date);
        return NULL;
    }

    event->date = event_date;

    PriorityQueue members_queue = pqCreate(copyMember, freeMember, equalMembers, 
                                           copyMemberID, freeMemberID, compareMembersID);
    if(members_queue == NULL) {
        dateDestroy(event_date);
        free(event);
        return NULL;
    }
    event->members_queue = members_queue;

    event->event_name = malloc(sizeof(char) * strlen(event_name) + 1);
    if(event->event_name == NULL) {
        pqDestroy(members_queue);
        dateDestroy(event_date);
        free(event);
        return NULL;
    }
    strcpy(event->event_name, event_name);

    event->event_id = event_id;

    return event;
}


PQElement copyEvent(PQElement event) {
    if(event == NULL) {
        return NULL; //event that was passed in is NULL
    }

    Event copy_of_event = malloc(sizeof(*copy_of_event));
    if(copy_of_event == NULL) {
        return NULL; //memory allocation of copy_of_event failed
    }

    Event event_paramater = (Event)event; 

    Date new_date = dateCopy(event_paramater->date);
    if(new_date == NULL) {
        free(copy_of_event);
        return NULL;
    }
    copy_of_event->date = new_date;

    PriorityQueue members_queue_copy = pqCopy(event_paramater->members_queue);
    if(members_queue_copy == NULL) {
        dateDestroy(copy_of_event->date);
        free(copy_of_event); //allocation of the new pq failed
        return NULL;
    }
    copy_of_event->members_queue = members_queue_copy;

    copy_of_event->event_id = event_paramater->event_id;

    copy_of_event->event_name = malloc(sizeof(char) * strlen(event_paramater->event_name) + 1);
    if(copy_of_event->event_name == NULL) {
        dateDestroy(copy_of_event->date);
        pqDestroy(members_queue_copy);
        free(copy_of_event);
        return NULL;
    }
    strcpy(copy_of_event->event_name, event_paramater->event_name);

    return copy_of_event;
}

void freeEvent(PQElement event) {
    if(event == NULL) {
        return;
    }

    free(((Event)event)->event_name);
    pqDestroy(((Event)event)->members_queue);
    dateDestroy(((Event)event)->date);
    free((Event)event);

    event = NULL;
}

// return true if the event have the same id
bool equalEvents(PQElement event1, PQElement event2){
    if(((Event)event1)->event_id == ((Event)event2)->event_id) {
        return true;
    }
    return false;
}

/*      priority funcs for date     */
PQElementPriority copyDate(PQElementPriority date){
    Date copy_of_date = dateCopy((Date)date);
    if(copy_of_date == NULL) {
        return NULL;
    }
    return copy_of_date;
}

void freeDate(PQElementPriority date) {
    dateDestroy((Date)date);
    date = NULL;
}

/**
* compareDate: compares to dates and return which comes first
* TODO: this might be code duplication
* @return
* 		A negative integer if date1 occurs first;
* 		0 if they're equal or one of the given dates is NULL;
*		A positive integer if date1 arrives after date2.
*/
int compareDate(PQElementPriority date1, PQElementPriority date2) {
    return -dateCompare((Date)date1, (Date)date2); 
}




// basically just pqInserts member into event->members_queue
PriorityQueueResult linkMemberToEvent(Event event, Member member) {
    if(event == NULL || member == NULL) {
        return PQ_NULL_ARGUMENT;
    }

    return pqInsert(event->members_queue, member, getMemberIdPointer(member));
    
}

bool isMemberLinkedToEvent(Event event, Member member) {
    if(event == NULL || member == NULL) {
        return false;
    }

    return pqContains(event->members_queue, member);
}

PriorityQueueResult removeMemberFromEvent(Event event, Member member) {
    if(event == NULL || member == NULL) {
        return PQ_NULL_ARGUMENT;
    }

    subtractOneFromNumOfEvents(member);

    return pqRemoveElement(event->members_queue, member);
}


char* getEventName(Event event) {
    if(event == NULL) {
        return NULL;
    }
    return event->event_name;
}

void setEventName(Event event, char* event_name) {
    if(event == NULL || event_name == NULL) {
        return;
    }
    if(event->event_name != NULL) {
        free(event->event_name);
    }
    
    event->event_name = malloc(strlen(event_name) + 1);
    strcpy(event->event_name, event_name);
}

Date getEventDate(Event event) {
    if(event == NULL) {
        return NULL;
    }
    return event->date;
}

void setEventDate(Event event, Date date) {
    if(event == NULL || date == NULL) {
        return;
    }
    if(event->date != NULL) {
        dateDestroy(event->date);
    }
    event->date = dateCopy(date); 
}

int getEventID(Event event) {
    if(event == NULL) {
        return -1;
    }
    return event->event_id;
}

int getMemberQueueSize(Event event) {
    return pqGetSize(event->members_queue);
}


PriorityQueue getPQEventMembers(Event event) {
    PriorityQueue copyQueue = pqCopy(event->members_queue);
    if(copyQueue == NULL) {
        return NULL;
    }
    return copyQueue;
}


// used for testing
void printEvent(Event event) {
    int day = -1, month = -1, year = -1;
    dateGet(event->date, &day, &month, &year);
    printf("Event Name: %s\tEvent ID: %d\tDate: %d.%d.%d\n", event->event_name, event->event_id, day, month, year);
    printf("Members: \n");
    PriorityQueue membersQueue = pqCopy(event->members_queue);
    PQ_FOREACH(Member, m, membersQueue) {
        printMember(m);
    }
    pqDestroy(membersQueue);
}



void getEventMembersName (Event event, FILE* output_file){
    if(pqGetSize(event->members_queue) == 0){
        fprintf(output_file, "\n");
        printf("\n");
        return;
    }
    PriorityQueue copied_members = pqCopy(event->members_queue);

    
    PQ_FOREACH(Member, current_member, copied_members){
        fprintf(output_file, ",%s", getMemberName(current_member));
        printf(",%s", getMemberName(current_member));
    }
    fprintf(output_file, "\n");
    printf("\n");

    pqDestroy(copied_members);
}



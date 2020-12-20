#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "event.h"
#include "priority_queue.h"
#include "string.h"
#include "date.h"


struct Event_t
{
    char* event_name;
    int event_id;
    Date date; //the date that the event will take place on
    PriorityQueue members_queue; //the list of members that manage the event
};

//Creates a new event and returns it.
Event eventCreate(char* event_name, int event_id, Date date)
{
    if(event_name == NULL || date == NULL || event_id < 0) {
        return NULL;
    }

    //Copies the date which we want to assign to the event.
    Date event_date = dateCopy(date);
    if(event_date == NULL) {
        return NULL;
    }
    //Allocate memory for event
    Event event = malloc(sizeof(*event));
    if(event == NULL) {
        dateDestroy(event_date);
        return NULL;
    }

    event->date = event_date;

    //Creates a linked members queue which we want to put in the event.
    PriorityQueue members_queue = pqCreate(copyMember, freeMember, equalMembers, 
                                           copyMemberID, freeMemberID, compareMembersID);
    if(members_queue == NULL) {
        dateDestroy(event_date);
        free(event);
        return NULL;
    }
    event->members_queue = members_queue;

    //Assign the name and id for the event.
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

//Copies the given event to a new event and return the copy.
PQElement copyEvent(PQElement event)
{
    if(event == NULL) {
        return NULL; 
    }

    Event copy_of_event = malloc(sizeof(*copy_of_event));
    if(copy_of_event == NULL) {
        return NULL; 
    }

    //Converts PQElement event to Event.
    Event event_paramater = (Event)event; 

    //Copies the date of the event and assigns it to the copy.
    Date new_date = dateCopy(event_paramater->date);
    if(new_date == NULL) {
        free(copy_of_event);
        return NULL;
    }
    copy_of_event->date = new_date;

    //Copies the members queue of the event and puts it in the copy.
    PriorityQueue members_queue_copy = pqCopy(event_paramater->members_queue);
    if(members_queue_copy == NULL) {
        dateDestroy(copy_of_event->date);
        free(copy_of_event); 
        return NULL;
    }
    copy_of_event->members_queue = members_queue_copy;

    //Copies event's ID and name and assigns them to the copy.
    copy_of_event->event_id = event_paramater->event_id;

    copy_of_event->event_name = malloc(sizeof(char) * strlen(event_paramater->event_name) + 1);
    //In case of memory allocation failure for the name, destroys the copied event.
    if(copy_of_event->event_name == NULL) {
        dateDestroy(copy_of_event->date);
        pqDestroy(members_queue_copy);
        free(copy_of_event);
        return NULL;
    }
    strcpy(copy_of_event->event_name, event_paramater->event_name);

    return copy_of_event;
}

//Destroys an event by freeing all of its contents and then freeing it.
void freeEvent(PQElement event)
{
    if(event == NULL) {
        return;
    }
    //Frees event's contents and then frees it.
    free(((Event)event)->event_name);
    pqDestroy(((Event)event)->members_queue);
    dateDestroy(((Event)event)->date);
    free((Event)event);

    event = NULL;
}

//Compares between two events by their IDs.
bool equalEvents(PQElement event1, PQElement event2)
{
    //Compares their IDs.
    if(((Event)event1)->event_id == ((Event)event2)->event_id) {
        return true;
    }
    return false;
}


/*      priority funcs for date     */

//Copies the given Date to a new one and returns the copy.
PQElementPriority copyDate(PQElementPriority date)
{
    Date copy_of_date = dateCopy((Date)date);
    if(copy_of_date == NULL) {
        return NULL;
    }
    return copy_of_date;
}

//Frees a date using dateDestroy function.
void freeDate(PQElementPriority date)
{
    dateDestroy((Date)date);
    date = NULL;
}

//Compares between two dates.
int compareDate(PQElementPriority date1, PQElementPriority date2)
{
    return -dateCompare((Date)date1, (Date)date2); 
}

//Adds the given member to the queue of linked members to the given event (members_queue).
PriorityQueueResult linkMemberToEvent(Event event, Member member)
{
    if(event == NULL || member == NULL) {
        return PQ_NULL_ARGUMENT;
    }

    //Links the member to the event by inserting the member into the members_queue in the event.
    return pqInsert(event->members_queue, member, getMemberIdPointer(member));
    
}

//Checks whether the given member is linked with the given event.
bool isMemberLinkedToEvent(Event event, Member member)
{
    if(event == NULL || member == NULL) {
        return false;
    }
    //Checks if member is in members_queue in event (which means they are linked).
    return pqContains(event->members_queue, member);
}

//Removes the given Member from the given Event.
PriorityQueueResult removeMemberFromEvent(Event event, Member member)
{
    if(event == NULL || member == NULL) {
        return PQ_NULL_ARGUMENT;
    }
    //Reduces the number of events which the member is linked to by 1.
    subtractOneFromNumOfEvents(member);
    //Removes the member from members_queue (meaning he is no longer linked with the event).
    return pqRemoveElement(event->members_queue, member);
}

//Returns the name of the given event.
char* getEventName(Event event)
{
    if(event == NULL) {
        return NULL;
    }
    return event->event_name;
}

//Sets the given event's name to event_name.
void setEventName(Event event, char* event_name)
{
    if(event == NULL || event_name == NULL) {
        return;
    }
    if(event->event_name != NULL) {
        free(event->event_name);
    }
    
    event->event_name = malloc(strlen(event_name) + 1);
    strcpy(event->event_name, event_name);
}

//Returns the given event's date.
Date getEventDate(Event event)
{
    if(event == NULL) {
        return NULL;
    }
    return event->date;
}

//Sets the given event's date to the given date.
void setEventDate(Event event, Date date)
{
    if(event == NULL || date == NULL) {
        return;
    }
    if(event->date != NULL) {
        dateDestroy(event->date);
    }
    event->date = dateCopy(date); 
}

//Returns the given event's ID.
int getEventID(Event event)
{
    if(event == NULL) {
        return -1;
    }
    return event->event_id;
}

//Returns the number of members linked with the given event (the number of members in the members_queue in event).
int getMemberQueueSize(Event event)
{
    return pqGetSize(event->members_queue);
}

//Returns a copy of the members_queue in the given event (which is the members linked with the event).
PriorityQueue getPQEventMembers(Event event)
{
    PriorityQueue copyQueue = pqCopy(event->members_queue);
    if(copyQueue == NULL) {
        return NULL;
    }
    //Returns a copy of members_queue in the given event.
    return copyQueue;
}

//This function is used in emPrintAllEvents in event_manager which prints out to the given file the names of the members
//for each event after printing the event's details.
void getEventMembersName (Event event, FILE* output_file)
{
    //If an event doesn't have members, then it just moves to a new line in the file.
    if(pqGetSize(event->members_queue) == 0){
        fprintf(output_file, "\n");
        return;
    }
    PriorityQueue copied_members = pqCopy(event->members_queue);

    //Iterate over the members in a copy of members_queue and prints to the file the name of each member.
    PQ_FOREACH(Member, current_member, copied_members){
        fprintf(output_file, ",%s", getMemberName(current_member));
    }
    //Prints to the file a new line because everything was printed for this event.
    fprintf(output_file, "\n");

    pqDestroy(copied_members);
}



// used for testing
void printEvent(Event event)
{
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

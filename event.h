#ifndef EVENT_H_
#define EVENT_H_

#include <stdbool.h>
#include "date.h"
#include "member.h"
#include "priority_queue.h"

/** Type for defining the event */
typedef struct Event_t *Event;


/**
 * @brief Creates a new event and returns it.
 * 
 * @param event_name - The name of the new event.
 * @param event_id - The ID of the new event.
 * @param date - The date of the event.
 * @return 
 *   NULL - NULL - if allocation failed or the given parameters are illegal or NULL.
 *   The created event in case it has successfully been created.
 */
Event eventCreate(char* event_name, int event_id, Date date);

/**
 * @brief Copies the given event to a new event and return the copy.
 * 
 * @param event - The event which we want to copy.
 * @return 
 *   NULL - In case event is NULL or if allocation failed.
 *   The copy of the event of type PQElement in case the event was copied successfully.
 */
PQElement copyEvent(PQElement event);

/**
 * @brief - Destroys an event by freeing all of its contents and then freeing it.
 * 
 * @param event - The event which we want to free.
 */
void freeEvent(PQElement event);

// return true if the event have the same id 
/**
 * @brief Compares between two events by their IDs.
 * 
 * @param event1 - The first event we want in the comparison.
 * @param event2 - The second event we want in the comparison.
 * @return  
 *   true - If the events have the same ID (meaning they are the same event).
 *   false - If the events have different IDs.
 */
bool equalEvents(PQElement event1, PQElement event2);

/*      priority funcs for date     */
/**
 * @brief Copies the given Date to a new one and returns the copy.
 * 
 * @param n - The Date we want to copy.
 * @return
 *   NULL - If allocation fails.
 *   A copy of the given Date which has type of PQElement.
 */
PQElementPriority copyDate(PQElementPriority n);

/**
 * @brief Frees a date using dateDestroy function.
 * 
 * @param n - The date we want to free.
 */
void freeDate(PQElementPriority n);

/**
 * @brief Compares between two dates.
 * 
 * @param n1 - The first date which we want in the comparison.
 * @param n2 - The second date which we want in the comparison.
 * @return 
 *   0 - if both dates are the same.
 *   1 - if the second date comes before the first date.
 *   -1 - if the first date comes before the second date.
 */
int compareDate(PQElementPriority n1, PQElementPriority n2);




/**
 * @brief Adds the given member to the queue of linked members to the given event (members_queue).
 * 
 * @param event - The event which we want to link the member to.
 * @param member - The member which we want to link to the given event.
 * @return 
 *   PQ_NULL_ARGUMENT - If member or event are is NULL.
 *   PQ_SUCCESS - if the member is linked to the event successfully.
 */
PriorityQueueResult linkMemberToEvent(Event event, Member member);

/**
 * @brief Checks whether the given member is linked with the given event.
 * 
 * @param event - The event which we want to check.
 * @param member - The member which we want to check.
 * @return 
 *   true - If the member is linked with the event.
 *   false - If member or event is NULL or if they are not linked.
 */
bool isMemberLinkedToEvent(Event event, Member member);

/**
 * @brief Removes the given Member from the given Event.
 * 
 * @param event - The event which we want to remove the member from.
 * @param member - The member which we want removed from the event.
 * @return 
 *   PQ_NULL_ARGUMENT - If event or member is NULL
 *   PQ_SUCCESS - If the member gets removed from the event successfully.
 */
PriorityQueueResult removeMemberFromEvent(Event event, Member member);



/**
 * @brief Gets the name of the given event.
 * 
 * @param event - The event which we want it's name.
 * @return 
 *   A string (char*) which has event's name.
 */
char* getEventName(Event event);


/**
 * @brief Sets the given event's name to event_name.
 * 
 * @param event - The event which we want to set it's name.
 * @param event_name - The name which we want to assign to the given event.
 */
void setEventName(Event event, char* event_name);


/**
 * @brief Gets the given event's date.
 * 
 * @param event - The event which we want to receive it's date.
 * @return 
 *   NULL - If event is NULL.
 *   The date of the given event (of type Date).
 */
Date getEventDate(Event event);


/**
 * @brief Sets the given event's date to the given date.
 * 
 * @param event - The Event which we want to set it's date.
 * @param date - The Date which we want to assign to the given event.
 */
void setEventDate(Event event, Date date);

/**
 * @brief Gets the given event's ID.
 * 
 * @param event - The event which we want to receive it's ID.
 * @return 
 *   -1 - In case event is NULL.
 *   The ID of the given Event.
 */
int getEventID(Event event);

/**
 * @brief 
 * 
 * @param event 
 */
void printEvent(Event event);

/**
 * @brief 
 *   This function is used in emPrintAllEvents in event_manager which prints out to the given file the names of the members 
 *   for each event after printing the event's details.
 * @param event - The event which we want to print out it's members' names.
 * @param output_file - The file which we want to print on it the names of the member's for each event after printing it's contents.
 */
void getEventMembersName (Event event, FILE* output_file);

/**
 * @brief Gets the number of members linked with the given event (the number of members in the members_queue in event).
 * 
 * @param event - The event which we want to get it's number of linked members.
 * @return 
 *   -1 - if members_queue is NULL
 *   The number of linked members with the given event.
 */
int getMemberQueueSize(Event event);


/**
 * @brief Returns a copy of the members_queue in the given event (which is the members linked with the event).
 * 
 * @param event - The event which we want to copy it's members_queue priority queue. 
 * @return 
 *   NULL - if allocation fails.
 *   PriorityQueue which is a copy of member_events queue in event. 
 */
PriorityQueue getPQEventMembers(Event event);

#endif /* EVENT_H_ */


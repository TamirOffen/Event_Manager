#ifndef EVENT_H_
#define EVENT_H_

#include <stdbool.h>
#include "date.h"
#include "member.h"
#include "priority_queue.h"

typedef struct Event_t *Event;

// returns the event if succesful, NULL otherwise
/**
 * @brief 
 * 
 * @param event_name 
 * @param event_id 
 * @param date 
 * @return Event 
 */
Event eventCreate(char* event_name, int event_id, Date date);

/**
 * @brief 
 * 
 * @param event 
 * @return PQElement 
 */
PQElement copyEvent(PQElement event);

/**
 * @brief 
 * 
 * @param event 
 */
void freeEvent(PQElement event);

// return true if the event have the same id 
/**
 * @brief 
 * 
 * @param event1 
 * @param event2 
 * @return true 
 * @return false 
 */
bool equalEvents(PQElement event1, PQElement event2);

/*      priority funcs for date     */
/**
 * @brief 
 * 
 * @param n 
 * @return PQElementPriority 
 */
PQElementPriority copyDate(PQElementPriority n);

/**
 * @brief 
 * 
 * @param n 
 */
void freeDate(PQElementPriority n);

/**
 * @brief 
 * 
 * @param n1 
 * @param n2 
 * @return int 
 */
int compareDate(PQElementPriority n1, PQElementPriority n2);



// basically just pqInserts member into event->members_queue
/**
 * @brief 
 * 
 * @param event 
 * @param member 
 * @return PriorityQueueResult 
 */
PriorityQueueResult linkMemberToEvent(Event event, Member member);

/**
 * @brief 
 * 
 * @param event 
 * @param member 
 * @return true 
 * @return false 
 */
bool isMemberLinkedToEvent(Event event, Member member);

/**
 * @brief 
 * 
 * @param event 
 * @param member 
 * @return PriorityQueueResult 
 */
PriorityQueueResult removeMemberFromEvent(Event event, Member member);


// returns a pointer to the event_name
/**
 * @brief Get the Event Name object
 * 
 * @param event 
 * @return char* 
 */
char* getEventName(Event event);

// sets the event's name
/**
 * @brief Set the Event Name object
 * 
 * @param event 
 * @param event_name 
 */
void setEventName(Event event, char* event_name);

// returns a pointer to the date of the "event"
/**
 * @brief Get the Event Date object
 * 
 * @param event 
 * @return Date 
 */
Date getEventDate(Event event);

// set the event's date
/**
 * @brief Set the Event Date object
 * 
 * @param event 
 * @param date 
 */
void setEventDate(Event event, Date date);

/**
 * @brief Get the Event I D object
 * 
 * @param event 
 * @return int 
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
 * 
 * @param event 
 */
void printEventMembers(Event event);

/**
 * @brief Get the Event Members Name object
 * 
 * @param event 
 * @param output_file 
 */
void getEventMembersName (Event event, FILE* output_file);

/**
 * @brief Get the Member Queue Size object
 * 
 * @param event 
 * @return int 
 */
int getMemberQueueSize(Event event);

/**
 * @brief 
 * 
 * @param pq 
 * @param event 
 */
void updateTotalMembersQueue(PriorityQueue pq, Event event);

/**
 * @brief 
 * 
 * @param event 
 * @return PriorityQueue 
 */
PriorityQueue getPQEventMembers(Event event);

#endif /* EVENT_H_ */


#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "date.h"

// NOTE: there cannot be multiple events in the em that have the same name, on the same day.
//       but there can be events with the same name, but on different days.
// NOTE: ???? we cannot enter an event with a date in the past
//       ???? we cannot enter an event that has already happened in the past, WHICH ONE??

typedef struct EventManager_t* EventManager;

typedef enum EventManagerResult_t {
    EM_SUCCESS,
    EM_OUT_OF_MEMORY,
    EM_NULL_ARGUMENT,
    EM_INVALID_DATE,
    EM_INVALID_EVENT_ID,
    EM_EVENT_ALREADY_EXISTS,
    EM_EVENT_ID_ALREADY_EXISTS,
    EM_EVENT_NOT_EXISTS,
    EM_EVENT_ID_NOT_EXISTS,
    EM_INVALID_MEMBER_ID,
    EM_MEMBER_ID_ALREADY_EXISTS,
    EM_MEMBER_ID_NOT_EXISTS,
    EM_EVENT_AND_MEMBER_ALREADY_LINKED,
    EM_EVENT_AND_MEMBER_NOT_LINKED,
    EM_ERROR
} EventManagerResult;

/**
 * @brief Create an Event Manager object
 * 
 * @param date the date at which the Event Manager is valid from
 * @return 
 *      NULL in case of any errors, like invalid date, memory, etc.
 *      EventManager if succesful  
 */
EventManager createEventManager(Date date);

/**
 * @brief frees the event manager, including anything that was used by it.
 * 
 * @param em the event manager to free
 * NOTE: doesn't return anything, even in case of an error
 */
void destroyEventManager(EventManager em);

/**
 * @brief adds an event into the em on date "date".
 * 
 * @param em the event manager that will have the new event added.
 * @param event_name the name of the new event.
 * @param date the date of the new event.
 *             NOTE: the date has to be after the current date of the em.
 * @param event_id unique id number of the new event.
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_DATE - the new event's date is before the current date of the em
 *      EM_INVALID_EVENT_ID - the id number of the event is negative
 *      EM_EVENT_ID_ALREADY_EXISTS - the id number of the event already exists in em on that "date"
 *      EM_EVENT_ALREADY_EXISTS - an event with name "event_name" already exists in the em on the same date
 *      EM_OUT_OF_MEMORY - out of memory, TODO: ask on piazza because instructions are not clear
 *      EM_SUCCESS - if everything ran fine
 */
EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id);

/**
 * @brief adds a new event into the em in a number of days
 * 
 * @param em the event manager that will have the new event added.
 * @param event_name the name of the new event.
 * @param days the number of days from the current date of the em that the new event should take place.
 * @param event_id unique if number of the new event.
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_DATE - the new event's date is before the current date of the em
 *      EM_INVALID_EVENT_ID - the id number of the event is negative
 *      EM_EVENT_ID_ALREADY_EXISTS - the id number of the event already exists in em
 *      EM_EVENT_ALREADY_EXISTS - an event with name "event_name" already exists in the em
 *      EM_OUT_OF_MEMORY - out of memory, TODO: ask on piazza because instructions are not clear
 *      EM_SUCCESS - if everything ran fine
 */
EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id);

/**
 * @brief removes the event with event_id from em
 * 
 * @param em the event manager that the event will be removed from
 * @param event_id the unique id of the event 
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_EVENT_ID - if the event_id is a negative number
 *      EM_EVENT_NOT_EXISTS - the event doesn't exist in em
 *      EM_OUT_OF_MEMORY - out of memory, TODO: This will never happen?
 *      EM_SUCCESS - if everything ran fine
 */
EventManagerResult emRemoveEvent(EventManager em, int event_id);

/**
 * @brief changes the date of event with event_id from its previous date to "new_date"
 * 
 * @param em the event manager where the date of the event will be changed
 * @param event_id the unique id of the event
 * @param new_date the new date of the event
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_DATE - the new_date is before the current date of the em
 *      EM_INVALID_EVENT_ID - event_id is a negative number
 *      EM_EVENT_ID_NOT_EXISTS - event_id does not exist in the em
 *      EM_EVENT_ALREADY_EXISTS - an event with the same name already exists on "new_date"
 *      EM_OUT_OF_MEMORY - out of memory, TODO: the user needs to fix it or the programmer?
 *      EM_SUCCESS - if everything ran fine
 */
EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date);

/**
 * @brief adds a new memeber by the name "member_name" with "member_id" into the em
 * NOTE: this new member is in the em for life, i.e. he/she cannot be removed
 * 
 * @param em the event manager where we will want to add the new member
 * @param member_name the name of the new member
 * @param member_id the unique id number of the new member
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_MEMBER_ID - member_id is a negative number
 *      EM_MEMBER_ID_ALREADY_EXISTS - member_id already exists in em
 *      EM_OUT_OF_MEMORY - out of memory, TODO: user needs to fix it or the progammer?
 *      EM_SUCCESS - if everything ran fine
 */
EventManagerResult emAddMember(EventManager em, char* member_name, int member_id);

/**
 * @brief adds the member with "member_id" to the list of students that are in charge of event with "event_id"
 * 
 * @param em the event manager where we want to add the connection between "member_id" and "event_id"
 * @param member_id the unique id of the member
 * @param event_id the unique id of the event 
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_EVENT_ID - event_id is a negative number
 *      EM_INVALID_MEMBER_ID - member_id is a negative number
 *      EM_EVENT_ID_NOT_EXISTS - event_id does not exist in the em
 *      EM_MEMBER_ID_NOT_EXISTS - member_id does not exist in the em
 *      EMD_EVENT_AND_MEMBER_ALREADY_LINKED - the member is aleady linked with event_id
 *      EM_OUT_OF_MEMORY - out of memory, TODO: programmer's or user's responsibility?
 *      EM_SUCCESS - if everything ran fine       
 */
EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id);

/**
 * @brief removes the member with "member_id" from the students in charge of event with "event_id"
 * 
 * @param em teh event manager where the member will have his connection removed from event_id
 * @param member_id the unique id of the member
 * @param event_id the unique if of the event
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_EVENT_ID - event_id is a negative number
 *      EM_INVALID_MEMBER_ID - member_id is a negative number
 *      EM_EVENT_ID_NOT_EXISTS - event_id does not exist in the em
 *      EM_MEMBER_ID_NOT_EXISTS - member_id does not exist in the em
 *      EM_EVENT_AND_MEMBER_NOT_LINKED - the member_id and event_id are not linked
 *      EM_OUT_OF_MEMORY - out of memory, TODO: programmer's or user's responsibility?
 *      EM_SUCCESS - if everything ran fine    
 */
EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id);

/**
 * @brief advances the em's current date by "days" amount of days
 * NOTE: removes the events that were supposed to have happened
 * 
 * @param em the event manager where we want to advance the date
 * @param days number of days that we want to advance the date by
 * @return EventManagerResult:
 *      EM_NULL_ARGUMENT - one of the arguments are NULL
 *      EM_INVALID_DATE - if days <= 0
 *      EM_OUT_OF_MEMORY - out of memory, TODO: programmer's or user's responsibility?
 *      EM_SUCCESS - if everything ran fine        
 */
EventManagerResult emTick(EventManager em, int days);

/**
 * @brief returns the number of future events in the em
 * 
 * @param em the event manager 
 * @return int:
 *      -1 - if em is NULL
 *      >= 0 - otherwise
 */
int emGetEventsAmount(EventManager em);

/**
 * @brief returns the name of the event that's supposed to occur next
 * NOTE: if there are multiple events that will happen next on the same date,
 *       than return the one entered first into the em.
 * 
 * @param em the event manager
 * @return char*
 *      NULL - if em is NULL
 *      else: return the pointer of the name of the next event
 */
char* emGetNextEvent(EventManager em);

/**
 * @brief prints to a file by name "file_name" in order the list of events, their dates, and the members in charge of them
 * NOTE: "in order" = by their dates
 * NOTE: if multiple events are on the same date, than print by the ones entered first
 * NOTE: members are printed by increasing order of their id's
 * EXAMPLE: if we have event1 on 1.1.2021 with member1, member2; event2 on 2.2.2021 with member1:
 *      event1,1.1.2021,member1,member2
 *      event2,2.2.2021,member2
 * 
 * @param em the event manager
 * @param file_name the name of the file where we will write the events from em onto
 * NOTE: this func does not return any errors or return values of any kind
 */
void emPrintAllEvents(EventManager em, const char* file_name);

/**
 * @brief writes into "file_name" the names of all of the members in em, and how many events they are in charge of
 * NOTE: the member in charge of the most events is printed first, etc.
 * NOTE: if multiple members have the same amount of events, than print by *lowest* member_id
 * NOTE: if a member is in charge of 0 events, he/she will not be printed
 * EXAMPLE: if we have event1 on 1.1.2021 with member1, member2; event2 on 2.2.2021 with member1:
 *      member1,2
 *      member2,1
 * 
 * @param em the event manager
 * @param file_name the name of the file that we will write into
 * NOTE: this func does not return any errors or return values of any kind
 */
void emPrintAllResponsibleMembers(EventManager em, const char* file_name);


//FOR TESTING:
// void printAllEventsAndTheirMembers(EventManager em);
// void printAllMembers(EventManager em);
// void getFirstMember(EventManager em);
// void getNextMember(EventManager em);
// void printEM(EventManager em);


// void emPrintAllResponsibleMembersTEST(EventManager em, const char* file_name);

#endif //EVENT_MANAGER_H

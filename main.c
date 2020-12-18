emChangeEventDate#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"
#include "member.h"
#include "string.h"

int main() {

    Date date1 = dateCreate(1, 3, 2000);
    Date date2 = dateCreate(1, 2, 2000); //before date1/3/4
    Date date3 = dateCreate(5, 3, 2000);
    Date date4 = dateCreate(9, 2, 2011);
    EventManager em = createEventManager(date1);

    //emAddEventByDate() Test:
    if(emAddEventByDate(em, "event 1", date1, 1) == EM_SUCCESS) {
        printf("Test1\n");
    }
    if(emAddEventByDate(em, "event BAD DATE", date2, 2) == EM_INVALID_DATE) {
        printf("Test2\n");
    }
    if(emAddEventByDate(em, "event NEG ID NUM", date1, -1) == EM_INVALID_EVENT_ID) {
        printf("Test3\n");
    }
    if(emAddEventByDate(em, "event 2", date3, 2) == EM_SUCCESS) {
        printf("Test4\n");
    }
    if(emAddEventByDate(em, "event SAME ID", date1, 1) == EM_EVENT_ID_ALREADY_EXISTS) {
        printf("Test5\n");
    }
    if(emAddEventByDate(em, "event 2", date3, 3) == EM_EVENT_ALREADY_EXISTS) {
        printf("Test6\n");
    }
    if(emAddEventByDate(em, "event 4", date4, 4) == EM_SUCCESS) {
        printf("Test7\n");
    }

    //emAddEventByDiff() Tests: More testing needed
    if(emAddEventByDiff(em, "event 3", 5, 3) == EM_SUCCESS) {
        printf("Test8\n");
    }
    if(emAddEventByDiff(em, "event 2", 4, 5) == EM_EVENT_ALREADY_EXISTS) {
        printf("Test9\n");
    }

    //emRemoveEvent() Tests:
    if(emRemoveEvent(em, 3) == EM_SUCCESS) {
        printf("Test10\n");
    }
    if(emRemoveEvent(em, 3) == EM_EVENT_NOT_EXISTS) {
        printf("Test11\n");
    }
    if(emRemoveEvent(em, -1) == EM_INVALID_EVENT_ID) {
        printf("Test12\n");
    }

    //emChangeEventDate() Tests: TODO: more tests
    if(emChangeEventDate(em, 1, date2) == EM_INVALID_DATE) {
        printf("Test13\n");
    }
    if(emChangeEventDate(em, 3, date1) == EM_EVENT_ID_NOT_EXISTS) {
        printf("Test14\n");
    }
    emAddEventByDate(em, "event 10", date1, 5);
    if(emChangeEventDate(em, 2, date4) == EM_SUCCESS) {
        printf("Test15\n");
    }
    if(emChangeEventDate(em, 2, date3) == EM_SUCCESS) {
        printf("Test16\n");
    }
    if(emChangeEventDate(em, 2, date2) == EM_INVALID_DATE) {
        printf("Test17\n");
    }
    if(emChangeEventDate(em, 5, date4) == EM_SUCCESS) {
        printf("Test18\n");
    }
    emRemoveEvent(em, 5);


    printEM(em);
    

    // destroyEventManager(em);
    // dateDestroy(date1);
    // dateDestroy(date2);
    // dateDestroy(date3);
    // dateDestroy(date4);
    

    return 0;
}


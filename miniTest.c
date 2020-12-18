#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"
#include "member.h"
#include "string.h"

int main() {

    Date start_date = dateCreate(1, 12, 2020);
    EventManager em = createEventManager(start_date);

    char *event_name1 = "event1";
    char *event_name2 = "event2";
    char *event_name3 = "event3";
    char *event_name4 = "event4";
    char *event_name5 = "event5";

    Date event_date1 = dateCreate(1, 12, 2020);
    Date event_date2 = dateCreate(5, 12, 2020);
    Date event_date3 = dateCreate(10, 12, 2020);
    Date event_date4 = dateCreate(11, 06, 2021);
    Date event_date5 = dateCreate(1, 11, 2020);

    printf("1: %d\n", emAddEventByDate(em, event_name1, event_date1, 1));
    printf("2: %d\n", emAddEventByDate(em, event_name2, event_date2, 2));
    printf("3: %d\n", emAddEventByDate(em, event_name3, event_date3, 3));
    printf("4: %d\n", emAddEventByDate(em, event_name4, event_date4, 4));
    printf("5: %d\n", emAddEventByDate(em, event_name5, event_date5, 5));
    printf("6: %d\n", emGetEventsAmount(em));

    Date new_date_to_event_4 = dateCreate(4, 12, 2020);
    printf("7: %d\n", emChangeEventDate(em, 8, new_date_to_event_4));
    // printEM(em);
    printf("8: %d\n", emChangeEventDate(em, 4, new_date_to_event_4));

    char *event_name_same_as_1 = "event1";
    printf("9: %d\n", emAddEventByDate(em, event_name_same_as_1, event_date3, 6));
    printf("10: %d\n", emChangeEventDate(em, 6, event_date1));

    printf("11: %d\n", emGetEventsAmount(em));

    printf("12: %d\n", emRemoveEvent(em, 6));

    printf("13: %d\n", strcmp(emGetNextEvent(em), event_name1) == 0);

    printEM(em);

    printf("14: %d\n", emAddMember(em, "yan1", 1));
    printf("15: %d\n", emAddMember(em, "yan2", 2));
    printf("16: %d\n", emAddMember(em, "yan3", 3));
    printf("17: %d\n", emAddMember(em, "yan4", 4));
    printf("18: %d\n", emAddMember(em, "yan5", 5));
    printf("19: %d\n", emAddMember(em, "yan6", 5));

    /*  member 1- events 1,2,3,4
        member 2 - events 2,3
        member 3 - events 2
        member 4 - events 2
        member 5 - events 2,4*/
    printf("19: %d\n", emAddMemberToEvent(em, 1, 1) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 1, 2) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 1, 3) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 1, 4) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 2, 2) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 2, 3) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 3, 2) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 4, 2) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 5, 1) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 5, 2) == EM_SUCCESS);
    printf("19: %d\n", emAddMemberToEvent(em, 5, 4) == EM_SUCCESS);

    printf("x: %d\n", emAddMemberToEvent(em, 2, 10) == EM_EVENT_ID_NOT_EXISTS);
    printf("x: %d\n", emAddMemberToEvent(em, 8, 1) == EM_MEMBER_ID_NOT_EXISTS);
    printf("x: %d\n", emAddMemberToEvent(em, 1, 1) == EM_EVENT_AND_MEMBER_ALREADY_LINKED); 
    printf("x: %d\n", emRemoveMemberFromEvent(em, 1, 1) == EM_SUCCESS);
    printf("x: %d\n", emAddMemberToEvent(em, 1, 1) == EM_SUCCESS);
    printf("x: %d\n", emRemoveMemberFromEvent(em, 2, 10) == EM_EVENT_ID_NOT_EXISTS);
    printf("x: %d\n", emRemoveMemberFromEvent(em, 8, 1) == EM_MEMBER_ID_NOT_EXISTS);
    printf("x: %d\n", emRemoveMemberFromEvent(em, 2, 1) == EM_EVENT_AND_MEMBER_NOT_LINKED);


    // printEM(em);

    printf("x1: %d\n", emTick(em, 4) == EM_SUCCESS);
    printEM(em);
    printf("\n");
    emPrintAllResponsibleMembers(em, "emPrintAllResponsibleMembers.txt");
    // printEM(em);

    // emPrintAllEvents(em, "emPrintAllEvents.txt");
    // emPrintAllResponsibleMembers(em, "emPrintAllResponsibleMembers.txt");

    return 0;
}



#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"
#include "member.h"
#include "string.h"

int main() {

    
    Date date = dateCreate(1, 3, 2020);
    Date dateChange = dateCreate(2,3,2020);
    EventManager em = createEventManager(date);
    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    emAddEventByDate(em, "event 2", dateChange, 2);   
    emAddEventByDate(em, "event 1", date, 1);  


    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    emAddMember(em, "Tamir", 1);
    emAddMember(em, "Nabeeh", 2);
    emAddMember(em, "Bob", 3);


    emAddMemberToEvent(em, 1, 1);
    emAddMemberToEvent(em, 2, 1);
    emAddMemberToEvent(em, 3, 2);

    emRemoveMemberFromEvent(em, 1, 1);
    emRemoveMemberFromEvent(em, 3, 2);
    // printf("%d\n", emRemoveMemberFromEvent(em, 2, 1));
    // printf("%d\n", emRemoveMemberFromEvent(em, 2, 1));
    // printf("%d\n", emRemoveMemberFromEvent(em, 3, 2));

    emRemoveEvent(em, 30);

    emTick(em, 1);

    printf("\n");
    printEM(em);


    // printf("%d\n", emRemoveEvent(em, 1));
    // printAllEventsAndTheirMembers(em);
    


    destroyEventManager(em);
    dateDestroy(date);
    dateDestroy(dateChange);
    
    

    // Date date = dateCreate(1, 3, 2020);
    // Date dateBad = dateCreate(1, 3, 2019);
    // EventManager em = createEventManager(date);
    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    // emAddEventByDate(em, "event 1", dateBad, 1);
    // printf("Number of Events: %d\n", emGetEventsAmount(em));


    // destroyEventManager(em);
    // dateDestroy(date);
    // dateDestroy(dateBad);

    // Event event = eventCreate("event 1", 1, date);
    // printEvent(event);
    // Event eventCopy = copy_event(event);
    // printEvent(eventCopy);

    // emAddEventByDate(em, "event 1", date, 1);
    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    // //should not work
    // if(emAddEventByDate(em, "event 1", date, 2) == EM_EVENT_ALREADY_EXISTS) {
    //     printf("works1\n");
    // }

    // //should not work
    // if(emAddEventByDate(em, "event 2", date, 1) == EM_EVENT_ID_ALREADY_EXISTS) {
    //     printf("works2\n");
    // }
    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    //should work
    // if(emAddEventByDate(em, "event 2", date, 2) == EM_SUCCESS) {
    //     printf("works3\n");
    // }
    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    // emAddEventByDiff(em, "event 3", 2, 3);
    // printf("Number of Events: %d\n", emGetEventsAmount(em));

    

    // Member member1 = createMember("Tamir Offen", 1);
    // printMember(member1);

    // Member member1Copy = copy_member(member1);
    // printMember(member1Copy);

    // printf("members are the same: %d\n", equal_members(member1, member1Copy));


    // free_member(member1);
    // free_member(member1Copy);
    

    // destroyEventManager(em);//Should check Valgrind
    // dateDestroy(date);
    // free_event(event);
    // free_event(eventCopy);

    return 0;
}


#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"
#include "member.h"
#include "string.h"

int main() {

    Date date = dateCreate(1, 3, 2020);
    freeDate(date);
    // EventManager em = createEventManager(date);

    // printf("Number of Events: %d\n", emGetEventsAmount(em));


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


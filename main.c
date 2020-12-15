#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"
#include "member.h"

int main() {

    Date date = dateCreate(1, 3, 2020);
    EventManager em = createEventManager(date);

    printf("Number of Events: %d\n", emGetEventsAmount(em));


    Event event = eventCreate("event 1", 1);
    printEvent(event);

    Event eventCopy = copy_event(event);
    printEvent(eventCopy);

    free_event(event);
    free_event(eventCopy);

    Member member1 = createMember("Tamir Offen", 1);
    printMember(member1);

    Member member1Copy = copy_member(member1);
    printMember(member1Copy);

    printf("members are the same: %d\n", equal_members(member1, member1Copy));


    free_member(member1);
    free_member(member1Copy);
    

    destroyEventManager(em);//Should check Valgrind


    return 0;
}


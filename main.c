#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"
#include "member.h"

int main() {

    // Date date = dateCreate(1, 3, 2020);
    // EventManager em = createEventManager(date);

    // printf("Number of Events: %d\n", emGetEventsAmount(em));


    Event event = eventCreate("event 1", 1);
    printEvent(event);

    Event eventCopy = copy_event(event);
    printEvent(eventCopy);

    free_event(event);
    free_event(eventCopy);

    Member member1 = createMember("Tamir Offen", 1);
    printMember(member1);

    free_member(member1);
    

    // destroyEventManager(em);//Should check Valgrind


    return 0;
}


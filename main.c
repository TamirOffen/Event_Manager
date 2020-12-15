#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"
#include "event.h"

int main() {

    Date date = dateCreate(1, 3, 2020);
    EventManager em = createEventManager(date);

    printf("Number of Events: %d\n", emGetEventsAmount(em));


    Event event = eventCreate("event 18", 123);
    printEvent(event);

    Event eventCopy = copy_event(event);
    printEvent(eventCopy);

    destroyEventManager(em);//Should check Valgrind


    return 0;
}


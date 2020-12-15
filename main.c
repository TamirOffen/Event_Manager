#include <stdio.h>
#include "priority_queue.h"
#include "event_manager.h"

int main() {

    Date date = dateCreate(1, 3, 2020);
    EventManager em = createEventManager(date);

    printf("Number of Events: %d\n", emGetEventsAmount(em));


    return 0;
}


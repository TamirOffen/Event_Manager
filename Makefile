CC=gcc
OBJS_PRIORITY_QUEUE=priority_queue.o priority_queue_tests.o
OBJS_EVENT_MANAGER=event_manager.o date.o event.o member.o event_manager_tests.o libpriority_queue.a
EXEC_PRIORITY_QUEUE=priority_queue
EXEC_EVENT_MANAGER=event_manager
DEBUG_FLAG = -g #?
COMP_FLAG=-std=c99 -Wall -pedantic-errors -Werror $(DEBUG_FLAG) 
LIB_FLAGS=-L. -lpriority_queue

all : $(EXEC_EVENT_MANAGER) $(EXEC_PRIORITY_QUEUE)
$(EXEC_EVENT_MANAGER) : $(OBJS_EVENT_MANAGER)
	$(CC) $(COMP_FLAG) $(OBJS_EVENT_MANAGER) -o event_manager $(LIB_FLAGS)

$(EXEC_PRIORITY_QUEUE) : $(OBJS_PRIORITY_QUEUE)
	$(CC) $(COMP_FLAG) $(OBJS_PRIORITY_QUEUE) -o priority_queue

priority_queue.o : priority_queue.c priority_queue.h
	$(CC) -c $(COMP_FLAG) $*.c

priority_queue_tests.o : tests/priority_queue_tests.c tests/test_utilities.h priority_queue.h
	$(CC) -c $(COMP_FLAG) tests/priority_queue_tests.c

date.o : date.c date.h
	$(CC) -c $(COMP_FLAG) $*.c

member.o : member.c member.h priority_queue.h
	$(CC) -c $(COMP_FLAG) $*.c
 
event.o : event.h date.h member.h priority_queue.h
	$(CC) -c $(COMP_FLAG) $*.c

event_manager.o : event_manager.c event.h date.h member.h priority_queue.h event_manager.h
	$(CC) -c $(COMP_FLAG) $*.c

event_manager_tests.o : tests/event_manager_tests.c tests/test_utilities.h event_manager.h date.h event.h member.h
	$(CC) -c $(COMP_FLAG) tests/event_manager_tests.c

clean:
	rm -f $(OBJS_EVENT_MANAGER) $(OBJS_PRIORITY_QUEUE) $(EXEC_PRIORITY_QUEUE) $(EXEC_EVENT_MANAGER)

cmake_minimum_required(VERSION 3.0)

set(MATAM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MATAM_FLAGS_RELEASE "${MATAM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${MATAM_FLAGS_DEBUG})

project(app VERSION 0.1 LANGUAGES C)

# link_directories(.)

add_executable(
    # add source c files here
    app
    main.c
    member.c
    event.c
    date.c
    event_manager.c
    priority_queue.c
)

#target_link_libraries(app libpriority_queue.a) //we can only use this on the technion servers
# target_link_libraries(app priority_queue.o)   #NOTE: this library only works on mac

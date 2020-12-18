#ifndef MEMBER_H_
#define MEMBER_H_

#include <stdbool.h>
#include "priority_queue.h"

typedef struct Member_t *Member;

typedef enum MemberResult_t {
    MEMBER_SUCCESS,
    //add more
} MemberResult;

Member createMember(char* member_name, int member_id);

PQElement copy_member(PQElement member);
void free_member(PQElement member);

// return true if the members have the same id //TODO: maybe wrong
bool equal_members(PQElement member1, PQElement member2);

/*     Priority funcs for the id of the member     */
PQElementPriority copy_member_id(PQElementPriority member_priority);
void free_member_id(PQElementPriority member_priority);

// compares the members' ids, which is their priority
// returns 0 if the members have the same id
// returns 1 if member1.id < member2.id
// return -1 if member1.id > member2.id
int compare_members_id(PQElementPriority member_priority1, PQElementPriority member_priority2);


/*      priority funcs to compare the order of ints, used in total_member PQ        */
PQElementPriority copyInt(PQElementPriority n);
void freeInt(PQElementPriority n);
int compareInts(PQElementPriority n1, PQElementPriority n2);


// returns a pointer to the event_name
char* getMemberName(Member member);

// sets the event's name
void setMemberName(Member member, char* member_name);

int getMemberNumOfEvents(Member member);
int* getMemberNumOfEventsPointer(Member member);

void setMemberNumOfEvents(Member member, int new_num_of_events);


int* getMemberIdPointer(Member member);


void printMember(Member member);

void tickMemberNumOfEvents(Member member);
void memberMinusOneEventCount(Member member);


#endif //TODO: add the /* ...

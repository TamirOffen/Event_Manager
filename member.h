#ifndef MEMBER_H_
#define MEMBER_H_

#include <stdbool.h>
#include "priority_queue.h"

typedef struct Member_t *Member;

typedef enum MemberResult_t {
    MEMBER_SUCCESS,
    //add more
} MemberResult;


PQElement copy_member(PQElement member);
void free_member(PQElement member);

// return true if the members have the same id //TODO: maybe wrong
bool equal_members(PQElement member1, PQElement member2);

/*     Priority funcs for the id of the member     */
PQElementPriority copy_member_id(PQElementPriority member_priority);
void free_member_id(PQElementPriority member_priority);

// compares the members' ids
// returns 0 if the members have the same id
// returns 1 if member1.id < member2.id
// return -1 if member1.id > member2.id
int compareMembersPriority(Member member1, Member member2);


/*      priority funcs to compare the order of ints, used in total_member PQ        */
PQElementPriority copyInt(PQElementPriority n);
void freeInt(PQElementPriority n);
int compareInts(PQElementPriority n1, PQElementPriority n2);













#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "member.h"



struct Member_t {
    char* member_name;
    int member_id; //priority
    int num_of_events;
};


PQElement copy_member(PQElement member) {
    return NULL;
}
void free_member(PQElement member) {
    return;
}

// return true if the members have the same id //TODO: maybe wrong
bool equal_members(PQElement member1, PQElement member2) {
    return false;
}

/*     Priority funcs for the id of the member     */
PQElementPriority copy_member_id(PQElementPriority member_priority){
    return NULL;
}
void free_member_id(PQElementPriority member_priority) {
    return;
}

// compares the members' ids
// returns 0 if the members have the same id
// returns 1 if member1.id < member2.id
// return -1 if member1.id > member2.id
int compareMembersPriority(Member member1, Member member2) {
    return -10;
}



// These are the funcs for the total_members PQ
PQElementPriority copyInt(PQElementPriority n) {
    if (!n) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(int *) n;
    return copy;
}

void freeInt(PQElementPriority n) {
 if (n != NULL) {
      free(n);
    }
    n = NULL;
}

int compareInts(PQElementPriority n1, PQElementPriority n2) {
    return (*(int *) n1 - *(int *) n2);
}







#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "member.h"
#include "strings.h"

struct Member_t {
    char* member_name;
    int member_id; //priority
    int num_of_events;
};

Member createMember(char* member_name, int member_id) {
    if(member_name == NULL || member_id < 0) {
        return NULL;
    }

    Member member = malloc(sizeof(*member));
    if(member == NULL) {
        return NULL; //out of memory
    }

    member->member_name = malloc(sizeof(char) * strlen(member_name) + 1);
    if(member->member_name == NULL) {
        free(member);
        return NULL; //out of memory
    }
    strcpy(member->member_name, member_name);

    member->member_id = member_id;
    member->num_of_events = 0; //each member starts off managing 0 events

    return member;
}

PQElement copy_member(PQElement member) {
    return NULL;
}

void free_member(PQElement member) {
    if(member == NULL) {
        return;
    }

    free(((Member)member)->member_name);
    free(((Member)member));
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
int compare_members_id(PQElementPriority member_priority1, PQElementPriority member_priority2) {
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




void printMember(Member member) {
    printf("Member Name: %s,\tMember ID: %d\n", member->member_name, member->member_id);
}




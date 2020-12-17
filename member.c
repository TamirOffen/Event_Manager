#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "member.h"
#include "string.h"

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
    if(member == NULL) {
        return NULL;
    }
    
    Member member_copy = malloc(sizeof(*member_copy));
    if(member_copy == NULL) {
        return NULL;
    }

    Member member_parameter = (Member)member;
    
    member_copy->member_name = malloc(sizeof(char) * strlen(member_parameter->member_name) + 1);
    if(member_copy->member_name == NULL) {
        free(member_copy);
        return NULL;
    }
    strcpy(member_copy->member_name, member_parameter->member_name);

    member_copy->member_id = member_parameter->member_id;
    member_copy->num_of_events = member_parameter->num_of_events;
    
    return member_copy;

}

void free_member(PQElement member) {
    if(member == NULL) {
        return;
    }

    free(((Member)member)->member_name);
    free(((Member)member));

    member = NULL; //TODO: CHECK THIS!
}

// return true if the members have the same id //TODO: maybe wrong
bool equal_members(PQElement member1, PQElement member2) {
    if(((Member)member1)->member_id == ((Member)member2)->member_id) {
        return true;
    }
    return false;
}


/*     Priority funcs for the id of the member     */
PQElementPriority copy_member_id(PQElementPriority member_priority){
    if(member_priority == NULL) {
        return NULL;
    }

    int* member_priority_copy = malloc(sizeof(member_priority_copy));
    if(member_priority_copy == NULL) {
        return NULL;
    }
    *member_priority_copy = *(int*)member_priority;
    return member_priority_copy;
}

//TODO: code duplication with bottom funcs
void free_member_id(PQElementPriority member_priority) {
    if(member_priority != NULL) {
        free(member_priority);
    }
    member_priority = NULL;
}

// compares the members' ids
// returns 0 if the members have the same id
// returns 1 if member1.id < member2.id
// return -1 if member1.id > member2.id
int compare_members_id(PQElementPriority member_priority1, PQElementPriority member_priority2) {
    int priority1 = *(int *)member_priority1;
    int priority2 = *(int *)member_priority2;
    if(priority1 < priority2) {
        return 1;
    } else if(priority1 > priority2) {
        return -1;
    } else {
        return 0;
    }
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



// GETTERS AND SETTES:
char* getMemberName(Member member) {
    if(member == NULL) {
        return NULL;
    }
    return member->member_name;
}

void setMemberName(Member member, char* member_name) {
    if(member == NULL || member_name == NULL) {
        return;
    }
    if(member->member_name != NULL) {
        free(member->member_name);
    }

    //TODO: might case memory issues here
    member->member_name = malloc(strlen(member_name) + 1);
    strcpy(member->member_name, member_name);
}


int getMemberNumOfEvents(Member member);

void setMemberNumOfEvents(Member member, int new_num_of_events);


int* getMemberIdPointer(Member member) {
    if(member == NULL) {
        return NULL;
    }

    return &(member->member_id);
}



void printMember(Member member) {
    printf("\tMember Name: %s,\tMember ID: %d\n", member->member_name, member->member_id);
}
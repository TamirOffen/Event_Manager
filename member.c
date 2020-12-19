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

//Creates a new Member.
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
    member->num_of_events = 1; 

    return member;
}

//Copies the given member to a new one and returns it.
PQElement copyMember(PQElement member) {
    if(member == NULL) {
        return NULL;
    }
    
    Member member_copy = malloc(sizeof(*member_copy));
    if(member_copy == NULL) {
        return NULL;
    }

    //Converting PQElement member to Member.
    Member member_parameter = (Member)member;
    
    //Copy the contents of the member.
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

//Frees the member contents (his name in this case), and then frees the member.
void freeMember(PQElement member) {
    if(member == NULL) {
        return;
    }

    //Free the member with it's contents.
    free(((Member)member)->member_name);
    free(((Member)member));

    member = NULL; 
}

//Checks whether member1 and member2 are the same member by comparing their IDs.
bool equalMembers(PQElement member1, PQElement member2) {
    if(((Member)member1)->member_id == ((Member)member2)->member_id) {
        return true;
    }
    return false;
}


/*     Priority funcs for the id of the member     */

//Gets a member ID, copies it to a new ID and returns it.
PQElementPriority copyMemberID(PQElementPriority member_priority){
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

//Gets a member ID and frees it.
void freeMemberID(PQElementPriority member_priority) {
    if(member_priority != NULL) {
        free(member_priority);
    }
    member_priority = NULL;
}

//Compares between two members' IDs according to their priority.
int compareMembersID(PQElementPriority member_priority1, PQElementPriority member_priority2) {
    //Converting them to int before checking.
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


/*     Funcs for the total_members PQ    */

//Gets a PQElementPriority, copies it into an int variable and returns it.
PQElementPriority copyInt(PQElementPriority n) {
    if (n == NULL) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    //Convert n to int before returning.
    *copy = *(int *) n;
    return copy;
}

//Frees a PQElementPriority as an int.
void freeInt(PQElementPriority n) {
    if (n != NULL) {
        free(n);
    }
    n = NULL;
}

//Compares between two ints.
int compareInts(PQElementPriority n1, PQElementPriority n2) {
    return (*(int *) n1 - *(int *) n2);
}


/*       GETTERS AND SETTES:     */

//Gets a Member and returns it's name.
char* getMemberName(Member member) {
    if(member == NULL) {
        return NULL;
    }
    return member->member_name;
}

//Sets the given member's name to a new name (member_name).
void setMemberName(Member member, char* member_name) {
    if(member == NULL || member_name == NULL) {
        return;
    }
    if(member->member_name != NULL) {
        free(member->member_name);
    }

    member->member_name = malloc(strlen(member_name) + 1);
    strcpy(member->member_name, member_name);
}

//Returns the number of events which the given member is linked to.
int getMemberNumOfEvents(Member member){
    return member->num_of_events;
}

//Returns a pointer to the number of events which the given member is linked to.
int* getMemberNumOfEventsPointer(Member member) {
    return &(member->num_of_events);
}

//Sets the number of events which the given member is linked to, to a new value.
void setMemberNumOfEvents(Member member, int new_num_of_events) {
    member->num_of_events = new_num_of_events;
}

//Increases the given member's number of linked events (num_of_events) by 1.
void tickMemberNumOfEvents(Member member){
    member->num_of_events++;
}

//Decreases the given member's number of linked events (num_of_events) by 1.
void subtractOneFromNumOfEvents(Member member) {
    member->num_of_events--;
}

//Returns a pointer to the ID of the given member (member_id);
int* getMemberIdPointer(Member member) {
    if(member == NULL) {
        return NULL;
    }

    return &(member->member_id);
}


// for testing only
void printMember(Member member) {
    printf("\tMember Name: %s,\tMember ID: %d\t#Events: %d\n", member->member_name, member->member_id, member->num_of_events);
}



#ifndef MEMBER_H_
#define MEMBER_H_

#include <stdbool.h>
#include "priority_queue.h"

typedef struct Member_t *Member;

/**
 * @brief Create a Member object
 * 
 * @param member_name 
 * @param member_id 
 * @return Member 
 */
Member createMember(char* member_name, int member_id);

/**
 * @brief 
 * 
 * @param member 
 * @return PQElement 
 */
PQElement copyMember(PQElement member);

/**
 * @brief 
 * 
 * @param member 
 */
void freeMember(PQElement member);

// return true if the members have the same id
/**
 * @brief 
 * 
 * @param member1 
 * @param member2 
 * @return true 
 * @return false 
 */
bool equalMembers(PQElement member1, PQElement member2);

/**
 * @brief 
 * 
 * @param member_priority 
 * @return PQElementPriority 
 */
PQElementPriority copyMemberID(PQElementPriority member_priority);

/**
 * @brief 
 * 
 * @param member_priority 
 */
void freeMemberID(PQElementPriority member_priority);

// compares the members' ids, which is their priority
// returns 0 if the members have the same id
// returns 1 if member1.id < member2.id
// return -1 if member1.id > member2.id
/**
 * @brief 
 * 
 * @param member_priority1 
 * @param member_priority2 
 * @return int 
 */
int compareMembersID(PQElementPriority member_priority1, PQElementPriority member_priority2);


/*      priority funcs to compare the order of ints, used in total_member PQ        */
/**
 * @brief 
 * 
 * @param n 
 * @return PQElementPriority 
 */
PQElementPriority copyInt(PQElementPriority n);

/**
 * @brief 
 * 
 * @param n 
 */
void freeInt(PQElementPriority n);

/**
 * @brief 
 * 
 * @param n1 
 * @param n2 
 * @return int 
 */
int compareInts(PQElementPriority n1, PQElementPriority n2);


// returns a pointer to the event_name
/**
 * @brief 
 * 
 * @param member 
 * @return char* 
 */
char* getMemberName(Member member);

// sets the event's name
/**
 * @brief Set the Member Name object
 * 
 * @param member 
 * @param member_name 
 */
void setMemberName(Member member, char* member_name);

/**
 * @brief 
 * 
 * @param member 
 * @return int 
 */
int getMemberNumOfEvents(Member member);

/**
 * @brief 
 * 
 * @param member 
 * @return int* 
 */
int* getMemberNumOfEventsPointer(Member member);

/**
 * @brief Set the Member Num Of Events object
 * 
 * @param member 
 * @param new_num_of_events 
 */
void setMemberNumOfEvents(Member member, int new_num_of_events);

/**
 * @brief Get the Member Id Pointer object
 * 
 * @param member 
 * @return int* 
 */
int* getMemberIdPointer(Member member);

/**
 * @brief (For Testing)
 * 
 * @param member 
 */
void printMember(Member member);

/**
 * @brief 
 * 
 * @param member 
 */
void tickMemberNumOfEvents(Member member);

/**
 * @brief 
 * 
 * @param member 
 */
void subtractOneFromNumOfEvents(Member member);


#endif /* MEMBER_H_ */



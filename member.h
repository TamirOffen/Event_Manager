#ifndef MEMBER_H_
#define MEMBER_H_

#include <stdbool.h>
#include "priority_queue.h"

typedef struct Member_t *Member;

/**
 * @brief Create a Member object
 * 
 * @param member_name - Name of the member.
 * @param member_id - ID if the member.
 * @return
 *   NULL - If allocation failed or member params are illegal.
 *   A new Member in case of success.
 */
Member createMember(char* member_name, int member_id);

/**
 * @brief Copies the given member to a new one and returns it.
 * 
 * @param member - The member which the user wants a copy of.
 * @return
 *   NULL - If allocation failed or member is NULL.
 *   A new PQElement which is a copy of member.
 */
PQElement copyMember(PQElement member);

/**
 * @brief Frees the member contents (his name in this case), and then frees the member.
 * 
 * @param member - The member which the user wants to free.
 */
void freeMember(PQElement member);

/**
 * @brief Checks whether member1 and member2 are the same member by comparing their IDs.
 * 
 * @param member1 - The first member which the user wants in the comparison.
 * @param member2 - The second member which the user wants in the comparison.
 * @return
 *   true - In case member1 and member2 have the same ID (meaning they are the same person).
 *   false - In case member1 and member2 have different IDs.
 */
bool equalMembers(PQElement member1, PQElement member2);

/**
 * @brief Gets a member ID, copies it to a new ID and returns it.
 * 
 * @param member_priority - The ID which the user wants to copy.
 * @return
 *   NULL - If allocation failed or member_priority is NULL.
 *   A new PQElementPriority which is a copy of member_priority (member's ID).  
 */
PQElementPriority copyMemberID(PQElementPriority member_priority);

/**
 * @brief Gets a member ID and frees it. 
 * 
 * @param member_priority - the ID which the user wants to free.
 */
void freeMemberID(PQElementPriority member_priority);

// compares the members' ids, which is their priority
// returns 0 if the members have the same id
// returns 1 if member1.id < member2.id
// return -1 if member1.id > member2.id
/**
 * @brief Compares between two members' IDs according to their priority.
 * 
 * @param member_priority1 - The first ID which the user wants in the comparison. 
 * @param member_priority2 - The second ID which the user wants in the comparison.
 * @return  
 *   0 - If the members have the same id
 *   1 - If member1's ID < member2's ID.
 *   -1 - If member1's ID > member2's ID.
 */
int compareMembersID(PQElementPriority member_priority1, PQElementPriority member_priority2);


/*      priority funcs to compare the order of ints, used in total_member PQ        */
/**
 * @brief Gets a PQElementPriority and copies it into an int variable and returns it.
 * 
 * @param n - The PQElementPriority which the user wants to copy as an Integer. 
 * @return 
 *   NULL - If allocation failed or n is NULL.
 *   An int copy of n.
 */
PQElementPriority copyInt(PQElementPriority n);

/**
 * @brief Frees a PQElementPriority as an int. 
 * 
 * @param n - The PQElemenPriority which the user wants to free. 
 */
void freeInt(PQElementPriority n);

/**
 * @brief Compares between two ints.
 * 
 * @param n1 - The first int which the user wants in the comparison
 * @param n2  -The second int which the user wants in the comparison.
 * @return
 *   The subtraction of the n2 from n1 as an int.
 */
int compareInts(PQElementPriority n1, PQElementPriority n2);


/**
 * @brief Gets a Member and returns it's name.
 * 
 * @param member - The Member which the user wants to get his name.
 * @return 
 *   NULL - If member is NULL.
 *   Returns a string which contains member's name. 
 */
char* getMemberName(Member member);

/**
 * @brief Sets the given member's name to a new name (member_name).
 * 
 * @param member - The member which the user wants to change his name.
 * @param member_name - The new name for the given member.
 */
void setMemberName(Member member, char* member_name);

/**
 * @brief Get the number of events which the given member is linked to.
 * 
 * @param member - The Member which the user wants to get his number of linked events. 
 * @return 
 *   The number of events member is linked to (num_of_events).
 */
int getMemberNumOfEvents(Member member);

/**
 * @brief Gets a pointer to the number of events which the given member is linked to.
 * 
 * @param member - The member which the user wants to get a pointer to his number of linked events  
 * @return 
 *   An int pointer to the number of linked events which member has (num_of_events).
 */
int* getMemberNumOfEventsPointer(Member member);

/**
 * @brief Set the number of events which the given member is linked to, to a new value.
 * 
 * @param member - The member which the user wants to change his number of linked events. 
 * @param new_num_of_events - The new number of events which the user wants to assign to the member.
 */
void setMemberNumOfEvents(Member member, int new_num_of_events);

/**
 * @brief Returns a pointer to the ID of the given member (member_id);
 * 
 * @param member - The member which the user wants to get his ID. 
 * @return
 *   NULL - If member is NULL.
 *   An int pointer to the ID of the given member. 
 */
int* getMemberIdPointer(Member member);

/**
 * @brief (For Testing)
 * 
 * @param member 
 */
void printMember(Member member);

/**
 * @brief Increases the given member's number of linked events (num_of_events) by 1.
 * 
 * @param member - The member which the user wants to increase his linked number of events. 
 */
void tickMemberNumOfEvents(Member member);

/**
 * @brief Decreases the given member's number of linked events (num_of_events) by 1.
 * 
 * @param member - The member which the user wants to decrease his linked number of events. 
 */
void subtractOneFromNumOfEvents(Member member);


#endif /* MEMBER_H_ */



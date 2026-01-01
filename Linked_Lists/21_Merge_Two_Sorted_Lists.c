#include <stdio.h>
#include <stdlib.h>

/*
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/*
 * Helper: Create a new node (just for testing in main)
 */
struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

/*
 * Helper: Print list visually
 */
void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

/*
 * Given the heads of two sorted linked lists, merge them into one sorted list.
 * Returns the head of the merged linked list.
 * Strategy: Using a Stack-based Dummy Node to simplify head handling without malloc.
 */  
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    /*
     * CONCEPT: Entity vs Pointer
     * --------------------------
     * 1. 'struct ListNode dummy' is an ENTITY (a real box). 
     * - It lives on the STACK. 
     * - We use it as a temporary "anchor" so we don't need special "if" checks 
     * for the first node (simplifies logic).
     * - No malloc() needed here (Embedded Friendly: prevents memory leaks/fragmentation).
     * * 2. 'struct ListNode *curr' is a POINTER (a finger/cursor).
     * - It just stores an address. 
     * - We use it to track the "tail" of our building list.
     */
    struct ListNode dummy; 
    
    // Initialize curr to point to our dummy anchor.
    // Since dummy is an entity, we need '&' to get its address.
    struct ListNode *curr = &dummy;

    // While both lists have nodes remaining, compare and attach the smaller one
    while (list1 != NULL && list2 != NULL){
        if (list1->val < list2->val){
            curr->next = list1;   // Attach list1 node to our chain
            list1 = list1->next;  // Advance list1
        } else {
            curr->next = list2;   // Attach list2 node to our chain
            list2 = list2->next;  // Advance list2
        }
        // Move the builder pointer 'curr' forward to the node we just attached
        curr = curr->next;
    }

    /*
     * Handling Leftovers:
     * When one list runs out, the other might still have nodes.
     * Since the input lists are already sorted, we can just attach the 
     * remainder of the non-empty list to the end.
     */  
    if (list1 != NULL){
        curr->next = list1;
    } else {
        curr->next = list2;
    }

    // Return the actual head of the merged list.
    // dummy was just the anchor, the real list starts at dummy.next.
    // Since dummy is a stack variable, it dies here, but dummy.next points to 
    // nodes that exist outside this function (heap or caller scope), so it's safe.
    return dummy.next;
}

int main(){
    /*
     * Test Case: 
     * List 1: 1 -> 2 -> 4
     * List 2: 1 -> 3 -> 4
     * Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> NULL
     */
    struct ListNode* l1 = createNode(1);
    l1->next = createNode(2);
    l1->next->next = createNode(4);

    struct ListNode* l2 = createNode(1);
    l2->next = createNode(3);
    l2->next->next = createNode(4);

    printf("List 1: "); printList(l1);
    printf("List 2: "); printList(l2);

    struct ListNode* mergedHead = mergeTwoLists(l1, l2);

    printf("Merged: "); 
    printList(mergedHead);
    
    // Simple verification for the first few nodes
    printf("Expected first node: 1\n");
    printf("Actual first node:   %d\n", mergedHead->val);

    if (mergedHead->val == 1 && mergedHead->next->val == 1) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    // Cleanup would go here in a full system
    return 0;
}

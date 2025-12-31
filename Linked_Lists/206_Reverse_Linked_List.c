/*
 * File: 206_Reverse_Linked_List.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 206 "Reverse Linked List".
 * Implements an iterative approach using three pointers to reverse the list in-place.
 */

#include <stdio.h>
#include <stdlib.h> // Required for malloc and NULL

/*
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Helper function to create a new node (for testing purposes)
 */
struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!newNode) return NULL;
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

/**
 * Helper function to print the list in a visual format: 1 -> 2 -> 3 -> NULL
 */
void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

/**
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 */
struct ListNode* reverseList(struct ListNode* head) {
    // We need three pointers to track state because singly linked lists are unidirectional.
    // 'prev' will eventually become the new head (pointing to the accumulated reversed list).
    struct ListNode *prev, *curr, *next;
    prev = NULL;
    curr = head;

    // Critical Mindset:
    // We cannot traverse to the end first and then build backwards because we lack back-pointers.
    // We must reverse the links "on the fly" as we traverse forward.
    // We explicitly store 'next' before breaking the link; otherwise, the rest of the list is lost.
    while (curr != NULL) {
        next = curr->next;  // Save the next node so we don't lose the rest of the chain
        curr->next = prev;  // Reverse the link: point current node backwards to 'prev'
        
        // Shift pointers one step forward for the next iteration
        prev = curr;
        curr = next;
    }

    // Termination Logic:
    // The loop condition is "curr != NULL". When the loop finishes, 'curr' has fallen off the end (is NULL).
    // At this point, 'prev' is pointing to the last valid node of the original list.
    // Since all links are reversed, 'prev' is now the HEAD of the new reversed list.
    head = prev;
    return head;
}

int main() {
    // -------------------------------------------------
    // Test Case Setup: Create a list 1 -> 2 -> 3 -> 4 -> 5 -> NULL
    // -------------------------------------------------
    struct ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("--- Test Case 206: Reverse Linked List ---\n");
    printf("Original List: ");
    printList(head);

    // -------------------------------------------------
    // Execution
    // -------------------------------------------------
    struct ListNode* reversedHead = reverseList(head);

    // -------------------------------------------------
    // Verification
    // -------------------------------------------------
    printf("Reversed List: ");
    printList(reversedHead);

    // Simple check logic
    if (reversedHead != NULL && reversedHead->val == 5) {
        printf("\nResult: PASS (New head is 5)\n");
    } else {
        printf("\nResult: FAIL\n");
    }

    // Cleanup (Free memory) - Good habit for Embedded Engineers
    struct ListNode* temp;
    while (reversedHead != NULL) {
        temp = reversedHead;
        reversedHead = reversedHead->next;
        free(temp);
    }

    return 0;
}

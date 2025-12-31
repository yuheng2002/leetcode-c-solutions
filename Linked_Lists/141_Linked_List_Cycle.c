/*
 * File: 141_Linked_List_Cycle.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 141 "Linked List Cycle".
 * Implements Floyd's Tortoise and Hare Algorithm for Cycle Detection.
 * Time Complexity: O(N), Space Complexity: O(1).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Helper function to create a new node
 */
struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!newNode) return NULL;
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

/**
 * Given the head of a linked list, determine if the linked list has a cycle in it. 
 * Strategy: Floyd's Tortoise and Hare Algorithm.
 * - Imagine two runners on a circular track.
 * - If a cycle exists, the fast runner (Hare) will eventually lap/catch the slow runner (Tortoise).
 * - If no cycle exists, the fast runner will simply reach the end (NULL).
 */
bool hasCycle(struct ListNode *head) {
    // Explicitly defining slow and fast pointers for clarity
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    /**
     * CRITICAL SAFETY CHECK (The "Crash" Prevention):
     * We must check the conditions in a specific order:
     * 1. 'fast != NULL': Ensure we are not standing on a cliff (NULL).
     * 2. 'fast->next != NULL': Ensure the NEXT step doesn't fall off a cliff.
     * * Why logic order matters? -> "Short-Circuit Evaluation"
     * In C, if the first condition (fast != NULL) is False, the compiler STOPS checking.
     * If we swapped them to (fast->next && fast), and fast was NULL, 
     * the code would try to access NULL->next, causing a Segmentation Fault (Crash).
     */
    while (fast != NULL && fast->next != NULL) {
        // Move pointers:
        // Slow takes 1 step, Fast takes 2 steps
        slow = slow->next;
        fast = fast->next->next;

        // Collision Check:
        // If they point to the exact same memory address, a cycle is confirmed.
        if (fast == slow) {
            return true;
        }
    }

    // If the loop exits, it means 'fast' reached the end (NULL).
    // Therefore, no cycle exists (Singly Linked List).
    return false;
}

int main() {
    // -------------------------------------------------
    // Test Case: Create a list 3 -> 2 -> 0 -> -4
    //                            ^             |
    //                            |_____________|
    // -------------------------------------------------
    struct ListNode* head = createNode(3);
    struct ListNode* node2 = createNode(2);
    struct ListNode* node0 = createNode(0);
    struct ListNode* node4 = createNode(-4);

    head->next = node2;
    node2->next = node0;
    node0->next = node4;

    // Create the cycle manually: Point the last node back to index 1 (node2)
    node4->next = node2; 

    printf("--- Test Case 141: Linked List Cycle ---\n");
    
    // Execution
    bool has_cycle = hasCycle(head);

    // Verification
    printf("Result: %s\n", has_cycle ? "Cycle Detected (PASS)" : "No Cycle (FAIL)");

    // Cleanup Note: 
    // Freeing a cyclic list is tricky because standard traversal loops forever.
    // We must break the cycle first before freeing.
    if (has_cycle) {
        node4->next = NULL; // Break the cycle manually
    }
    
    // Now safe to free
    free(head);
    free(node2);
    free(node0);
    free(node4);

    return 0;
}

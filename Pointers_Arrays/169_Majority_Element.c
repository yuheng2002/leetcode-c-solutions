#include <stdio.h>

/**
 * Problem: Majority Element (LeetCode 169)
 * Context: Embedded System Constraint - O(N) Time, O(1) Space.
 * * Strategy: Boyer-Moore Voting Algorithm (State Machine Implementation)
 * Instead of using a Hash Map (RAM intensive), we use a "Pairwise Cancellation" strategy.
 * We maintain a 'candidate' register and a 'count' counter.
 * - If the counter is 0: We latch the current number as the new candidate.
 * - If current == candidate: We increment the counter (reinforce signal).
 * - If current != candidate: We decrement (noise cancellation / one-for-one exchange).
 * * Since the majority element > n/2, it will survive the cancellation process.
 */

int majorityElement(int* nums, int numsSize) {
    // Initialize state with the first element
    int candidate = nums[0];
    int count = 1;

    // Optimization: Start from i = 1, since nums[0] is already handled in initialization.
    for (int i = 1; i < numsSize; i++) {
        
        // 1. Comparison & Counter Update
        if (nums[i] == candidate) {
            count++;
        } else {
            count--;
        }

        // 2. State Transition (Reset)
        // If count hits 0, the previous candidate is fully "cancelled" by enemies.
        // The current element (nums[i]) becomes the new candidate for the next round.
        if (count == 0) {
            candidate = nums[i];
            count = 1;
        }
    }

    return candidate;
}

// Helper function to print results
void runTest(int* nums, int size, int expected) {
    int result = majorityElement(nums, size);
    printf("Input Array Size: %d | Result: %d | Expected: %d | Status: %s\n", 
           size, result, expected, (result == expected) ? "PASS" : "FAIL");
}

int main() {
    // Test Case 1: Standard case
    int t1[] = {3, 2, 3};
    runTest(t1, 3, 3);

    // Test Case 2: Complex case with "fighting" between non-majority elements
    // [2, 2, 1, 1, 1, 2, 2] -> Majority is 2
    int t2[] = {2, 2, 1, 1, 1, 2, 2};
    runTest(t2, 7, 2);

    // Test Case 3: Majority appears at the very end
    // [10, 10, 20] -> This case actually violates problem constraint (n/2), 
    // but useful to test logic behavior. 
    // LeetCode guarantees a majority exists > n/2, so let's use [10, 20, 20]
    int t3[] = {10, 20, 20};
    runTest(t3, 3, 20);

    return 0;
}

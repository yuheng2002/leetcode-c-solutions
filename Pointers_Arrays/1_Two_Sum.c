/*
 * Description: 
 * Given an array of integers nums and an integer target, return indices of the two 
 * numbers such that they add up to target.
 *
 * Approach: Brute Force (Iterative)
 * We iterate through each element x and try to find another value that equals to (target - x).
 * Time Complexity: O(N^2) - For each element, 
   we try to find its complement by looping through the rest of the array.
 * Space Complexity: O(1) - The memory required does not depend on the input size (ignoring the returned array).
 * * Why Brute Force in C?
 * Although Hash Map offers O(N), implementing a generic Hash Map in C is complex and requires significant overhead.
 * For typical embedded constraints or small input sizes, this O(N^2) approach avoids dynamic memory complexity 
 * and preserves original indices without needing an auxiliary structure for sorting.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    // Iterate through the array to pick the first number
    for (int i = 0; i < numsSize - 1; i++) {
        // Iterate through the rest of the array to pick the second number
        // Start from i + 1 to avoid using the same element twice
        for (int j = i + 1; j < numsSize; j++) {

            // Check if the sum matches the target
            if (nums[i] + nums[j] == target) {

                // Firmware Optimization: Lazy Allocation
                // We only allocate memory on the Heap once a valid solution is confirmed.
                // This prevents unnecessary malloc/free operations in failure paths.
                int* result = (int*)malloc(2 * sizeof(int));

                // Defensively check if malloc succeeded (optional but good practice)
                if (result == NULL) {
                    *returnSize = 0;
                    return NULL;
                }

                result[0] = i;
                result[1] = j;

                // Set the output parameter size
                *returnSize = 2;

                // Early Exit: Return immediately once found
                return result;
            }
        }
    }

    // Defensive Coding: Default return for invalid input or no solution found.
    // Explicitly set returnSize to 0 to inform the caller the array is empty.
    *returnSize = 0;
    return NULL;
}

// Simple Test Driver
int main() {
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;
    int size = sizeof(nums) / sizeof(nums[0]);

    printf("Input: nums = [");
    for(int i=0; i<size; i++) printf("%d%s", nums[i], (i<size-1)?",":"");
    printf("], target = %d\n", target);

    int* result = twoSum(nums, size, target, &returnSize);

    if (result != NULL) {
        printf("Output: [%d, %d]\n", result[0], result[1]);
        free(result); // Don't forget to free the heap memory!
    } else {
        printf("No solution found.\n");
    }

    return 0;
}



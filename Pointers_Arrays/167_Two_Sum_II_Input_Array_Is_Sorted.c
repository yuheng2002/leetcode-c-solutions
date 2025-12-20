/*
 * LeetCode 167. Two Sum II - Input Array Is Sorted
 * Author: Yuheng Zhang
 * Date: 2025-12-19
 *
 * Description: 
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,
 * find two numbers such that they add up to a specific target number.
 *
 * Approach: Two Pointers
 * Since the array is sorted, we can use two pointers shrinking the search space from both ends.
 * * Complexity Analysis:
 * Time Complexity: O(N) - We touch each element at most once.
 * Space Complexity: O(1) - Only constant extra space is used (ignoring output).
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int left = 0;
    int right = numbersSize - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum < target) {
            left++;
        } else if (sum > target) {
            right--;
        } else {
            // Target found!
            // Optimization: Lazy Allocation
            // Only allocate memory when we are ready to return.
            int* result = (int*)malloc(2 * sizeof(int));

            // Defensive Check: Malloc failure handling
            if (result == NULL) {
                *returnSize = 0;
                return NULL;
            }

            // Requirement: 1-based indices
            result[0] = left + 1;
            result[1] = right + 1;

            *returnSize = 2;
            return result;
        }
    }

    // Default return for no solution / invalid input
    *returnSize = 0;
    return NULL;
}

// Test Driver
int main() {
    int numbers[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Input: numbers = [2, 7, 11, 15], target = 9\n");

    int* result = twoSum(numbers, size, target, &returnSize);

    if (result != NULL) {
        printf("Output: [%d, %d]\n", result[0], result[1]);
        free(result); // Clean up heap memory
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

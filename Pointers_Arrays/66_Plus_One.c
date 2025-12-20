/*
 * LeetCode 66. Plus One
 * Author: Yuheng Zhang
 * Date: 2025-12-19
 *
 * Description: 
 * Given a large integer represented as an integer array digits, 
 * increment the large integer by one and return the resulting array of digits.
 * * Complexity Analysis:
 * Time Complexity: O(N) - Worst case we traverse the whole array (e.g., 999).
 * Space Complexity: O(N) - We need to allocate a new array for the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    
    // Traverse backwards from the Least Significant Bit (LSB)
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] != 9) {
            // Case 1: Simple increment (e.g., 123 -> 124)
            digits[i] += 1;

            // Allocate memory for the result on Heap
            int* result = (int*)malloc(digitsSize * sizeof(int));
            *returnSize = digitsSize;

            // CRITICAL: memcpy requires size in BYTES, not element count!
            // Pitfall: memcpy(dest, src, count) -> Wrong
            // Correct: memcpy(dest, src, count * sizeof(int))
            memcpy(result, digits, digitsSize * sizeof(int));

            return result;
        }
        
        // Case 2: Carry over needed (e.g., ...9 -> ...0)
        digits[i] = 0;
    }

    // Case 3: Overflow (All digits were 9, e.g., 999 -> 1000)
    // We need an array with size + 1.
    int* result = (int*)calloc(digitsSize + 1, sizeof(int));
    *returnSize = digitsSize + 1;

    // Set the Most Significant Bit (MSB) to 1
    result[0] = 1;
    
    // The rest are already 0 thanks to calloc, no loop needed.
    return result;
}

// Simple Test Driver for local debugging
int main() {
    int digits[] = {1, 2, 9};
    int size = sizeof(digits) / sizeof(digits[0]);
    int returnSize;

    printf("Input: ");
    for(int i=0; i<size; i++) printf("%d ", digits[i]);
    printf("\n");

    int* result = plusOne(digits, size, &returnSize);

    printf("Output: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Always free memory allocated in the function
    free(result);

    return 0;
}

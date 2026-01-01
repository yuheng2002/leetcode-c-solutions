/*
 * File: 217_Contains_Duplicate.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 217 "Contains Duplicate".
 * Strategy: Sorting + Linear Scan.
 * * In Embedded/C contexts where Hash Maps (Dictionaries) are not part of the standard library
 * and memory constraints prevent large direct-mapped arrays (LUTs), 
 * the standard solution is to Sort the array first (O(N log N)) and then check adjacent elements.
 */

#include <stdio.h>
#include <stdlib.h> // Required for qsort
#include <stdbool.h>

/**
 * Comparator function required by qsort.
 * --------------------------------------
 * qsort passes generic (void*) pointers to elements, so we must:
 * 1. Cast them back to specific types (int*).
 * 2. Dereference them to get values.
 * 3. Return <0, 0, or >0 based on comparison.
 * * SAFETY NOTE: We use strict comparisons (if/else) instead of subtraction (a - b).
 * Subtraction can cause Integer Overflow if 'a' is large positive and 'b' is large negative.
 */
int compareInts(const void *a, const void *b){
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;

    return 0;
}

/*
 * Given an integer array nums, return true if any value appears at least twice in the array,
 * and return false if every element is distinct. 
 */  
bool containsDuplicate(int* nums, int numsSize){
    // Guard Clause: Defensive programming against invalid/trivial inputs
    if (numsSize <= 1) return false; 
    
    /*
     * Step 1: Sort the array
     * We use the Standard Library's qsort (Quicksort implementation).
     * - Base: Pointer to the start of the array.
     * - Nmemb: Number of elements.
     * - Size: Size of a single element (sizeof(int)) -> needed for pointer arithmetic.
     * - Compar: Function pointer to our comparison logic.
     */  
    qsort(nums, numsSize, sizeof(int), compareInts); 

    /*
     * Step 2: Linear Scan for Adjacent Duplicates
     * Since the array is sorted, any duplicate values must be next to each other.
     * We only need to iterate once (O(N)).
     */
    for (int i = 0; i < numsSize - 1; i++){
        // Check "Current" vs "Next"
        if (nums[i] == nums[i + 1]){
            return true; // Duplicate found
        }
    }

    return false; // No duplicates found after full scan
}

int main(){
    /*
     * Test Case 1: Input contains duplicate
     * Expected: true (1)
     */
    int nums1[] = {1, 2, 3, 1};
    int nums1_size = 4;
    bool result1 = containsDuplicate(nums1, nums1_size);

    printf("nums1 is: [1, 2, 3, 1]\n");
    printf("expected result1 is: 1 (true)\n");
    printf("actual result1 is: %d\n", result1);

    if (result1 == 1){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    printf("\n"); // Just for formatting

    /*
     * Test Case 2: Input contains all distinct elements
     * Expected: false (0)
     */
    int nums2[] = {1, 2, 3, 4, 5};
    int nums2_size = 5;
    bool result2 = containsDuplicate(nums2, nums2_size);

    printf("nums2 is: [1, 2, 3, 4, 5]\n");
    printf("expected result2 is: 0 (false)\n");
    printf("actual result2 is: %d\n", result2);

    if (result2 == 0){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    return 0;
}

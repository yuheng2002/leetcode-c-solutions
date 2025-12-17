#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**
 * Problem: Merge Sorted Array (LeetCode 88)
 * Context: Embedded/Firmware constraints (In-place operation, Memory efficiency).
 * * Strategy: Reverse Two-Pointer Approach
 * We fill the buffer from the back (end of nums1) towards the front.
 * This utilizes the empty "padding" (zeros) at the end of nums1 as a safe write zone,
 * preventing us from overwriting valid data in nums1 before it's read.
 */
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    // Initialize pointers to the end of the valid data
    // read1: points to the last valid element in nums1 (index m-1)
    int read1 =  (nums1Size - nums2Size) - 1;

    // read2: points to the last element in nums2 (index n-1)
    int read2 =  nums2Size - 1; // equivalent to n

    // write: points to the end of the total buffer (index m+n-1)
    // This is where the largest elements will accumulate first.
    int write = nums1Size - 1;

    while (read1 >= 0 && read2 >= 0){
        if (nums1[read1] > nums2[read2]){
            nums1[write] = nums1[read1];
            read1--;
        }
        else if (nums1[read1]< nums2[read2]){
            nums1[write] = nums2[read2];
            read2--;
        }
        // branch for when they are equal
        else{
            // Optimization: "Burst Write" approach.
            // Since we found two identical values, we write both to memory immediately.
            // This effectively unrolls the loop slightly, reducing iteration overhead.
            nums1[write] = nums1[read1];
            nums1[write - 1] = nums2[read2];
            read1--;
            read2--;
            write--; // addtional decrement due to writing two elements instead of one
        }
        write--; // Standard decrement for the current loop iteration
    }

    /* * Post-Loop Cleanup Logic:
     * 1. If read1 >= 0: We do NOTHING.
     * Why? Because nums1 is already sorted. If any elements remain in nums1,
     * they are already in their correct initial positions.
     * * 2. If read2 >= 0: We MUST copy.
     * Why? This implies nums2 has remaining elements that are smaller than
     * everything we've processed so far. We need to move them into the
     * remaining empty slots at the front of nums1.
     */
    while (read2 >= 0){
        nums1[write] = nums2[read2];
        write--;
        read2--;
    }
}

// Helper function to verify the memory state
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    // Test Case 1: Standard Interleaved Merge
    // Simulating a buffer of size 6 with 3 valid elements and 3 padding zeros
    int t1_nums1[6] = {1, 2, 3, 0, 0, 0};
    int t1_m = 3;
    int t1_nums2[3] = {2, 5, 6};
    int t1_n = 3;

    printf("Test Case 1 (Standard):\n");
    printf("Before: "); printArray(t1_nums1, 6);
    merge(t1_nums1, 6, t1_m, t1_nums2, 3, t1_n);
    printf("After : "); printArray(t1_nums1, 6);
    printf("Expect: [1, 2, 2, 3, 5, 6]\n\n");

    // Test Case 2: nums2 is smaller (Cleanup Logic Trigger)
    // Here, nums2 contains [1, 2, 3] which are smaller than [4, 5, 6]
    // This tests if the final while-loop correctly backfills the remaining data.
    int t2_nums1[6] = {4, 5, 6, 0, 0, 0};
    int t2_m = 3;
    int t2_nums2[3] = {1, 2, 3};
    int t2_n = 3;

    printf("Test Case 2 (nums2 smaller):\n");
    printf("Before: "); printArray(t2_nums1, 6);
    merge(t2_nums1, 6, t2_m, t2_nums2, 3, t2_n);
    printf("After : "); printArray(t2_nums1, 6);
    printf("Expect: [1, 2, 3, 4, 5, 6]\n");

    return 0;
}

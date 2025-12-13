#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
 * Core Logic: "Look Back Two" Strategy
 * Since the array is sorted, comparing nums[i] with nums[write - 2] 
 * ensures that no number appears more than twice.
 */
int removeDuplicates(int* nums, int numsSize) {
    // 1. Edge case: Arrays with length <= 2 require no changes.
    if (numsSize <= 2) return numsSize;

    // 2. Initialize write pointer: First two elements (index 0, 1) are always valid.
    int write = 2;

    for (int i = 2; i < numsSize; i++) {
        // 3. Check against the element written 2 positions ago.
        // If they differ, it means we haven't used this value twice yet.
        if (nums[i] != nums[write - 2]) {
            nums[write] = nums[i];
            write++;
        }
    }

    return write;
}

int main(){

    return 0;
}

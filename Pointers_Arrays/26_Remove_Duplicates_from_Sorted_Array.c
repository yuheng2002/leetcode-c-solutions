#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Given an integer array nums sorted in non-decreasing order, 
// remove the duplicates in-place such that each unique element appears only once. 
// The relative order of the elements should be kept the same.

// Consider the number of unique elements in nums to be k. After removing duplicates, 
// return the number of unique elements k.

// The first k elements of nums should contain the unique numbers in sorted order. 
// The remaining elements beyond index k - 1 can be ignored.
int removeDuplicates(int* nums, int numsSize){
    if (numsSize == 0) return 0; // handle edge case: empty input array

    int count = 1; // since the input size is guaranteeded to be at least 1, there is at least one unique element

    int curr_idx = 0; // functions as the slow/write pointer

    for (int i = 0; i < numsSize; i++){
        if (nums[i] != nums[curr_idx]){
            nums[++curr_idx] = nums[i]; // same as nums[curr_index + 1] = nums[i] and curr_index++
            count++;
        }
    }

    return count;
}

int main(){
    return 0;
}

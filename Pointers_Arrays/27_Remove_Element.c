#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 * Core Logic: In-place Remove
 * 1. Move all elements NOT equal to 'val' to the front of the array.
 * 2. The relative order of elements does not matter.
 * 3. Return the new length 'k'. (Values beyond index k are ignored).
 */
int removeElement(int* nums, int numsSize, int val){
    // the key is realizing removing unwanted elements is the same as rewriting the wanted ones
    int write = 0;

    for (int i = 0; i < numsSize; i++){
        if (nums[i] != val){
            nums[write] = nums[i];
            write++;
        }
    }

    return write;
}

int main(){

    return 0;
}

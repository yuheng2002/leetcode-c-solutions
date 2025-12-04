#include <stdio.h>
#include <stdint.h>

// instead of moving all zero to the right, move all the non-zero to the left
void moveZeroes(int* nums, int numsSize){
    int slow = 0; // keeps track of the last index that has been overriden with a non-zero integer

    // First step: moves all non-zero integers to the left, in their original order
    // It is fine to override existing non-zero integers with later non-zero integers,
    // because i will always be bigger than or equal to slow, so we won't miss anything.
    for (int i = 0; i < numsSize; i++){
        if (nums[i] != 0){
            nums[slow] = nums[i];
            slow++;
        }
    }

    // Second step: fill the rest with 0s
    while (slow < numsSize){
        nums[slow] = 0;
        slow++;
    }

}

int main(){
    int test[] = {0, 1, 0, 3, 12};
    int size = 5;

    moveZeroes(test, size);

    printf("Result: ");
    for (int i = 0; i < size; i++){
        printf("%d, ", test[i]);
    }
    printf("\n");

    return 0;
}

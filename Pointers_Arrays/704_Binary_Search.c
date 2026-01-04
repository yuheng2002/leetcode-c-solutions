#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    if (numsSize == 0 || !nums) return -1; // Guard Clause: check for invalid input

    int left = 0;
    int right = numsSize - 1;

    /*
     * Note: "left <= right" is used instead of "left < right".
     * This ensures the algorithm correctly handles arrays with one or two elements
     * by including the case where left == right.
     * At left == right, 'middle' evaluates to the same index, allowing us
     * to check the final remaining element. If no match is found, the loop
     * terminates and returns -1.
     */
    while (left <= right){
        // Use left + (right - left) / 2 instead of (left + right) / 2 to avoid integer overflow
        int middle = left + (right - left) / 2;
        if (target < nums[middle]){
            right = middle - 1;
        }else if (target > nums[middle]){
            left = middle + 1;
        }else{
            return middle;
        }
    }
    
    /* default return statement, if none of the elements searched above is our target, then it does not exist */
    return -1;
}

int main(){
    // Test Case 1: Standard Search
    int nums1[] = {-1, 0, 3, 5, 9, 12};
    int size1 = 6;
    int target1 = 9;
    int result1 = search(nums1, size1, target1);
    printf("--- Test Case 1 ---\n");
    printf("Expected result1 is: 4\n");
    printf("Actual result1 is: %d\n", result1);
    if (result1 == 4){
        printf("PASS\n\n");
    }else{
        printf("FAIL\n\n");
    }
    
    // Test Case 2: Standard Search
    int nums2[] = {5};
    int size2 = 1;
    int target2 = 5;
    int result2 = search(nums2, size2, target2);
    printf("--- Test Case 2 ---\n");
    printf("Expected result2 is: 0\n");
    printf("Actual result2 is: %d\n", result2);
    if (result2 == 0){
        printf("PASS\n\n");
    }else{
        printf("FAIL\n\n");
    }

    // Test Case 3: Target Not Found
    int nums3[] = {-1, 0, 3, 5, 9, 12};
    int size3 = 6;
    int target3 = 2; // 2 is not in nums3
    int result3 = search(nums3, size3, target3);
    printf("--- Test Case 3 (Not Found) ---\n");
    printf("Expected result: -1\n");
    printf("Actual result:   %d\n", result3);
    if (result3 == -1) {
        printf("PASS\n\n");
    } else {
        printf("FAIL\n\n");
    }
    return 0;
}

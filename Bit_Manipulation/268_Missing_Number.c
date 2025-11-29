#include <stdio.h>
#include <stdint.h>

// Approach 1: Mathematical Summation
// Logic: Calculate the sum of 0..n and subtract every element in the array.
// The remaining value is the missing number.
int missingNumberSum(int* nums, int numsSize) {
    int total = 0;       // Initialize accumulator
    int n = numsSize;    // Store original size because numsSize will be decremented

    // Step 1: Add all numbers in the range [1, n] to total
    // Note: We technically need 0..n, but adding 0 doesn't change the sum, so 1..n is fine.
    while (numsSize > 0) {
        total += numsSize;
        numsSize--;
    }

    // Step 2: Subtract all numbers present in the input array
    while (n > 0) {
        // Access array elements from end to start
        total -= nums[n - 1];
        n--;
    }

    // The remaining value in 'total' is the number that was added in Step 1
    // but never subtracted in Step 2.
    return total;
}

// Approach 2: Bit Manipulation (XOR)
// Logic: XOR supports the commutative property (order doesn't matter).
// We XOR all indices [0..n] and all values in the array.
// Duplicate numbers cancel out (A ^ A = 0), leaving only the missing number.
int missingNumberXOR(int* nums, int numsSize) {
    int n = numsSize;    // Store original size
    int total = 0;       // 0 is the identity element for XOR (x ^ 0 = x)

    // Step 1: XOR all numbers in the range [1, n]
    // Again, we omit 0 here because x ^ 0 = x, so it doesn't affect the result.
    while(numsSize > 0){
        total = total ^ numsSize;
        numsSize--;
    }

    // Step 2: XOR with all elements in the input array
    while(n > 0){
        total ^= nums[n - 1];
        n--;
    }

    return total;
}

int main(){
    return 0;
}

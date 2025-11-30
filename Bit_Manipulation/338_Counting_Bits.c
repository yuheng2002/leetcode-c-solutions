#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Approach 1: Brute Force (Naive)
 * Time Complexity: O(n * sizeof(int))
 * Logic: Treat each number independently and count bits from scratch.
 */
int* countBits_naive(int n, int* returnSize){
    *returnSize = n + 1;
    int* result = malloc((*returnSize) * sizeof(int));

    // FIX: Loop condition must be i <= n to cover the full range [0, n]
    for (int i = 0; i <= n; i++){
        // FIX: You want to count bits for 'i', NOT 'n'.
        int cur = i;  
        int count = 0;

        // Standard "Popcount" logic: verify LSB, then shift right
        while (cur > 0){
            if ((cur & 1) == 1){
                count++;
            }
            cur = cur >> 1; // Shift right to process the next bit
        }

        result[i] = count;
    }

    return result;
}

/**
 * Approach 2: Dynamic Programming (O(n))
 * Logic: Reuse the count from a previously calculated smaller number.
 * Relation: bits(i) = bits(i >> 1) + (i & 1)
 * Explain: "i" has the same bits as "i/2", plus the LSB (1 if odd, 0 if even).
 */
int* countBits_dp(int n, int* returnSize){ // Renamed from 'recursion' to 'dp' for accuracy
    *returnSize = n + 1;
    int* result = malloc((*returnSize) * sizeof(int));

    result[0] = 0; // Base case

    for (int i = 1; i <= n; i++){
        int half = i >> 1;    // Looking back at the number "i/2" (already calculated)
        int last_bit = i & 1; // Check if "i" is odd (LSB is 1) or even (LSB is 0)

        // Reuse history: No need to loop, just look up + add 1 bit
        result[i] = result[half] + last_bit;
    }
    
    return result;
}

int main(){
    return 0;
}

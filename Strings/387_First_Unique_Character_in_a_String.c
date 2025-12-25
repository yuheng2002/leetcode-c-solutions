#include <stdio.h>
#include <string.h>

/*
 * File: 387_First_Unique_Character_in_a_String.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 387. Finds the first non-repeating character using a frequency map.
 * Key Concept: "Everything is a Number". We use char offsets as array indices
 * to create a lightweight, high-performance lookup table (O(N) time, O(1) space).
 * 'a' = 97 -> 'z' = 122;
 * 'A' = 65 -> 'Z' = 90
 */
int firstUniqChar(char* s){
    // Guard clause: Handle NULL input.
    // Return -1 because 0 is a valid index (the first character).
    if (!s) return -1;

    // CRITICAL: Must initialize array to {0}.
    // In C, local arrays on the stack contain garbage values by default.
    // Without {0}, frequency counts would start from random numbers, causing bugs.
    int frequency[26] = {0};

    // Pass 1: Build the Frequency Map (Histogram)
    // 'a' (ASCII 97) serves as the base offset.
    for (int i = 0; s[i] != '\0'; i++){
        int curr_char = s[i] - 'a'; 
        frequency[curr_char]++;
    }

    // Pass 2: Find the First Unique Character
    // STRATEGY: Loop over the STRING 's', not the frequency array.
    // Looping over 's' preserves the original order, allowing us to find the "first" occurrence immediately.
    // Looping over 'frequency' would lose the position information and require nested loops.
    for (int j = 0; s[j] != '\0'; j++){
        int curr_char = s[j] - 'a';
        if (frequency[curr_char] == 1){
            return j;
        }
    }

    return -1; // Default return if no unique character exists
    
}
    
int main(){
    char* test1 = "leetcode";
    int result1 = firstUniqChar(test1);
    printf("expected result1 is 0\n");
    printf("actual result1 is: %d, ", result1);
    if (result1 == 0){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    char* test2 = "loveleetcode";
    int result2 = firstUniqChar(test2);
    printf("expected result2 is 2\n");
    printf("actual result2 is: %d, ", result2);
    if (result2 == 2){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    char* test3 = "aabb";
    int result3 = firstUniqChar(test3);
    printf("expected result3 is -1\n");
    printf("actual result3 is: %d, ", result3);
    if (result3 == -1){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    return 0;
}


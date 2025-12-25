/*
 * File: 242_Valid_Anagram.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 242 "Valid Anagram".
 * This file documents the optimization journey from an intuitive "Two-Array" approach 
 * to a memory-efficient "Single-Array Net Zero" approach.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Version 1: Intuitive Approach
 * -----------------------------
 * Uses two separate frequency arrays to count characters for each string independently.
 * Finally, compares the two arrays element-by-element.
 * * Pros: Logic is very straightforward and easy to debug.
 * Cons: Uses double the memory (stack space) and requires two separate passes plus a comparison loop.
 */
bool isAnagram_intuitive(char* s, char* t) {
    if (strlen(s) != strlen(t)) return false; // if they have different lengths -> Fail

    int freq_s[26] = {0};
    int freq_t[26] = {0};
    
    // Pass 1: Build frequency map for s
    for (int i = 0; s[i] != '\0'; i++){
        int curr_char = s[i] - 'a';
        freq_s[curr_char]++;
    }
    
    // Pass 2: Build frequency map for t
    for (int j = 0; t[j] != '\0'; j++){
        int curr_char = t[j] - 'a';
        freq_t[curr_char]++;
    }

    // DEBUG: Print arrays to visualize counts (Uncomment to debug)
    /*
    for (int i = 0; i < 26; i++) printf("%d ", freq_s[i]);
    printf("\n");
    for (int i = 0; i < 26; i++) printf("%d ", freq_t[i]);
    printf("\n");
    */

    // Compare the two int arrays "element by element".
    // CRITICAL NOTE: Simply checking "if (freq_s == freq_t)" would be a logic error.
    // In C, array names decay to pointers, so that would compare memory addresses (which are always different),
    // not the actual content values.
    for (int k = 0; k < 26; k++){
        if (freq_s[k] != freq_t[k]){
            return false;
        }
    }

    return true; // every test has passed, so t is indeed an anagram of s
}

/**
 * Version 2: Optimized Approach (Net Zero Strategy)
 * -------------------------------------------------
 * Uses a SINGLE frequency map to track the "balance" of characters.
 * - Increment (+1) for characters in 's'
 * - Decrement (-1) for characters in 't'
 * * If they are anagrams, the pluses and minuses should perfectly cancel out,
 * leaving the array as all zeros.
 * * Pros: More memory efficient (single array), better cache locality (single loop context).
 */
bool isAnagram_optimized(char* s, char* t){
    if (strlen(s) != strlen(t)) return false; // if lengths differ, they cannot be anagrams.

    // Use a single frequency map to track the "balance" of characters.
    // +1 for characters in 's', -1 for characters in 't'
    // If they are anagrams, the final array must be all zeros.
    int count[26] = {0};

    // Combine the loops: process both strings simultaneously
    // This improves CPU pipeline efficiency compared to separate loops.
    // NOTE: do NOT write i < strlen(s) as the condition in the for loop
    // strlen() takes O(n) runtime, which will make the loop overall runtime O(n^2)
    for (int i = 0; s[i] != '\0' && t[i] != '\0'; i++){
        int curr_s = s[i] - 'a';
        int curr_t = t[i] - 'a';
        
        count[curr_s]++;
        count[curr_t]--;
    }

    // Check if the balance is zero for all letters
    for (int i = 0; i < 26; i++){
        // NOTE: we MUST check element values, not the array pointer itself.
        // Writing "if (count == 0)" would be a logic error comparing memory addresses.
        if (count[i] != 0){
            return false;
        }
    }

    return true;
}

int main(){
    char* s1 = "rat";
    char* t1 = "car";
    char* s2 = "anagram";
    char* t2 = "nagaram";

    // -------------------------------------------------
    // Testing Version 1: Intuitive Approach
    // -------------------------------------------------
    printf("--- Testing Intuitive Approach ---\n");

    bool result1 = isAnagram_intuitive(s1, t1);
    printf("expected result1 is: false\n");
    printf("actual result1 is: %d, ", result1); // a boolean value is just either 1 or 0 in C
    if (result1 == false){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    bool result2 = isAnagram_intuitive(s2, t2);
    printf("expected result2 is: true\n");
    printf("actual result2 is: %d, ", result2); 
    if (result2 == true){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    printf("\n"); // Just for formatting

    // -------------------------------------------------
    // Testing Version 2: Optimized Approach
    // -------------------------------------------------
    printf("--- Testing Optimized Approach ---\n");

    bool result3 = isAnagram_optimized(s1, t1);
    printf("expected result3 is: false\n");
    printf("actual result3 is: %d, ", result3);
    if (result3 == false){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    bool result4 = isAnagram_optimized(s2, t2);
    printf("expected result4 is: true\n");
    printf("actual result4 is: %d, ", result4);
    if (result4 == true){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }

    return 0;
}

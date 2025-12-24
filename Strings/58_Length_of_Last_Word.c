/*
 * File: 58_Length_of_Last_Word.c
 * Author: Yuheng Zhang
 * Description: 
 * Solution for LeetCode 58 "Length of Last Word".
 * Implements a Reverse Scan strategy to efficiently determine the length 
 * of the final word in a string, handling edge cases like trailing spaces.
 * * Includes two variations:
 * 1. Array Indexing (Intuitive Approach)
 * 2. Pointer Arithmetic (Embedded/Low-level optimized Approach)
 */

#include <stdio.h>
#include <string.h>

/**
 * Approach 1: Array Indexing (Intuitive)
 * --------------------------------------
 * Uses standard array indices to scan backwards.
 * Good for readability and general application logic.
 */
int lengthOfLastWord_Intuitive_Approach(char* s) {
    // Guard Clause: Defend against invalid/NULL input
    if (!s) return 0; 

    int len = strlen(s); 
    int i = len - 1; // Start pointing to the last character of the string

    // Step 1: Trim/Skip all trailing spaces
    // We iterate backwards until we find a non-space character or hit the start
    while (i >= 0 && s[i] == ' '){
        i--;
    }

    // Step 2: Scan backwards to find the start of the last word
    // Initialize j to current i, then keep going back until a space is found
    int j = i;
    while (j >= 0 && s[j] != ' '){
        j--;
    }

    // Calculate length using the difference between indices.
    // NOTE: This logic provides "Uniform Handling":
    // It works seamlessly for single-word strings without needing extra branching.
    return i - j;
}

/**
 * Approach 2: Pointer Arithmetic (Embedded Style)
 * -----------------------------------------------
 * Uses direct pointer manipulation instead of array indexing.
 * This is often preferred in firmware/embedded contexts to reduce 
 * the overhead of base+offset calculation in loops.
 */
int lengthOfLastWord_Pointer_Arithmetic(char* s){
    // Guard Clause
    if (!s) return 0;

    // Point 'end' to the very last byte of the string
    char* end = s + strlen(s) - 1;

    // Decrement pointer to skip trailing spaces
    // Ensure pointer address does not go below the base address 's'
    while (end >= s && *end == ' '){
        end--;
    }

    // Use a second pointer 'start' to find the word boundary
    char* start = end;
    while (start >= s && *start != ' '){
        start--;
    }

    // Pointer subtraction yields the distance (length) as a long int, cast to int
    return (int)(end - start);
}

int main(){
    // Test cases can be added here
    return 0;
}

/*
 * File: 151_Reverse_Words_in_a_String.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 151.
 * Implements an In-Place algorithm to reverse words in a string using a "Three-Step Reverse" strategy.
 * This approach is optimized for Embedded Systems: O(1) Space, No Malloc, No Local Buffers.
 */

#include <stdio.h>
#include <string.h>

/**
 * Helper function: Reverse a substring within the range [start, end].
 * Strategy: Two-Pointer Swap.
 * ------------------------------------------------------------------
 * Initial:  [e] u l b [s]   (start=0, end=4) -> swap
 * Step 1:    s [u] l [b] e   (start=1, end=3) -> swap
 * Step 2:    s  b [l] e  e   (start=2, end=2) -> start == end (Stop)
 * ------------------------------------------------------------------
 * Note: Using 'while(start < end)' avoids the complexity of calculating
 * relative offsets (like 'len - i - 1') required in a for-loop.
 */  
void reverse(char *s, int start, int end){
    while (start < end){
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

/**
 * Main Logic: Reverse Words in a String (In-Place)
 * ------------------------------------------------
 * Constraint Analysis (Embedded Perspective):
 * Input length can be up to 10^4. Allocating a local buffer of this size on the Stack
 * risks Stack Overflow. Using 'malloc' (Heap) introduces fragmentation and overhead.
 * Therefore, an In-Place modification is the only robust solution.
 */  
char* reverseWords(char* s){
    // Guard Clause: Check for invalid input
    if (!s) return NULL; 

    int len_s = strlen(s);

    // Step 1: Global Reverse
    // We pass 'len_s - 1' because strlen counts elements excluding the null-terminator.
    // Accessing s[len_s] would be an Out-of-Bounds access (Seg Fault risk).
    reverse(s, 0, len_s - 1);

    int read = 0;
    int write = 0;

    // Step 2: Clean Spaces & Reverse Individual Words
    // We use 'read < len_s' as the boundary check.
    // Why not 's[read] != \0'? 
    // Because in complex string manipulation (especially with trailing spaces), 
    // relying on a specific character is riskier than relying on the fixed length.
    while (read < len_s){
        
        // Skip leading or multiple spaces
        if (s[read] == ' '){
            read++;
            continue;
        }
    
        // Add a space BEFORE the word (if it's not the first word).
        // This avoids the tricky edge case of adding a trailing space after the last word.
        if (write > 0){
            s[write] = ' ';
            write++;
        }

        // Copy the current word to the 'write' position
        int start = write;
        while (read < len_s && s[read] != ' '){
            s[write] = s[read];
            write++;
            read++;
        }

        // Reverse the word we just copied to make it readable again.
        // 'write' currently points to the slot AFTER the last char, so we use 'write - 1'.
        int end = write - 1;
        reverse(s, start, end);
    }

    // Terminate the string at the new length
    s[write] = '\0';

    return s;
}

int main(){
    /*
     * CRITICAL FIX for Local Testing:
     * -------------------------------
     * Wrong: char* test1 = "the sky is blue"; 
     * -> Creates a string literal in Read-Only Memory (.rodata).
     * -> Attempting to modify it causes Segmentation Fault.
     * * Correct: char test1[] = "the sky is blue";
     * -> Creates a mutable copy on the Stack.
     */
    
    char test1[] = "the sky is blue"; // Stack allocation (Mutable)
    printf("Original: '%s'\n", test1);
    char* result1 = reverseWords(test1);
    printf("Expected: 'blue is sky the'\n");
    printf("Actual:   '%s'\n\n", result1);

    char test2[] = "  hello world  "; // Stack allocation (Mutable)
    printf("Original: '%s'\n", test2);
    char* result2 = reverseWords(test2);
    printf("Expected: 'world hello'\n");
    printf("Actual:   '%s'\n", result2);

    return 0;
}

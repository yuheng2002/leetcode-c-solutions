/*
 * File: 125_Valid_Palindrome.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 125 "Valid Palindrome".
 * Implements a "Two-Pointer" strategy with "On-the-fly Skipping".
 * * Key Challenges in C:
 * 1. Memory Safety: Inner loops must rigorously check bounds (front < back) 
 * to prevent Heap Buffer Overflow when skipping consecutive non-alphanumerics.
 * 2. In-Place Processing: We avoid malloc/copying to save memory (O(1) Space),
 * which means we must skip "garbage" characters dynamically during the scan.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>   // Required for isalnum() and tolower()
#include <stdbool.h>

// isalnum() functions the same as the commented code below
// #define IS_ALPHANUM(c) ( ((c) >= '0' && (c) <= '9') || \
                         ((c) >= 'a' && (c) <= 'z') || \
                         ((c) >= 'A' && (c) <= 'Z') )

bool isPalindrome(char* s){
    // Guard Clause: Handle NULL input safely
    if (!s) return false; 

    int front = 0;
    int back = strlen(s) - 1;

    // Macro-Loop: Continues as long as pointers haven't crossed
    while (front < back){
        
        /* * Step 1: Skip invalid characters from the LEFT
         * ---------------------------------------------
         * Library Note: 'isalnum(c)' checks if 'c' is A-Z, a-z, or 0-9.
         * Why use this instead of manual checks like (c >= 'a' && c <= 'z')?
         * 1. Readability: "Is Alphanumeric" is self-explanatory.
         * 2. Portability: Handles different charsets (though rare) better.
         * 3. Robustness: Manual compound IFs (if c>='a' || c>='A' || c>='0'...) are prone to typos.
         * * CRITICAL SAFETY FIX:
         * We MUST check (front < back) inside this loop.
         * Without it, for inputs like ".,", 'front' would increment past 'back',
         * eventually reading out of bounds (Heap Buffer Overflow).
         */
        while (front < back && !isalnum(s[front])){
            front++;
        }
        
        /* * Step 2: Skip invalid characters from the RIGHT
         * ---------------------------------------------
         * Same safety logic applies here. We must stop if we hit 'front'.
         */
        while (front < back && !isalnum(s[back])){
            back--;
        }
        
        /* * Step 3: Compare Valid Characters
         * --------------------------------
         * 'tolower(c)' standardizes the case (A -> a). 
         * It has no effect on digits or symbols, making it safe to use blindly.
         */
        if (tolower(s[front]) != tolower(s[back])){
            return false; // Mismatch found, not a palindrome
        }
        
        // Move pointers inward for the next iteration
        front++;
        back--;
    }
    
    return true; // Pointers met in the middle without issues
}

int main(){
    // Test Case 1: Standard Palindrome with noise
    char* s1 = "A man, a plan, a canal: Panama";
    printf("Test 1 ('%s') -> Expected: 1, Actual: %d\n", s1, isPalindrome(s1));

    // Test Case 2: Not a Palindrome
    char* s2 = "race a car";
    printf("Test 2 ('%s') -> Expected: 0, Actual: %d\n", s2, isPalindrome(s2));

    // Test Case 3: Edge Case - All symbols (Result depends on definition, usually True for empty effective string)
    char* s3 = ".,";
    printf("Test 3 ('%s') -> Expected: 1, Actual: %d\n", s3, isPalindrome(s3));

    return 0;
}

/*
 * File: 205_Isomorphic_Strings.c
 * Author: Yuheng Zhang
 * Description:
 * Solution for LeetCode 205 "Isomorphic Strings".
 * Implements a "Two-Way Mapping" strategy using Look-Up Tables (LUTs) 
 * to verify if a Bijection exists between two strings.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isIsomorphic(char* s, char* t) {
    // Basic Validation: If lengths differ, a one-to-one mapping is impossible.
    if (strlen(s) != strlen(t)) return false; 

    /* Use two arrays as Look-Up Tables (LUTs) to store the mapping.
     * 128 covers standard ASCII. 
     * In Embedded contexts, this is extremely efficient (O(1) access, no hashing overhead).
     * CRITICAL: Must initialize array to {0}.
     * In C, local arrays on the stack contain garbage values by default.
     * Without {0}, frequency counts would start from random numbers, causing bugs.
     */
    char map_s[128] = {0}; 
    char map_t[128] = {0};

    /* * Core Logic: Verify Bijection (Concept from Discrete Math / CSE 21)
     * ------------------------------------------------------------------
     * For strings to be isomorphic, the mapping must be "One-to-One" and "Onto" (Bijection).
     * * Requirement 1 (Source -> Target): 
     * Every character in 's' must map to a UNIQUE character in 't'.
     * Example Conflict: "foo" -> "bar"
     * - 'o' maps to 'a' (first occurrence)
     * - 'o' maps to 'r' (second occurrence) -> CONFLICT! Same input, different output.
     * * Requirement 2 (Target -> Source):
     * No two characters in 's' can map to the SAME character in 't'.
     * Example Conflict: "ab" -> "cc"
     * - 'a' maps to 'c'
     * - 'b' also maps to 'c' -> CONFLICT! Two inputs map to same output (Not one-to-one).
     */
    for (int i = 0; s[i] != '\0' && t[i] != '\0'; i++){
        char s_curr = s[i];
        char t_curr = t[i];
        
        // ---------------------------------------------------------
        // Check Mapping: Source 's' -> Target 't'
        // ---------------------------------------------------------
        // Note: "Everything is a number in C". 
        // We cast char to unsigned char to use it as an array index (Offset).
        if (map_s[(unsigned char)s_curr] == 0){
            // If check fails (== 0), logic implies this char hasn't been mapped yet.
            // Establish the mapping now.
            map_s[(unsigned char)s_curr] = t_curr;
        }
        else{
            // If mapped previously, verify consistency.
            if (map_s[(unsigned char)s_curr] != t_curr){
                return false; // Broken consistency
            }
        }

        // ---------------------------------------------------------
        // Check Mapping: Target 't' -> Source 's'
        // ---------------------------------------------------------
        // This ensures the reverse mapping is also unique (prevents "ab" -> "cc").
        if (map_t[(unsigned char)t_curr] == 0){
            map_t[(unsigned char)t_curr] = s_curr;
        }else{
            if (map_t[(unsigned char)t_curr] != s_curr){
                return false;
            }
        }
    }

    return true; // All checks passed: A valid bijection exists.
}

int main(){
    /*
     * Test Case 1: Standard Isomorphic Case
     */
    char* test1_s = "egg";
    char* test1_t = "add";
    bool result1 = isIsomorphic(test1_s, test1_t);
    
    printf("--- Test Case 1 ---\n");
    // In C, boolean is technically an integer: true -> 1, false -> 0
    printf("Expected result: 1\n"); 
    printf("Actual result:   %d\n", result1);
    
    if (result1 == true){
        printf("Verdict: PASS\n\n");
    }else{
        printf("Verdict: FAIL\n\n");
    }
    
    /*
     * Test Case 2: Violation of One-to-One Mapping
     */
    char* test2_s = "foo";
    char* test2_t = "bar";
    bool result2 = isIsomorphic(test2_s, test2_t);

    printf("--- Test Case 2 ---\n");
    printf("Expected result: 0\n");
    printf("Actual result:   %d\n", result2);
    
    if (result2 == false){
        printf("Verdict: PASS\n");
    }else{
        printf("Verdict: FAIL\n");
    }

    return 0;
}

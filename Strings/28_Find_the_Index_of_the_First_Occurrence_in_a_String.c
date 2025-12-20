/*
 * LeetCode 28. Find the Index of the First Occurrence in a String
 * Author: Yuheng Zhang
 * Date: 2025-12-19
 *
 * Description: 
 * Given two strings needle and haystack, return the index of the first occurrence 
 * of needle in haystack, or -1 if needle is not part of haystack.
 *
 * Approach: Brute Force (Sliding Window)
 * We treat the 'needle' as a window and slide it across the 'haystack'.
 * * Complexity Analysis:
 * Time Complexity: O(N * M) - In the worst case (e.g., "AAAAAB" vs "AAB"), we compare nearly every character.
 * Space Complexity: O(1) - No extra space allocated.
 */

#include <stdio.h>
#include <string.h>

int strStr(char* haystack, char* needle) {
    int h = strlen(haystack);
    int n = strlen(needle);

    // Edge Case: If needle is empty, by definition index 0 is correct (or debatable, but usually 0)
    if (n == 0) return 0;

    // Optimization: Loop only goes up to h - n.
    // If haystack has 5 chars and needle has 3, we only need to check indices 0, 1, 2.
    for (int i = 0; i <= h - n; i++) {
        
        // number of chars that match so far
        // will reset for each i
        int count = 0; 

        for (int j = 0; j < n; j++) {
            // Compare character by character
            // 'i' is the base offset, 'j' is the window offset
            if (haystack[i + j] != needle[j]) {
                break; // Mismatch found, stop checking this window
            } else {
                count++;
            }
        }

        // If we found 'n' matches, it means the whole needle matches
        if (count == n) {
            return i;
        }
    }

    return -1;
}

int main(){

    return 0;
}

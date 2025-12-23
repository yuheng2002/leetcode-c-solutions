#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Function: longestCommonPrefix
 * -----------------------------
 * Finds the longest common prefix string amongst an array of strings.
 * * Strategy: Vertical Scanning
 * We iterate through the characters of the first string (column by column).
 * For each character, we compare it with the corresponding character in
 * all other strings (rows). If a mismatch is found, we stop and return
 * the prefix found so far.
 * * Edge Cases Handled:
 * - Empty input array
 * - Single string array
 * - No common prefix
 * - All strings are identical
 */
char* longestCommonPrefix(char** strs, int strsSize) {
    // Guard clause: Defend against invalid/empty input
    if (strsSize == 0) return "";

    // Trivial case: If only one string exists, it is the prefix of itself
    if (strsSize == 1) return strs[0];

    // Declare 'col' outside the loop scope so it persists after the loop ends.
    // We will need this value later to handle the "all strings are identical" edge case.
    int col = 0;

    for (; strs[0][col] != '\0'; col++){

        char curr = strs[0][col]; // The "reference" char we are comparing against

        for (int row = 1; row < strsSize; row++){

            // If mismatch found, or if the current row's string is shorter than col
            if (strs[row][col] != curr){
                // Allocate memory for the result.
                // Explicitly using 'sizeof(char)' for clarity, and '+ 1' is CRITICAL for the null-terminator.
                char* result = (char*)malloc((col + 1) * sizeof(char));

                // Use strncpy to copy exactly 'col' characters.
                // PITFALL: strncpy does NOT automatically add the Null-terminator when length limit is reached.
                strncpy(result, strs[0], col);

                result[col] = '\0'; // Manually null-terminate the string

                return result;
            }
        }
    }

    // If the code reaches here, the nested loop finished without returning.
    // This means 'col' incremented for every character without finding a mismatch.
    //
    // Logic check:
    // 1. 'col' now reflects the total number of matching characters (the full length).
    // 2. 'strlen' counts elements excluding the null-terminator.
    // 3. Edge Case: If all strings are identical, 'col' will equal the length of strs[0].
    //
    // In this case, simply return the first string as the answer.
    if (col == strlen(strs[0])){
        return strs[0];
    }

    return ""; // Default return as a fallback safety net
}

int main(){

    return 0;
}

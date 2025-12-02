#include <stdio.h>
#include <string.h>

// Write a function that reverses a string. The input string is given as an array of characters s.
// You must do this by modifying the input array in-place with O(1) extra memory.

// Example 1:
// Input: s = ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]

// Example 2:
// Input: s = ["H","a","n","n","a","h"]
// Output: ["h","a","n","n","a","H"]

void reverseString(char* s, int sSize){
    // sSize represents the return value of strlen(s)
    // which counts the number of elements in string s without the null-terminator
    // do NOT need to decrement sSize
    // only the purpose is to visit the last element in the array
    // for example, if a string is ['h','e','l','l','o','\0']
    // strlen returns 5
    // to access the last element 'o', which is at index 4, we need to decrement len
    // but for the purpose of this problem,
    // decrementing sSize could cause the mid point to shift to the left by 1
    // leading to incorrect result after swapping elements.
    for (int i = 0; i < (sSize / 2); i++){
        char temp = s[i];
        s[i] = s[sSize - 1 - i];
        s[sSize - 1 - i] = temp;
    }
}

int main(){

    return 0;
}

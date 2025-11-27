#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// an integer is a power of two when its binary representation has exactly 1 set bit in it
// A set bit refers to a bit in the binary representation of a number that has a value of 1
bool isPowerOfTwo(int n){
    size_t count = 0;

    while (n > 0){
	if ((n & 1) == 1){
	    count++;
	}

	n = n >> 1;
    }
    return count == 1;
}

// testing
int main(){
    int test_val1 = 0;
    int test_val2 = 16;

    int result1 = isPowerOfTwo(test_val1);
    int result2 = isPowerOfTwo(test_val2);

    if (!result1){
	printf("result1 is: %d, PASS\n", result1);
    }else{
	printf("FAIL\n");
    }

    if (result2){
	printf("result2 is: %d, PASS\n", result2);
    }else{
	printf("FAIL\n");
    }
}

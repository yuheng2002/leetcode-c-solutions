#include <stdio.h>
#include <stdint.h>

// Every number appears twice except for one.
// XOR has two key properties:
//   1) x ^ x = 0        (pairs cancel out)
//   2) x ^ 0 = x        (0 does not change the value)
// It also has commutative and associative laws,
// so the order of XOR operations does not matter.
//
// Therefore, XOR all elements in the array:
// all paired numbers become 0, and only the single
// unique number remains.
//
// Time: O(n), Space: O(1)
int singleNumber(int* nums, int numsSize) {
    int res = *nums;
    for (int i = 0; i < numsSize - 1; i++){
        res = res ^ *(nums + 1);
        nums++;
    }
    return res;
}

int main(){
    int test[] = {4, 1, 2, 1, 2};

    int result = singleNumber(test, 5);
    // 0100 ^ 0001 = 0101
    // 0101 ^ 0010 = 0111
    // 0111 ^ 0001 = 0110
    // 0110 ^ 0010 = 0100

    printf("result is: %d\n", result);

    if (result == 4){
        printf("PASS\n");
    }else{
        printf("FAIL\n");
    }
    return 0;
}

#include <stdio.h>
#include <stdint.h>

int reverseBits (int n){
    // convert to unsigned integer first, otherwise if n is negative
    // when shitfting to the right, it will have padding ones on the left
    // which will lead to incorrect result
    uint32_t un = (uint32_t) n;
    uint32_t result = 0; // bit shifting is safely done with unsigned integers

    for (int i = 0; i < 32; i++){
        if ((un & 1) == 1){
            result = (result << 1) + 1;
        }else{
            result = result << 1;
        }
        un = un >> 1; // do NOT forget to shift un to the right
    }
    return (int)result;
}

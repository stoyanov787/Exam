#include <stdio.h>
#include <stdint.h>
#include "functions.h"

int main(void){
    // Test Ones count
    printf("Ones count: %u\n", onesCount(0, 0, 1, 3));

    // Test flip odd bits
    uint64_t mask = 0ULL;
    flipOddBits(&mask);
    printf("0b");
    for(int i = 63; i >= 0; i--){
        printf("%d", check_bit(mask, i));
    }
    printf("\n");

    // Test mirror bits
    uint16_t mask_mirror = 0b1111111100000000;
    mirrorBits(&mask_mirror);
    printf("0b");
    for(int i = 15; i >= 0; i--){
        printf("%d", check_bit(mask_mirror, i));
    }
    printf("\n");

    return 0;
}
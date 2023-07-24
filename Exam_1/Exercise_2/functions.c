#include <stdint.h>

// Function to check bit
int check_bit(uint64_t mask, int position){
    return (mask & (1ULL << position)) ? 1 : 0;
}

// Function to set bit
void set_bit(uint64_t *mask, int position){
    (*mask) = (*mask) | (1ULL << position);
}

// Function to clear bit
void clear_bit(uint64_t *mask, int position){
    (*mask) = (*mask) & (~(1ULL << position));
}

// Function to check bit in 16-bit int
int check_bit_16(uint16_t mask, int position){
    return (mask & (1ULL << position)) ? 1 : 0;
}

// Function to set bit in 16-bit int
void set_bit_16(uint16_t *mask, int position){
    (*mask) = (*mask) | (1ULL << position);
}

// Function to clear bit in 16-bit int
void clear_bit_16(uint16_t *mask, int position){
    (*mask) = (*mask) & (~(1ULL << position));
}

// Function to count ones
unsigned onesCount(uint64_t mask1, uint32_t mask2, uint16_t mask3, uint8_t mask4){
    unsigned count = 0;
    for(int i = 0; i < 64; i++){
        count += check_bit(mask1, i);
        if(i < 32) count += check_bit(mask2, i);
        if(i < 16) count += check_bit(mask3, i);
        if(i < 8) count += check_bit(mask4, i);
    }
    return count;
}

// Function to flip odd bits
void flipOddBits(uint64_t* mask){
    for(int i = 0; i < 64; i++){
        // Check if position is odd
        if(i % 2 == 1){
            if(check_bit(*mask, i)) clear_bit(mask, i);
            else set_bit(mask, i);
        } 
    }
}

// Function to mirror bits
void mirrorBits(uint16_t* mask){
    for(int right = 0, left = 15; right < 8 && left >= 8; right++, left--){
        // Find right and left bits
        int right_bit = check_bit_16(*mask, right);
        int left_bit = check_bit_16(*mask, left);

        // Mirror right bit to left bit
        if(right_bit) set_bit_16(mask, left);
        else clear_bit_16(mask, left);

        // Mirror left bit to right bit
        if(left_bit) set_bit_16(mask, right);
        else clear_bit_16(mask, right);
    }
}
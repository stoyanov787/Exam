int check_bit(uint64_t mask, int position);
void set_bit(uint64_t *mask, int position);
void clear_bit(uint64_t *mask, int position);
void set_bit_16(uint16_t *mask, int position);
void clear_bit_16(uint16_t *mask, int position);
unsigned onesCount(uint64_t mask1, uint32_t mask2, uint16_t mask3, uint8_t mask4);
void flipOddBits(uint64_t* mask);
void mirrorBits(uint16_t* mask);
#include "sprite.h"

/* ---=== Intermediate Data Structure : ===--- */
typedef struct RadixItem {
  Sprite*   data;
  uint8_t   digits[16];
} RadixItem;





/* ---=== Function Prototypes : ===--- */
uint8_t     hex_digit(uint16_t n, uint16_t digit);
RadixItem** format_input_data(size_t input_length,Sprite** input);
void        count_sort_by_hex_digit(size_t input_length,RadixItem** input,uint16_t digit);
//Sprite**    radix_sort(size_t input_length,Sprite **input);
void        radix_sort(size_t input_length,Sprite** input,Sprite** output);

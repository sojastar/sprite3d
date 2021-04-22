#include <stdlib.h>
#include <stdio.h>
#include "radix_sort.h"





/* ---=== Function Declarations : ===--- */
uint8_t hex_digit(uint16_t n, uint16_t digit) {
  uint16_t p = digit << 2;
  return (n >> p) % 16;
}

void count_sort_by_hex_digit(size_t input_length,Sprite** input,Sprite** output,uint16_t digit) {
  // 1. Counting input keys :
  /* We are sorting hex digits on a uint16_t key, so the input_count count ...
   * ... array has to be of length 16. */
  uint16_t input_count[16] = { 0 };
  for (size_t i = 0; i < input_length; ++i)
    //input_count[input[i].digits[digit]] += 1;
    //input_count[hex_digit(input[i]->vertex->view[2],digit)] += 1;
    input_count[hex_digit(input[i]->vertex->int_view_z, digit)] += 1;

  // 2. Stacking counts :
  for (size_t i = 1; i < 16; ++i)
    input_count[i] += input_count[i-1];

  // 3. Actually sorting :
  //RadixItem** output = (RadixItem**)calloc(input_length, sizeof(RadixItem*));
  for (ssize_t i = input_length - 1; i >= 0; i -= 1) {
    //uint16_t key = input[i].digits[digit];
    //uint16_t key = hex_digit(input[i]->vertex->view[2],digit);
    uint16_t key = hex_digit(input[i]->vertex->int_view_z, digit);
    input_count[key] -= 1;
    output[input_count[key]] = input[i];
  }

  //for (size_t i = 0; i < input_length; ++i)
  //  input[i] = output[i];

  //free(output);
}

void radix_sort(size_t input_length,Sprite **input,Sprite** output) {
  //RadixItem** formated_input = format_input_data(input_length, input);
  //Sprite** buffer = (Sprite**)calloc(input_length, sizeof(Sprite*));
  //Sprite** buffers[]  = { buffer, ouptut }

  //for (size_t i = 0; i < 3; ++i)
  //  count_sort_by_hex_digit(input_length, formated_input, i);
  count_sort_by_hex_digit(input_length, input,  output, 0);
  count_sort_by_hex_digit(input_length, output, input, 1);
  count_sort_by_hex_digit(input_length, input,  output, 2);
  //count_sort_by_hex_digit(input_length, output, input, 0);
  //count_sort_by_hex_digit(input_length, input,  output, 0);

  //for (size_t i = 0; i < input_length; ++i)
  //  output[i] = formated_input[i]->data;
}

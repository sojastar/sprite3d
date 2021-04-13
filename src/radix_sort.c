#include <stdlib.h>
#include <stdio.h>
#include "radix_sort.h"





/* ---=== Function Declarations : ===--- */
uint8_t hex_digit(uint16_t n, uint16_t digit) {
  uint16_t p = 4 * digit;
  return (n >> p) % 16;
}

RadixItem** format_input_data(size_t input_length,Sprite** input) {
  RadixItem** formated_input_data = (RadixItem**)calloc(input_length, sizeof(RadixItem*));

  for (size_t i = 0; i < input_length; i++) {
    RadixItem*  formated_entry  = (RadixItem*)malloc(sizeof(RadixItem));
    formated_entry->data        = input[i];
    formated_entry->digits[0]   = hex_digit(input[i]->vertex->view[2],  0);
    formated_entry->digits[1]   = hex_digit(input[i]->vertex->view[2],  1);
    formated_entry->digits[2]   = hex_digit(input[i]->vertex->view[2],  2);
    formated_entry->digits[3]   = hex_digit(input[i]->vertex->view[2],  3);
    formated_entry->digits[4]   = hex_digit(input[i]->vertex->view[2],  4);
    formated_entry->digits[5]   = hex_digit(input[i]->vertex->view[2],  5);
    formated_entry->digits[6]   = hex_digit(input[i]->vertex->view[2],  6);
    formated_entry->digits[7]   = hex_digit(input[i]->vertex->view[2],  7);
    formated_entry->digits[8]   = hex_digit(input[i]->vertex->view[2],  8);
    formated_entry->digits[9]   = hex_digit(input[i]->vertex->view[2],  9);
    formated_entry->digits[10]  = hex_digit(input[i]->vertex->view[2], 10);
    formated_entry->digits[11]  = hex_digit(input[i]->vertex->view[2], 11);
    formated_entry->digits[12]  = hex_digit(input[i]->vertex->view[2], 12);
    formated_entry->digits[13]  = hex_digit(input[i]->vertex->view[2], 13);
    formated_entry->digits[14]  = hex_digit(input[i]->vertex->view[2], 14);
    formated_entry->digits[15]  = hex_digit(input[i]->vertex->view[2], 15);
    

    formated_input_data[i]  = formated_entry;
  }

  return formated_input_data;
}

void count_sort_by_hex_digit(size_t input_length,RadixItem** input,uint16_t digit) {
  // 1. Counting input keys :
  /* We are sorting hex digits on a uint16_t key, so the input_count count ...
   * ... array has to be of length 16. */
  uint16_t input_count[16] = { 0 };
  for (size_t i = 0; i < input_length; ++i)
    input_count[input[i]->digits[digit]] += 1;

  // 2. Stacking counts :
  for (size_t i = 1; i < 16; ++i)
    input_count[i] += input_count[i-1];

  // 3. Actually sorting :
  RadixItem** output = (RadixItem**)calloc(input_length, sizeof(RadixItem*));
  for (ssize_t i = input_length - 1; i >= 0; i -= 1) {
    uint16_t key = input[i]->digits[digit];
    input_count[key] -= 1;
    output[input_count[key]] = input[i];
  }

  for (size_t i = 0; i < input_length; ++i)
    input[i] = output[i];

  free(output);
}

void radix_sort(size_t input_length,Sprite **input,Sprite** output) {
  RadixItem** formated_input = format_input_data(input_length, input);

  for (size_t i = 0; i < 16; ++i)
    count_sort_by_hex_digit(input_length, formated_input, i);

  for (size_t i = 0; i < input_length; ++i)
    output[i] = formated_input[i]->data;
}

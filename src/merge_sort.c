#include <stdlib.h>
#include <stdio.h>
#include "merge_sort.h"

/* ---=== Function Declarations : ===--- */
void merge_sort(size_t left, size_t right,Sprite** input,Sprite** buffer) {
  if (right - left > 0) {
    size_t middle = left + ( right - left ) / 2;
    merge_sort(left, middle, input, buffer);
    merge_sort(      middle + 1, right, input, buffer);

    merge(left, middle, right, input, buffer);
  }
}

void merge(size_t left,size_t middle,size_t right,Sprite** input,Sprite** buffer) {
  size_t left_index   = left;
  size_t right_index  = middle + 1;
  size_t buffer_index = 0;

  //Sprite** buffer = (Sprite**)malloc((right - left + 1) * sizeof(Sprite*));

  while ((left_index <= middle) && (right_index <= right)) {
    if (input[left_index]->vertex->int_view_z <= input[right_index]->vertex->int_view_z) {
      buffer[buffer_index] = input[left_index];
      left_index   += 1;
    }
    else {
      buffer[buffer_index] = input[right_index];
      right_index  += 1;
    }
    buffer_index += 1;
  }

  if (left_index > middle) {
    for (size_t i = right_index; i <= right; i++)
      buffer[i - right_index + buffer_index] = input[i]; 
  }
  else {
    for (size_t i = left_index; i <= middle; i++)
      buffer[i - left_index + buffer_index] = input[i]; 
  }

  for (size_t i = 0; i < right - left + 1; i++)
    input[i + left] = buffer[i];
 
  //free(buffer);
}

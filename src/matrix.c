#include <stdlib.h>
#include <stdio.h>

void matrix_print(float m[static 4][4]) {
  printf("[ [%f, %f, %f, %f],\n",  m[0][0], m[0][1], m[0][2], m[0][3]);
  printf("  [%f, %f, %f, %f],\n",  m[1][0], m[1][1], m[1][2], m[1][3]);
  printf("  [%f, %f, %f, %f],\n",  m[2][0], m[2][1], m[2][2], m[2][3]);
  printf("  [%f, %f, %f, %f] ]\n", m[3][0], m[3][1], m[3][2], m[3][3]);
}

void matrix_copy(float s[static 4][4],float d[static 4][4]) {
  for(size_t i = 0; i < 16; i += 1)
    *((float *)d + i) = *((float *)s + i);
}

void matrix_negate(float m[static 4][4]) {
  for(size_t i = 0; i < 4; ++i)
    for(size_t j = 0; j < 4; ++j)
      m[i][j] = -m[i][j];
}

void matrix_matrix_add(float m1[static 4][4], float m2[static 4][4],float r[static 4][4]) {
  for(size_t i = 0; i < 4; ++i)
    for(size_t j = 0; j < 4; ++j)
      r[i][j] = m1[i][j] + m2[i][j];
}

void matrix_matrix_mul(float m1[static 4][4], float m2[static 4][4],float r[static 4][4]) {
  for(size_t i = 0; i < 4; ++i) {
    for(size_t j = 0; j < 4; ++j) {
      r[i][j] = 0.0;
      for(size_t k = 0; k < 4; ++k)
        r[i][j] += m1[i][k] * m2[k][j];
    }
  }
}

void d_matrix_matrix_mul(float m1[static 4][4], float m2[static 4][4],float r[static 4][4]) {
  float buffer[4][4];

  for(size_t i = 0; i < 4; ++i) {
    for(size_t j = 0; j < 4; ++j) {
      buffer[i][j] = 0.0;
      for(size_t k = 0; k < 4; ++k)
        buffer[i][j] += m1[i][k] * m2[k][j];
    }
  }

  for(size_t i = 0; i < 16; i += 1)
    *((float *)r + i) = *((float *)buffer + i);
}

void matrix_vector_mul(float m[static 4][4],float v[static 4],float r[static 4]) {
  for(size_t i = 0; i < 4; ++i) {
    r[i] = 0.0;
    for(size_t j = 0; j < 4; ++j)
      r[i] += m[i][j] * v[j];
  }
}

void d_matrix_vector_mul(float m[static 4][4],float v[static 4]) {
  float buffer[4];

  for(size_t i = 0; i < 4; ++i) {
    buffer[i] = 0.0;
    for(size_t j = 0; j < 4; ++j)
      buffer[i] += m[i][j] * v[j];
  }

  for(size_t i = 0; i < 4; i += 1)
    *((float *)v + i) = *((float *)buffer + i);
}

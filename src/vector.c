#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "vector.h"


float* vector_copy(float v[static 4]) {
  float* new_v  = (float *)calloc(4, sizeof(float));

  new_v[0]  = v[0];
  new_v[1]  = v[1];
  new_v[2]  = v[2];
  new_v[3]  = v[3];

  return new_v;
}

void vector_set(float v[static 4],float x,float y,float z,float w) {
  v[0] = x; 
  v[1] = y; 
  v[2] = z; 
  v[3] = w; 
}

void vector_translate(float v[static 4],float dx,float dy,float dz) {
  v[0] += dx;
  v[1] += dy;
  v[2] += dz;
}

bool vector_equality(float v1[static 4],float v2[static 4]) {
  return  ( fabs(v1[0] - v2[0]) < EPSILON ) &&
          ( fabs(v1[1] - v2[1]) < EPSILON ) &&
          ( fabs(v1[2] - v2[2]) < EPSILON );
}

void vector_reverse(float v[static 4]) {
  v[0] = -v[0];
  v[1] = -v[1];
  v[2] = -v[2];
}

void vector_scalar_mul(float v[static 4],float s) {
  v[0] *= s; 
  v[1] *= s; 
  v[2] *= s; 
}

float vector_squared_magnitude(float v[static 4]) {
  return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

float vector_magnitude(float v[static 4]) {
  return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vector_normalize(float v[static 4]) {
  float norm = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

  v[0] /= norm;
  v[1] /= norm;
  v[2] /= norm;
}

void vector_rotate_x(float v[static 4],float angle) {
  float s = sinf(angle);
  float c = cosf(angle);
  
  float buffer[4];

  buffer[0] = v[0];
  buffer[1] = v[1] * c - v[2] * s;
  buffer[2] = v[1] * s + v[2] * c;
  buffer[3] = v[3];

  v[0]  = buffer[0];
  v[1]  = buffer[1];
  v[2]  = buffer[2];
  v[3]  = buffer[3];
}

void vector_rotate_y(float v[static 4],float angle) {
  float s = sinf(angle);
  float c = cosf(angle);
  
  float buffer[4];

  buffer[0] =  v[0] * c + v[2] * s;
  buffer[1] =  v[1];
  buffer[2] = -v[0] * s + v[2] * c;
  buffer[3] =  v[3];

  v[0]  = buffer[0];
  v[1]  = buffer[1];
  v[2]  = buffer[2];
  v[3]  = buffer[3];
}

void vector_rotate_z(float v[static 4],float angle) {
  float s = sinf(angle);
  float c = cosf(angle);
  
  float buffer[4];

  buffer[0] = v[0] * c - v[1] * s;
  buffer[1] = v[0] * s - v[1] * c;
  buffer[2] = v[2];
  buffer[3] = v[3];

  v[0]  = buffer[0];
  v[1]  = buffer[1];
  v[2]  = buffer[2];
  v[3]  = buffer[3];
}

void vector_cross_product(float v1[static 4],float v2[static 4],float cp[static 4]) {
  float cx = v1[1] * v2[2] - v1[2] * v2[1];
  float cy = v1[2] * v2[0] - v1[0] * v2[2];
  float cz = v1[0] * v2[1] - v1[1] * v2[0];

  cp[0] = cx;
  cp[1] = cy;
  cp[2] = cz;
  cp[3] = 1.0;
}

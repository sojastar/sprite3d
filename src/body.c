#include <stdlib.h>
#include <math.h>
#include "vertex.h"
#include "matrix.h"
#include "body.h"

Body* new_body(size_t sprite_count,Sprite** sprites) {
  Body* b = (Body *)malloc(sizeof(Body));

  b->world[0][0] = 1.0; b->world[0][1] = 0.0; b->world[0][2] = 0.0; b->world[0][3] = 0.0;
  b->world[1][0] = 0.0; b->world[1][1] = 1.0; b->world[1][2] = 0.0; b->world[1][3] = 0.0;
  b->world[2][0] = 0.0; b->world[2][1] = 0.0; b->world[2][2] = 1.0; b->world[2][3] = 0.0;
  b->world[3][0] = 0.0; b->world[3][1] = 0.0; b->world[3][2] = 0.0; b->world[3][3] = 1.0;

  b->sprite_count  = sprite_count;
  b->sprites       = sprites;

  return b;
}

void free_body(Body *b) {
  for(size_t i = 0; i < b->sprite_count; ++i)
    free(b->sprites[i]);
  free(b);
}

void body_move_to(Body* b,float x,float y,float z) {
  b->world[0][3] = x;
  b->world[1][3] = y;
  b->world[2][3] = z;
}

void body_translate(Body* b,float x,float y,float z) {
  b->world[0][3] += x;
  b->world[1][3] += y;
  b->world[2][3] += z;
}

void body_rotate_x(Body *b,float a) {
  float rot_matrix[4][4]  = { { 1.0,      0.0,      0.0, 0.0 },
                              { 0.0,  cosf(a), -sinf(a), 0.0 },
                              { 0.0,  sinf(a),  cosf(a), 0.0 },
                              { 0.0,      0.0,      0.0, 1.0 } };
  d_matrix_matrix_mul(b->world, rot_matrix, b->world);
}

void body_rotate_y(Body *b,float a) {
  float rot_matrix[4][4]  = { { cosf(a), 0.0, sinf(a), 0.0 },
                              {     0.0, 1.0,     0.0, 0.0 },
                              {-sinf(a), 0.0, cosf(a), 0.0 },
                              {     0.0, 0.0,     0.0, 1.0 } };
  d_matrix_matrix_mul(b->world, rot_matrix, b->world);
}

void body_rotate_z(Body *b,float a) {
  float rot_matrix[4][4]  = { { cosf(a),-sinf(a), 0.0, 0.0 },
                              { sinf(a), cosf(a), 0.0, 0.0 },
                              {     0.0,     0.0, 1.0, 0.0 },
                              {     0.0,     0.0, 0.0, 1.0 } };
  d_matrix_matrix_mul(b->world, rot_matrix, b->world);
}

void body_reset_rotation(Body* b) {
  b->world[0][0]  = 1.0;
  b->world[0][1]  = 0.0;
  b->world[0][2]  = 0.0;
  b->world[1][0]  = 0.0;
  b->world[1][1]  = 1.0;
  b->world[1][2]  = 0.0;
  b->world[2][0]  = 0.0;
  b->world[2][1]  = 0.0;
  b->world[2][2]  = 1.0;
  b->world[3][3]  = 1.0;
}

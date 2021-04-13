#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "camera.h"

SCamera* new_camera(float p[static 4],float d[static 4]) {
  SCamera* camera  = (SCamera *)malloc(sizeof(SCamera));

  camera->position[0]   = p[0];
  camera->position[1]   = p[1];
  camera->position[2]   = p[2];
  camera->position[3]   = p[3];

  camera->direction[0]  = d[0];
  camera->direction[1]  = d[1];
  camera->direction[2]  = d[2];
  camera->direction[3]  = d[3];

  /*camera->view_matrix   = { { 1.0, 0.0, 0.0, 0.0 },
                            { 0.0, 1.0, 0.0, 0.0 },
                            { 0.0, 0.0, 1.0, 0.0 },
                            { 0.0, 0.0, 0.0, 1.0 } };*/
  camera->view_matrix[0][0] = 1.0;
  camera->view_matrix[0][1] = 0.0;
  camera->view_matrix[0][2] = 0.0;
  camera->view_matrix[0][3] = 0.0;
  camera->view_matrix[1][0] = 0.0;
  camera->view_matrix[1][1] = 1.0;
  camera->view_matrix[1][2] = 0.0;
  camera->view_matrix[1][3] = 0.0;
  camera->view_matrix[2][0] = 0.0;
  camera->view_matrix[2][1] = 0.0;
  camera->view_matrix[2][2] = 1.0;
  camera->view_matrix[2][3] = 0.0;
  camera->view_matrix[3][0] = 0.0;
  camera->view_matrix[3][1] = 0.0;
  camera->view_matrix[3][2] = 0.0;
  camera->view_matrix[3][3] = 1.0;

  camera->view_matrix_status = CAMERA_VIEW_MATRIX_NOT_COMPUTED;

  return camera;
}

void free_camera(SCamera* camera) {
  free(camera);
}

void print_camera(SCamera* camera) {
}

void camera_move_to(SCamera* c,float offset[4]) {
  c->position[0]  = offset[0];
  c->position[1]  = offset[1];
  c->position[2]  = offset[2];
}

void camera_translate(SCamera* c,float offset[4]) {
  c->position[0]  += offset[0];
  c->position[1]  += offset[1];
  c->position[2]  += offset[2];
}

void camera_look_at(SCamera* c,float offset[4]) {
  c->direction[0]  = offset[0];
  c->direction[1]  = offset[1];
  c->direction[2]  = offset[2];
}

void camera_rotate_x(SCamera* c,float a) {
  vector_rotate_x(c->direction, a);
}

void camera_rotate_y(SCamera* c,float a) {
  vector_rotate_y(c->direction, a);
}

void camera_rotate_z(SCamera* c,float a) {
  vector_rotate_z(c->direction, a);
}

void camera_reset_view_matrix(SCamera* c) {
  c->view_matrix_status = CAMERA_VIEW_MATRIX_NOT_COMPUTED;
}

void camera_compute_view_matrix(SCamera* c) {
  //printf("hereeeeeeeeee\n");
  if (c->view_matrix_status == CAMERA_VIEW_MATRIX_NOT_COMPUTED) {
    float v[4]  = { 0.0, 1.0, 0.0, 1.0 };
    float right_axis[4], up_axis[4];

    vector_cross_product(v, c->direction, right_axis);
    vector_normalize(right_axis);

    vector_cross_product(c->direction, right_axis, up_axis);
    vector_normalize(up_axis);

    float rotation_matrix[4][4] = { {   right_axis[0],   right_axis[1],   right_axis[2], 0.0 },
                                    {      up_axis[0],      up_axis[1],      up_axis[2], 0.0 },
                                    { c->direction[0], c->direction[1], c->direction[2], 0.0 },
                                    {             0.0,             0.0,             0.0, 1.0 } };
    float translation_matrix[4][4]  = { { 1.0, 0.0, 0.0, -c->position[0] },
                                        { 0.0, 1.0, 0.0, -c->position[1] },
                                        { 0.0, 0.0, 1.0, -c->position[2] },
                                        { 0.0, 0.0, 0.0,             1.0 } };

    matrix_matrix_mul(rotation_matrix, translation_matrix, c->view_matrix);
    c->view_matrix_status = CAMERA_VIEW_MATRIX_COMPUTED;
  }
}

#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "camera.h"
//#include "raylib.h"

void compute_right_up_axis(SCamera* c) {
}

SCamera* new_camera(float p[static 4],float f[static 4]) {
  SCamera* camera  = (SCamera *)malloc(sizeof(SCamera));

  camera->position[0]   = p[0];
  camera->position[1]   = p[1];
  camera->position[2]   = p[2];
  camera->position[3]   = p[3];

  camera->front[0]  = f[0];
  camera->front[1]  = f[1];
  camera->front[2]  = f[2];
  camera->front[3]  = f[3];
  vector_normalize(camera->front);

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

void camera_move_to(SCamera* c,float position[4]) {
  c->position[0]  = position[0];
  c->position[1]  = position[1];
  c->position[2]  = position[2];
}

void camera_translate(SCamera* c,float offset[4]) {
  c->position[0]  += offset[0];
  c->position[1]  += offset[1];
  c->position[2]  += offset[2];
}

void camera_look_at(SCamera* c,float offset[4]) {
  c->front[0] = offset[0];
  c->front[1] = offset[1];
  c->front[2] = offset[2];

  vector_normalize(c->front);
}

void camera_rotate_x(SCamera* camera,float angle) {
  vector_rotate_x(camera->front, angle);
  // there shouldn't be any need for noramlization ...
  // ... but I leave this here as a reminder.
}

void camera_rotate_y(SCamera* camera,float angle) {
  vector_rotate_y(camera->front, angle);
  // there shouldn't be any need for noramlization ...
  // ... but I leave this here as a reminder.
}

void camera_rotate_z(SCamera* camera,float angle) {
  vector_rotate_z(camera->front, angle);
  // there shouldn't be any need for noramlization ...
  // ... but I leave this here as a reminder.
}

void camera_move_forward(SCamera* camera, float speed) {
  float offset[4];
 
  vector_copy_over(camera->front, offset);
  //vector_scalar_mul(offset, speed * GetFrameTime());
  vector_scalar_mul(offset, speed);

  camera_translate(camera, offset);
}

void camera_move_right(SCamera* camera, float speed) {
}

void camera_move_up(SCamera* camera, float speed) {
}

void camera_pitch(SCamera* camera, float angle) {
}

void camera_yaw(SCamera* camera, float angle) {
}

void camera_roll(SCamera* camera, float angle) {
}

void camera_reset_view_matrix(SCamera* camera) {
  camera->view_matrix_status = CAMERA_VIEW_MATRIX_NOT_COMPUTED;
}

void camera_compute_view_matrix(SCamera* camera) {
  if (camera->view_matrix_status == CAMERA_VIEW_MATRIX_NOT_COMPUTED) {
    float v[4]  = { 0.0, 1.0, 0.0, 1.0 };
    float right_axis[4], up_axis[4];

    vector_cross_product(v, camera->front, right_axis);
    vector_normalize(right_axis);

    vector_cross_product(camera->front, right_axis, up_axis);
    vector_normalize(up_axis);

    float rotation_matrix[4][4] = { {    right_axis[0],    right_axis[1],    right_axis[2], 0.0 },
                                    {       up_axis[0],       up_axis[1],       up_axis[2], 0.0 },
                                    { camera->front[0], camera->front[1], camera->front[2], 0.0 },
                                    {              0.0,              0.0,              0.0, 1.0 } };
    float translation_matrix[4][4]  = { { 1.0, 0.0, 0.0, -camera->position[0] },
                                        { 0.0, 1.0, 0.0, -camera->position[1] },
                                        { 0.0, 0.0, 1.0, -camera->position[2] },
                                        { 0.0, 0.0, 0.0,                  1.0 } };

    matrix_matrix_mul(rotation_matrix, translation_matrix, camera->view_matrix);
    camera->view_matrix_status = CAMERA_VIEW_MATRIX_COMPUTED;
  }
}

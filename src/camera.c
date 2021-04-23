#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "camera.h"

SCamera* new_camera(float p[static 4],float f[static 4],float u[static 4]) {
  SCamera* camera  = (SCamera *)malloc(sizeof(SCamera));

  camera->position[0]   = p[0];
  camera->position[1]   = p[1];
  camera->position[2]   = p[2];
  camera->position[3]   = p[3];

  camera->forward[0]  = f[0];
  camera->forward[1]  = f[1];
  camera->forward[2]  = f[2];
  camera->forward[3]  = f[3];
  vector_normalize(camera->forward);

  camera->up[0] = u[0];
  camera->up[1] = u[1];
  camera->up[2] = u[2];
  camera->up[3] = u[3];
  vector_normalize(camera->up);

  vector_cross_product(camera->forward, camera->up, camera->right);

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

void camera_look_at(SCamera* c,float object[4]) {
  /*c->front[0] = offset[0];
  c->front[1] = offset[1];
  c->front[2] = offset[2];

  vector_normalize(c->front);*/
}

void camera_rotate_x(SCamera* camera,float angle) {
  vector_rotate_x(camera->forward, angle);
  vector_rotate_x(camera->up, angle);
  vector_cross_product(camera->forward, camera->up, camera->right);
  // there shouldn't be any need for normalization ...
  // ... but I leave this here as a reminder.
}

void camera_rotate_y(SCamera* camera,float angle) {
  vector_rotate_y(camera->forward, angle);
  vector_rotate_y(camera->up, angle);
  vector_cross_product(camera->forward, camera->up, camera->right);
  // there shouldn't be any need for normalization ...
  // ... but I leave this here as a reminder.
}

void camera_rotate_z(SCamera* camera,float angle) {
  vector_rotate_z(camera->forward, angle);
  vector_rotate_z(camera->up, angle);
  vector_cross_product(camera->forward, camera->up, camera->right);
  // there shouldn't be any need for normalization ...
  // ... but I leave this here as a reminder.
}

void camera_move_forward(SCamera* camera, float speed) {
  float offset[4];
 
  vector_copy_over(camera->forward, offset);
  vector_scalar_mul(offset, speed);

  camera_translate(camera, offset);
}

void camera_move_right(SCamera* camera, float speed) {
  float offset[4];
 
  vector_copy_over(camera->right, offset);
  vector_scalar_mul(offset, speed);

  camera_translate(camera, offset);
}

void camera_move_up(SCamera* camera, float speed) {
  float offset[4];
 
  vector_copy_over(camera->up, offset);
  vector_scalar_mul(offset, speed);

  camera_translate(camera, offset);
}

/*void camera_pitch(SCamera* camera, float angle) {
}

void camera_yaw(SCamera* camera, float angle) {
}

void camera_roll(SCamera* camera, float angle) {
}*/

void camera_reset_view_matrix(SCamera* camera) {
  camera->view_matrix_status = CAMERA_VIEW_MATRIX_NOT_COMPUTED;
}

void camera_compute_view_matrix(SCamera* camera) {
  if (camera->view_matrix_status == CAMERA_VIEW_MATRIX_NOT_COMPUTED) {
    vector_normalize(camera->forward);
    vector_normalize(camera->up);
    vector_normalize(camera->right);

    camera->view_matrix[0][0] = camera->right[0];
    camera->view_matrix[1][0] = camera->right[1];
    camera->view_matrix[2][0] = camera->right[2];
    camera->view_matrix[3][0] = 0.0;
    camera->view_matrix[0][1] = camera->up[0];
    camera->view_matrix[1][1] = camera->up[1];
    camera->view_matrix[2][1] = camera->up[2];
    camera->view_matrix[3][1] = 0.0;
    camera->view_matrix[0][2] = camera->forward[0];
    camera->view_matrix[1][2] = camera->forward[1];
    camera->view_matrix[2][2] = camera->forward[2];
    camera->view_matrix[3][2] = 0.0;
    camera->view_matrix[0][3] = -camera->position[0];
    camera->view_matrix[1][3] = -camera->position[1];
    camera->view_matrix[2][3] = -camera->position[2];
    camera->view_matrix[3][3] = 1.0;

    camera->view_matrix_status = CAMERA_VIEW_MATRIX_COMPUTED;
  }
}

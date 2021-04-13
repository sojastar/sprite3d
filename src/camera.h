#include <stdlib.h>

#define CAMERA_VIEW_MATRIX_NOT_COMPUTED 0
#define CAMERA_VIEW_MATRIX_COMPUTED     1

#ifndef _CAMERA_DEFINED
#define _CAMERA_DEFINED
typedef struct SCamera {
  float   position[4];
  float   direction[4];
  float   view_matrix[4][4];
  uint8_t view_matrix_status;
} SCamera;
#endif

SCamera*  new_camera(float position[static 4],float direction[static 4]);
void      free_camera(SCamera* camera);
void      print_camera(SCamera *camera);
void      camera_move_to(SCamera* camera,float offset[4]);
void      camera_translate(SCamera* camera,float offset[4]);
void      camera_look_at(SCamera* camera,float offset[4]);
void      camera_rotate_x(SCamera* camera,float a);
void      camera_rotate_y(SCamera* camera,float a);
void      camera_rotate_z(SCamera* camera,float a);
void      camera_reset_view_matrix(SCamera* camera);
void      camera_compute_view_matrix(SCamera* camera);

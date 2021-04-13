#include "sprite.h"

#ifndef _BODY_DEFINED
#define _BODY_DEFINED
typedef struct Body {
  float   world[4][4];
  Sprite  **sprites;
  size_t  sprite_count;
} Body;
#endif

Body* new_body(size_t sprite_count,Sprite** sprites);
void  free_body(Body *b);
void  body_move_to(Body* b,float x,float y,float z);
void  body_translate(Body* b,float x,float y,float z);
void  body_rotate_x(Body *b,float a);
void  body_rotate_y(Body *b,float a);
void  body_rotate_z(Body *b,float a);
void  body_reset_rotation(Body* b);

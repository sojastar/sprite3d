#include <stddef.h>
#include "vertex.h"

#ifndef _SPRITE_DEFINED
#define _SPRITE_DEFINED
typedef struct Sprite {
  Vertex      *vertex;
  uint16_t    width;
  uint16_t    height;
  uint16_t    scale;
  uint16_t    draw_x;
  uint16_t    draw_y;
  float       draw_scale;
  uint16_t    draw_width;
  uint16_t    draw_height;
  float       angle;
  const char* atlas_file;
  uint16_t    atlas_x;
  uint16_t    atlas_y;
  uint16_t    atlas_w;
  uint16_t    atlas_h;
} Sprite;
#endif

Sprite* new_sprite(Vertex* v,uint16_t width,uint16_t height,uint16_t scale,const char* file,uint16_t atlas_x,uint16_t atlas_y,uint16_t atlas_w,uint16_t atlas_h);
void    free_sprite(Sprite* s);
void    sprite_compute_draw_size(Sprite* s);
void    sprite_rotate(Sprite* s,float da);
void    sprite_rotate_absolute(Sprite* s,float a);

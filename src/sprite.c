#include <stdlib.h>
#include <math.h>
#include "sprite.h"

Sprite* new_sprite(Vertex* vertex,uint16_t width,uint16_t height,uint16_t scale,const char* file,uint16_t atlas_x,uint16_t atlas_y,uint16_t atlas_w,uint16_t atlas_h) {
  Sprite *s = (Sprite *)malloc(sizeof(Sprite));

  s->vertex       = vertex;
  s->width        = scale * width;
  s->height       = scale * height;
  s->draw_x       = -1280;
  s->draw_y       = -720;
  s->draw_scale   = scale;
  s->draw_width   = scale * width;
  s->draw_height  = scale * height;
  s->angle        = 0.0;
  s->atlas_file   = file;
  s->atlas_x      = atlas_x;
  s->atlas_y      = atlas_y;
  s->atlas_w      = atlas_w;
  s->atlas_h      = atlas_h;
  s->scale        = scale;

  return s;
}

void free_sprite(Sprite* s) {
  free(s->vertex);
  free(s);
}

void sprite_compute_draw_size(Sprite* s) {
  s->draw_scale   = (float)s->scale / s->vertex->view[2];
  s->draw_width   = (uint16_t)( s->width / s->vertex->view[2]);
  s->draw_height  = (uint16_t)(s->height / s->vertex->view[2]);
  s->draw_x       = s->vertex->screen_x - (s->draw_width  >> 1);
  s->draw_y       = s->vertex->screen_y - (s->draw_height >> 1);
}

void sprite_rotate(Sprite* s,float da) {
  s->angle = fmod(s->angle + da, 360.0);
}

void sprite_rotate_absolute(Sprite* s,float a) {
  s->angle = fmod(a, 360.0);
}

#include <stdio.h>
#include <math.h>
#include "renderer.h"
#include "radix_sort.h"

Renderer* new_renderer(uint16_t width,uint16_t height,float near, float far) {
  Renderer* renderer = (Renderer *)malloc(sizeof(Renderer));

  renderer->width           = width;
  renderer->height          = height;
  renderer->half_width      = width >> 1;
  renderer->half_height     = height >> 1;
  renderer->ratio           = (float)width / height;
  renderer->near            = near;
  renderer->far             = far;
  renderer->sorted_sprites  = (void*)0;

  return renderer;
}

void free_renderer(Renderer *renderer) {
  free(renderer->in_frustum_sprites);
  free(renderer->sorted_sprites);
  free(renderer);
}

bool vertex_in_frustum(Renderer* renderer,Vertex* vertex) {
  float x = vertex->view[0];
  float y = vertex->view[1];
  float z = vertex->view[2];
      
  return  (       z > renderer->near            ) &&
          (       z < renderer->far             ) &&
          ( fabs(z) > fabs(x)                   ) &&
          ( fabs(z) > renderer->ratio * fabs(y) );
}

void project_vertex(Renderer* renderer,SCamera* camera,Vertex* vertex) {
  compute_view_coordinates(vertex, camera->view_matrix);

  if (vertex_in_frustum(renderer, vertex)) {
    vertex->screen_x   = renderer->half_width  + (int)(                  renderer->half_width * vertex->view[0] / vertex->view[2]);
    //vertex->screen_y   = renderer->half_height + (int)(renderer->ratio * renderer->half_width * vertex->view[1] / vertex->view[2]);
    vertex->screen_y   = renderer->half_height + (int)( renderer->half_width * vertex->view[1] / vertex->view[2]);
    vertex->in_frustum = true;
  }
  else {
    vertex->in_frustum = false;
  }
}

void render_scene(Renderer* renderer,SCamera* camera,Scene* scene) {
  Element *current = scene->first;

  if(renderer->in_frustum_sprites == (void*)0) {
    size_t in_frustum_sprites_count  = 0;
    while(current != (void*)0) {
      in_frustum_sprites_count += current->body->sprite_count;
      current = current->next;
    }

    renderer->in_frustum_sprites  = (Sprite**)malloc(in_frustum_sprites_count * sizeof(Sprite*));
    renderer->sorted_sprites      = (Sprite**)malloc(in_frustum_sprites_count * sizeof(Sprite*));
  }

  //camera_reset_view_matrix(camera);
  camera_compute_view_matrix(camera);

  renderer->in_frustum_sprites_count  = 0;
  while(current != (void*)0) {
    Body* body  = current->body;
    for(size_t i = 0; i < body->sprite_count; ++i) {
      Vertex *vertex  = body->sprites[i]->vertex;
      compute_world_coordinates(vertex, body->world);
      project_vertex(renderer, camera, vertex);

      if (vertex->in_frustum) {
        renderer->in_frustum_sprites[renderer->in_frustum_sprites_count] = body->sprites[i];
        renderer->in_frustum_sprites_count += 1;
      }

      radix_sort(renderer->in_frustum_sprites_count, renderer->in_frustum_sprites, renderer->sorted_sprites);
    }

    current     = current->next; 
  }

  
}

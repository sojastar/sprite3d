#include <stdio.h>
#include "raylib.h"
#include "sprite3d.h"

int main(void) {

  // Window Initialization :
  const int window_width  = 1280;
  const int window_height = 720;

  InitWindow(window_width, window_height, "Sprite3D");


  // Textures Initialization :
  // NOTE: Textures MUST be loaded after Window initialization.
  // because an OpenGL context is required.
  Texture2D spheres       = LoadTexture("./game_src/sprites/spheres_all.png");


  // Engine Initialization :
  Vertex* v1              = new_vertex(-1.0,-1.0,-1.0);
  Vertex* v2              = new_vertex( 1.0,-1.0,-1.0);
  Vertex* v3              = new_vertex( 1.0, 1.0,-1.0);
  Vertex* v4              = new_vertex(-1.0, 1.0,-1.0);
  Vertex* v5              = new_vertex(-1.0,-1.0, 1.0);
  Vertex* v6              = new_vertex( 1.0,-1.0, 1.0);
  Vertex* v7              = new_vertex( 1.0, 1.0, 1.0);
  Vertex* v8              = new_vertex(-1.0, 1.0, 1.0);
  Sprite* s1              = new_sprite(v1, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s2              = new_sprite(v2, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s3              = new_sprite(v3, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s4              = new_sprite(v4, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s5              = new_sprite(v5, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s6              = new_sprite(v6, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s7              = new_sprite(v7, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
  Sprite* s8              = new_sprite(v8, 16, 16, 80, "sprites/spheres_all.png", 16, 0, 16, 16);
  Sprite* cube_sprites[8] = { s1, s2, s3, s4, s5, s6, s7, s8 };
  Body*   cube            = new_body(8, cube_sprites);
  Scene*  scene           = new_scene();

  scene_push_element(scene, cube);
  body_move_to(cube, 0.0, 0.0, -35.0);

  float     position[4]   = { 0.0, 0.0, 0.0, 1.0 };
  float     direction[4]  = { 0.0, 0.0,-1.0, 1.0 };
  SCamera*  camera        = new_camera(position, direction);

  Renderer* renderer  = new_renderer(1280, 720, 1.0, 300.0);
  //Renderer* renderer  = new_renderer(640, 360, 1.0, 300.0);

  float angle = 0.01f;

  // Miscellaneous :
  SetTargetFPS(60);


  // Main Loop :
  while (!WindowShouldClose()) {

    body_rotate_x(scene->first->body, angle);
    body_rotate_z(scene->first->body, 2*angle);
    //angle += 0.005f;

    BeginDrawing();
      ClearBackground(RAYWHITE);

      render_scene(renderer, camera, scene);
      
      for (ssize_t i = renderer->in_frustum_sprites_count -1; i >= 0; --i) {
        Sprite* sprite  = renderer->sorted_sprites[i];
        Vertex* vertex  = sprite->vertex;
        uint16_t  screen_width  = (int)(sprite->width / vertex->view[2]);
        uint16_t  screen_height = (int)(sprite->height / vertex->view[2]);
        uint16_t  screen_x  = vertex->screen_x - (screen_width >> 1);
        uint16_t  screen_y  = vertex->screen_y - (screen_height >> 1);
        /*printf( "v%zu: x=%hu y=%hu ss=%hu sx=%hu sy=%hu sw=%hu sh=%hu ax=%hu ay=%hu aw=%hu ah=%hu\n",
                i,
                sprite->vertex->screen_x,
                sprite->vertex->screen_y,
                sprite->scale,
                screen_x,
                screen_y,
                screen_width,
                screen_height,
                sprite->atlas_x,
                sprite->atlas_y,
                sprite->atlas_w,
                sprite->atlas_h );*/
        DrawTextureTiled( spheres,
                          (Rectangle){ sprite->atlas_x, sprite->atlas_y, sprite->atlas_w, sprite->atlas_h},
                          (Rectangle){ screen_x, screen_y, screen_width, screen_height },
                          (Vector2){ 0.0f, 0.0f },
                          0.0f,
                          sprite->scale / vertex->view[2],
                          GetColor(0xFFFFFFFF) );
      }
    EndDrawing();
  }

  free_scene(scene);
  free_camera(camera);
  free_renderer(renderer);

  UnloadTexture(spheres);

  CloseWindow();
  
  return 0;
}

#include <stdio.h>
#include "raylib.h"
#include "sprite3d.h"

Body* generate_cube(size_t size);

int main(void) {

  // Window Initialization :
  const int window_width  = 1280;
  const int window_height = 720;

  InitWindow(window_width, window_height, "Sprite3D");


  // Textures Initialization :
  // NOTE: Textures MUST be loaded after Window initialization.
  // because an OpenGL context is required.
  Texture2D spheres       = LoadTexture("./example/sprites/spheres_all.png");


  // Engine Initialization :
  Body* cube              = generate_cube(16);
  Scene*  scene           = new_scene();

  scene_push_element(scene, cube);
  body_move_to(cube, 0.0, 0.0, -50.0);

  float     position[4]   = { 0.0, 0.0, 0.0, 1.0 };
  float     direction[4]  = { 0.0, 0.0,-1.0, 1.0 };
  SCamera*  camera        = new_camera(position, direction);

  Renderer* renderer  = new_renderer(1280, 720, 1.0, 300.0);

  float angle = 0.5f;

  // Miscellaneous :
  SetTargetFPS(60);


  // Main Loop :
  while (!WindowShouldClose()) {

    // Game Logic :
    
    // Rotate the cube :
    body_rotate_z(scene->first->body,  1.5 * angle * GetFrameTime());
    body_rotate_y(scene->first->body, -2.0 * angle * GetFrameTime());
    body_rotate_x(scene->first->body,        angle * GetFrameTime());

    // Move the camera :
    float o[4]  = {0.0, 0.0, 1.0, 0.0};
    if (IsKeyDown(KEY_DOWN)) camera_translate(camera, o);

    // Game Render :
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
        DrawTextureTiled( spheres,
                          (Rectangle){ sprite->atlas_x, sprite->atlas_y, sprite->atlas_w, sprite->atlas_h},
                          (Rectangle){ screen_x, screen_y, screen_width, screen_height },
                          (Vector2){ 0.0f, 0.0f },
                          0.0f,
                          sprite->scale / vertex->view[2],
                          GetColor(0xFFFFFFFF) );
      }
    EndDrawing();

    //printf("%d\n", GetFPS());
  }

  free_scene(scene);
  free_camera(camera);
  free_renderer(renderer);

  UnloadTexture(spheres);

  CloseWindow();
  
  return 0;
}

Body* generate_cube(size_t size) {
  Sprite** spheres  = (Sprite**)calloc(6 * size * size, sizeof(Sprite*));

  // Blue sphere :
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      Vertex* front_vertex  = new_vertex( 2.0 * i - size + 1.0,
                                          2.0 * j - size + 1.0,
                                         -1.0 - size);
      Sprite* front_sprite  = new_sprite( front_vertex, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
      spheres[2*(i*size + j)] = front_sprite;
      Vertex* back_vertex   = new_vertex( 2.0 * i - size + 1.0,
                                          2.0 * j - size + 1.0,
                                          1.0 + size);
      Sprite* back_sprite   = new_sprite(  back_vertex, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
      spheres[2*(i*size + j) + 1] = back_sprite;
    }
  }

  // Green sphere :
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      Vertex* front_vertex  = new_vertex( 2.0 * i - size + 1.0,
                                         -1.0 - size,
                                          2.0 * j - size + 1.0 );
      Sprite* front_sprite  = new_sprite( front_vertex, 16, 16, 80, "sprites/spheres_all.png",  16, 0, 16, 16);
      spheres[4*size*size + 2*(i*size + j)] = front_sprite;
      Vertex* back_vertex   = new_vertex( 2.0 * i - size + 1.0,
                                          1.0 + size,
                                          2.0 * j - size + 1.0 );
      Sprite* back_sprite   = new_sprite(  back_vertex, 16, 16, 80, "sprites/spheres_all.png",  16, 0, 16, 16);
      spheres[4*size*size + 2*(i*size + j) + 1] = back_sprite;
    }
  }

  // Red sphere :
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      Vertex* front_vertex  = new_vertex( -1.0 - size,
                                           2.0 * i - size + 1.0,
                                          2.0 * j - size + 1.0 );
      Sprite* front_sprite  = new_sprite( front_vertex, 16, 16, 80, "sprites/spheres_all.png",  32, 0, 16, 16);
      spheres[2*size*size + 2*(i*size + j)] = front_sprite;
      Vertex* back_vertex  = new_vertex( 1.0 + size,
                                           2.0 * i - size + 1.0,
                                          2.0 * j - size + 1.0 );
      Sprite* back_sprite   = new_sprite(  back_vertex, 16, 16, 80, "sprites/spheres_all.png",  32, 0, 16, 16);
      spheres[2*size*size + 2*(i*size + j) + 1] = back_sprite;
    }
  }

  Body* cube = new_body(6*size*size, spheres); 

  return cube;
}

#include <stdio.h>
#include "raylib.h"
#include "sprite3d.h"





/******************************************************************************
 * ---=== FUNCTION PROTOTYPES : ===---                                        *
 ******************************************************************************/
Body* generate_cube(size_t size);





/******************************************************************************
 * ---=== MAIN : ===---                                                       *
 ******************************************************************************/
int main(void) {

  /* ---=== 1. Initialization : ===--- */

  // --- 1.1 RayLib Initialization :
  const int window_width  = 1280;
  const int window_height = 720;

  InitWindow(window_width, window_height, "Sprite3D");

  SetTargetFPS(60);

  // --- 1.2 Textures Initialization :
  Texture2D spheres       = LoadTexture("./example/sprites/spheres_all.png");

  // --- 1.3 ENGINE INITIALIZATION :
  Scene*  scene           = new_scene();

  Body* cube              = generate_cube(20);
  scene_push_element(scene, cube);
  body_move_to(cube, 0.0, 0.0, -100.0);

  float     position[4]   = { 0.0, 0.0, 0.0, 1.0 };
  float     forward[4]    = { 0.0, 0.0,-1.0, 1.0 };
  float     up[4]         = { 0.0, 1.0, 0.0, 1.0 };
  SCamera*  camera        = new_camera(position, forward, up);

  Renderer* renderer  = new_renderer(1280, 720, 1.0, 300.0);

  // --- 1.4 Miscellaneous :
  float cube_rotation_speed       = 0.5f;
  float camera_rotation_speed     = 0.4f;
  float camera_translation_speed  = 20.0;


  /* ---=== 2. Main Loop : ===--- */
  while (!WindowShouldClose()) {

    // --- 2.1 Game Logic :
    
    // 2.1.1 Rotate the cube :
    body_rotate_x(scene->first->body,        cube_rotation_speed * GetFrameTime());
    body_rotate_z(scene->first->body,  1.5 * cube_rotation_speed * GetFrameTime());
    body_rotate_y(scene->first->body, -2.0 * cube_rotation_speed * GetFrameTime());

    // 2.1.2 Player Input :
    if (IsKeyDown(KEY_Q)) camera_rotate_z(camera,  camera_rotation_speed * GetFrameTime());
    if (IsKeyDown(KEY_E)) camera_rotate_z(camera, -camera_rotation_speed * GetFrameTime());
    if (IsKeyDown(KEY_W)) camera_rotate_x(camera, -camera_rotation_speed * GetFrameTime());
    if (IsKeyDown(KEY_S)) camera_rotate_x(camera,  camera_rotation_speed * GetFrameTime());
    if (IsKeyDown(KEY_A)) camera_rotate_y(camera,  camera_rotation_speed * GetFrameTime());
    if (IsKeyDown(KEY_D)) camera_rotate_y(camera, -camera_rotation_speed * GetFrameTime());

    if (IsKeyDown(KEY_UP))    camera_move_forward(camera, -camera_translation_speed * GetFrameTime());
    if (IsKeyDown(KEY_DOWN))  camera_move_forward(camera,  camera_translation_speed * GetFrameTime());
    if (IsKeyDown(KEY_LEFT))  camera_move_right(camera,   -camera_translation_speed * GetFrameTime());
    if (IsKeyDown(KEY_RIGHT)) camera_move_right(camera,    camera_translation_speed * GetFrameTime());

    // --- 2.2 Game Render :
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

  /* ---=== 3. Cleanup : ===--- */

  // --- 3.1 Engine cleanup :
  free_scene(scene);
  free_camera(camera);
  free_renderer(renderer);

  // --- 3.2 RayLib cleanup :
  UnloadTexture(spheres);

  CloseWindow();
  

  return 0;
}





/******************************************************************************
 * ---=== FUNCTION DECLARATIONS : ===---                                      *
 ******************************************************************************/
Body* generate_cube(size_t size) {
  Sprite** spheres  = (Sprite**)calloc(6 * size * size, sizeof(Sprite*));

  // Blue spheres :
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
      Sprite* back_sprite   = new_sprite( back_vertex, 16, 16, 80, "sprites/spheres_all.png",  0, 0, 16, 16);
      spheres[2*(i*size + j) + 1] = back_sprite;
    }
  }

  // Green spheres :
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
      Sprite* back_sprite   = new_sprite( back_vertex, 16, 16, 80, "sprites/spheres_all.png",  16, 0, 16, 16);
      spheres[4*size*size + 2*(i*size + j) + 1] = back_sprite;
    }
  }

  // Red spheres:
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      Vertex* front_vertex  = new_vertex( -1.0 - size,
                                           2.0 * i - size + 1.0,
                                           2.0 * j - size + 1.0 );
      Sprite* front_sprite  = new_sprite( front_vertex, 16, 16, 80, "sprites/spheres_all.png",  32, 0, 16, 16);
      spheres[2*size*size + 2*(i*size + j)] = front_sprite;
      Vertex* back_vertex   = new_vertex( 1.0 + size,
                                          2.0 * i - size + 1.0,
                                          2.0 * j - size + 1.0 );
      Sprite* back_sprite   = new_sprite( back_vertex, 16, 16, 80, "sprites/spheres_all.png",  32, 0, 16, 16);
      spheres[2*size*size + 2*(i*size + j) + 1] = back_sprite;
    }
  }

  Body* cube = new_body(6*size*size, spheres); 

  return cube;
}

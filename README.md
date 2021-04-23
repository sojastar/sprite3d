# sprite3d
A Sprite based 3D Engine

![Sprite3d Demo](demo.mov)

Sprite3d is a sprite based 3D engine. Objects are not built from polygons but from single vertices rendered as scaled and rotated sprites. The engine tries to emulate the aesthetic of late 80's/early 90's games like [After Burner](https://en.wikipedia.org/wiki/After_Burner), [Power Drift](https://en.wikipedia.org/wiki/Power_Drift) or [Galaxy Force](https://en.wikipedia.org/wiki/Galaxy_Force).

The engine example program uses RayLib as the sprite rendering backend but it can easily be modified to work with any other rendering scheme. The engine was actually developed as a C extension for the DragonRuby game engine but is provided here in a pure C version in case someone may be interested in it.

## A Basic Scene and Renderer Initialization :

```C
// --- 1. Creating a scene, the top most container for the engine.
Scene* scene = new_scene();


// --- 2. Creating a pair of 3d sprites.

// 2.1 Creating the vertices that will represent the positions ...
//     ... of the sprites in 3d space :
Vertex* vertex1 = new_vertex(-1.0, 0.0, 0.0);
Vertex* vertex2 = new_vertex( 1.0, 0.0, 0.0);

// 2.2 Actually creating the sprites. They are stored in an array ...
//     ... so as to be later passed to the Body factory function.
Sprite** sprites = (Sprite**)malloc(2 * sizeof(Sprite*));
sprites[0] = new_sprite(vertex1,
                        16, 16,                 // width and height in pixels
                        80,                     // scale
                        "sprites/sprites.png",  // sprite atlas file
                        0, 0,                   // bottom left corner in the sprite atlas
                        16, 16);                // width and height in pixels in the sprite atlas
sprites[1] = new_sprite(vertex1, 16, 16, 80, "sprites/sprites.png", 16, 0, 16, 16);


// --- 3. Creating a body, an aggregate of single sprites. A body ...
//        ... can be rotated and translated in 3d space.
Body* body = new_body(2, sprites);
scene_push_element(scene, body);      // add the body to the scene
body_move_to(cube, 0.0, 0.0, -10.0);  // move the body to a position visible by the camera


// --- 4. Creating the Camera.
float position[4] = { 0.0, 0.0, 0.0, 1.0 };            // camera position
float forward[4]  = { 0.0, 0.0,-1.0, 1.0 };            // camera forward direction
float up[4]       = { 0.0, 1.0, 0.0, 1.0 };            // Camera up direction
SCamera*  camera  = new_camera(position, forward, up);


// --- 5. Creating the Renderer.
Renderer* renderer = new_renderer(1280, 720,  // width and height of the viewport in pixels
                                  1.0,        // near clip plane distance
                                  300.0);     // far clip plane distance
```

## Manupulating Bodies :
There are a number of self explanatory functions to manipulate bodies in 3D space :
```C
void  body_move_to(Body* b,float x,float y,float z);
void  body_translate(Body* b,float x,float y,float z);
void  body_rotate_x(Body *b,float a);
void  body_rotate_y(Body *b,float a);
void  body_rotate_z(Body *b,float a);
void  body_reset_rotation(Body* b);
```

## Manipulating the Camera :
Likewise, the engine has a set of simple functions manipulate the camera in 3D space :
```C
void camera_move_to(SCamera* camera,float position[4]);
void camera_translate(SCamera* camera,float offset[4]);
void camera_look_at(SCamera* camera,float offset[4]);
void camera_rotate_x(SCamera* camera,float angle);
void camera_rotate_y(SCamera* camera,float angle);
void camera_rotate_z(SCamera* camera,float angle);
void camera_move_forward(SCamera* camera, float speed);
void camera_move_right(SCamera* camera, float speed);
void camera_move_up(SCamera* camera, float speed);
```

## Rendering the scene :
```C

// 1. Performing all the calculations :
render_scene(renderer, camera, scene);

// 2. Drawing on screen :
for (size_t i = 0; i < renderer->in_frustum_sprites_count; i++) {
  Sprite* sprite = renderer->sorted_sprites[i];
  // All the necessary informations for drawing the sprite ...
  // ... with your backend of choice are available in the  ...
  // ... enumerated sprite structure :
  // - sprite->draw_x|y for the position
  // - sprite->draw_width|height for the size
  // - sprite->draw_scale (needed by some backends )
  // - sprite->atlas_file|x|y|w|h for the sprite texture position in the texture atlas
}
```

#include "unity.h"
#include "sprite.h"

/*******************************************************************************
 * Setup and Teardown :
 ******************************************************************************/
void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}





/*******************************************************************************
 * Test Suit :
 ******************************************************************************/
void test_new_sprite(void) {
  Vertex* v = new_vertex(1.0, 2.0, 3.0);
  Sprite* s = new_sprite( v,
                          16, 16, 64,
                          "sprite_file.png",
                          0, 0, 16, 16 );

  TEST_ASSERT_EQUAL_FLOAT(               1.0, s->vertex->local[0]);
  TEST_ASSERT_EQUAL_FLOAT(               2.0, s->vertex->local[1]);
  TEST_ASSERT_EQUAL_FLOAT(               3.0, s->vertex->local[2]);
  TEST_ASSERT_EQUAL_FLOAT(               1.0, s->vertex->local[3]);
  TEST_ASSERT_EQUAL_UINT16(             1024, s->width);
  TEST_ASSERT_EQUAL_UINT16(             1024, s->height);
  TEST_ASSERT_EQUAL_UINT16(               64, s->scale);
  TEST_ASSERT_EQUAL_INT16(             -1280, s->draw_x);
  TEST_ASSERT_EQUAL_INT16(              -720, s->draw_y);
  TEST_ASSERT_EQUAL_UINT16(             1024, s->draw_width);
  TEST_ASSERT_EQUAL_UINT16(             1024, s->draw_height);
  TEST_ASSERT_EQUAL_FLOAT(               0.0, s->angle);
  TEST_ASSERT_EQUAL_STRING("sprite_file.png", s->atlas_file);
  TEST_ASSERT_EQUAL_UINT16(                0, s->atlas_x);
  TEST_ASSERT_EQUAL_UINT16(                0, s->atlas_y);
  TEST_ASSERT_EQUAL_UINT16(               16, s->atlas_w);
  TEST_ASSERT_EQUAL_UINT16(               16, s->atlas_h);

  free_sprite(s);
}

void test_sprite_compute_draw_size(void) {
  Vertex* v   = new_vertex(1.0, 2.0, 3.0);
  v->view[2]  = 10;
  v->screen_x = 200;
  v->screen_y = 50;

  Sprite* s = new_sprite( v,
                          16, 16, 64,
                          "sprite_file.png",
                          0, 0, 16, 16 );
  
  sprite_compute_draw_size(s);

  TEST_ASSERT_EQUAL_UINT16(102, s->draw_width);
  TEST_ASSERT_EQUAL_UINT16(102, s->draw_height);
  TEST_ASSERT_EQUAL_UINT16(149, s->draw_x);
  TEST_ASSERT_EQUAL_UINT16( -1, s->draw_y);

  free_sprite(s);
}

void test_sprite_rotate(void) {
  Vertex* v = new_vertex(1.0, 2.0, 3.0);
  Sprite* s = new_sprite( v,
                          16, 16, 64,
                          "sprite_file.png",
                          0, 0, 16, 16 );

  sprite_rotate(s, 367.0);
  TEST_ASSERT_EQUAL_FLOAT(7.0, s->angle);
  sprite_rotate(s, -370.0);
  TEST_ASSERT_EQUAL_FLOAT(-3.0, s->angle);

  free_sprite(s);
}

void test_sprite_rotate_absolute(void) {
  Vertex* v = new_vertex(1.0, 2.0, 3.0);
  Sprite* s = new_sprite( v,
                          16, 16, 64,
                          "sprite_file.png",
                          0, 0, 16, 16 );

  sprite_rotate_absolute(s, 367.0);
  TEST_ASSERT_EQUAL_FLOAT(7.0, s->angle);
  sprite_rotate_absolute(s, -370.0);
  TEST_ASSERT_EQUAL_FLOAT(-10.0, s->angle);

  free_sprite(s);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_new_sprite);
  RUN_TEST(test_sprite_compute_draw_size);
  RUN_TEST(test_sprite_rotate);
  RUN_TEST(test_sprite_rotate_absolute);
  
  return UNITY_END();
}

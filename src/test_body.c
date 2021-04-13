#include "unity.h"
#include "vector.h"
#include "body.h"

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
void test_new_body(void) {
  Vertex* v1    = new_vertex(1.0, 2.0, 3.0);
  Vertex* v2    = new_vertex(4.0, 5.0, 6.0);
  Vertex* v3    = new_vertex(7.0, 8.0, 9.0);
  Sprite* s1    = new_sprite(v1, 16, 16, 64, "sprite1_file.png",  0, 0, 16, 16);
  Sprite* s2    = new_sprite(v2, 16, 16, 64, "sprite2_file.png", 16, 0, 16, 16);
  Sprite* s3    = new_sprite(v3, 16, 16, 64, "sprite3_file.png", 32, 0, 16, 16);
  Sprite* sl[3] = { s1, s2, s3 };
  Body*   b     = new_body(3, sl);

  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[0][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][2]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][0]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[1][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][2]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][1]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[2][2]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[3][3]);

  TEST_ASSERT_EQUAL_UINT16(3, b->sprite_count);   // no size_t assertion
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->sprites[0]->vertex->local[0]);
  TEST_ASSERT_EQUAL_FLOAT(4.0, b->sprites[1]->vertex->local[0]);
  TEST_ASSERT_EQUAL_FLOAT(7.0, b->sprites[2]->vertex->local[0]);

  TEST_ASSERT_EQUAL_STRING("sprite1_file.png", b->sprites[0]->atlas_file);
  TEST_ASSERT_EQUAL_STRING("sprite2_file.png", b->sprites[1]->atlas_file);
  TEST_ASSERT_EQUAL_STRING("sprite3_file.png", b->sprites[2]->atlas_file);

  free_body(b);
}

void test_body_move_to(void) {
  Vertex* v1    = new_vertex(1.0, 2.0, 3.0);
  Sprite* s1    = new_sprite(v1, 16, 16, 64, "sprite_file.png",  0, 0, 16, 16);
  Sprite* sl[3] = { s1 };
  Body*   b     = new_body(1, sl);

  body_move_to(b, 1.0, 2.0, 3.0);
  body_move_to(b, 4.0, 5.0, 6.0);

  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[0][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][2]);
  TEST_ASSERT_EQUAL_FLOAT(4.0, b->world[0][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][0]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[1][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][2]);
  TEST_ASSERT_EQUAL_FLOAT(5.0, b->world[1][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][1]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[2][2]);
  TEST_ASSERT_EQUAL_FLOAT(6.0, b->world[2][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[3][3]);

  free_body(b);
}

void test_body_translate(void) {
  Vertex* v1    = new_vertex(1.0, 2.0, 3.0);
  Sprite* s1    = new_sprite(v1, 16, 16, 64, "sprite_file.png",  0, 0, 16, 16);
  Sprite* sl[3] = { s1 };
  Body*   b     = new_body(1, sl);

  body_translate(b, 1.0, 2.0, 3.0);
  body_translate(b, 4.0, 5.0, 6.0);

  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[0][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[0][2]);
  TEST_ASSERT_EQUAL_FLOAT(5.0, b->world[0][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][0]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[1][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[1][2]);
  TEST_ASSERT_EQUAL_FLOAT(7.0, b->world[1][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[2][1]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[2][2]);
  TEST_ASSERT_EQUAL_FLOAT(9.0, b->world[2][3]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, b->world[3][2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, b->world[3][3]);

  free_body(b);
}

void test_body_rotate_x(void) {
  Vertex* v1    = new_vertex(1.0, 2.0, 3.0);
  Sprite* s1    = new_sprite(v1, 16, 16, 64, "sprite_file.png",  0, 0, 16, 16);
  Sprite* sl[3] = { s1 };
  Body*   b     = new_body(1, sl);

  body_rotate_x(b, M_PI_2);

  TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[0][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[1][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[2][0]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[3][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[0][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[1][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[2][1]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[3][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[0][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001,-1.0, b->world[1][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[2][2]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[3][2]);

  free_body(b);
}

void test_body_rotate_y(void) {
  Vertex* v1    = new_vertex(1.0, 2.0, 3.0);
  Sprite* s1    = new_sprite(v1, 16, 16, 64, "sprite_file.png",  0, 0, 16, 16);
  Sprite* sl[3] = { s1 };
  Body*   b     = new_body(1, sl);

  body_rotate_y(b, M_PI_2);

  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[0][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[1][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001,-1.0, b->world[2][0]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[3][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[0][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[1][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[2][1]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[3][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[0][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[1][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[2][2]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[3][2]);

  free_body(b);
}

void test_body_rotate_z(void) {
  Vertex* v1    = new_vertex(1.0, 2.0, 3.0);
  Sprite* s1    = new_sprite(v1, 16, 16, 64, "sprite_file.png",  0, 0, 16, 16);
  Sprite* sl[3] = { s1 };
  Body*   b     = new_body(1, sl);

  body_rotate_z(b, M_PI_2);

  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[0][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[1][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[2][0]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[3][0]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001,-1.0, b->world[0][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[1][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[2][1]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[3][1]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[0][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 0.0, b->world[1][2]);
  TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[2][2]);
  //TEST_ASSERT_FLOAT_WITHIN(0.0001, 1.0, b->world[3][2]);

  free_body(b);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_new_body);
  RUN_TEST(test_body_move_to);
  RUN_TEST(test_body_translate);
  RUN_TEST(test_body_rotate_x);
  RUN_TEST(test_body_rotate_y);
  RUN_TEST(test_body_rotate_z);
  
  return UNITY_END();
}

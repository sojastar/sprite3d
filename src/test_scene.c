#include "unity.h"
#include "scene.h"

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
void test_new_scene(void) {
  Scene* s = new_scene();

  TEST_ASSERT_EQUAL_UINT16(0, s->element_count);
  TEST_ASSERT_NULL(s->first);
  TEST_ASSERT_NULL(s->last);

  free_scene(s);
}

void test_scene_push_element(void) {
  Vertex* v1      = new_vertex(1.0, 2.0, 3.0);
  Vertex* v2      = new_vertex(4.0, 5.0, 6.0);
  Vertex* v3      = new_vertex(7.0, 8.0, 9.0);
  Sprite* s1      = new_sprite(v1, 16, 16, 64, "sprite1_file.png",  0, 0, 16, 16);
  Sprite* s2      = new_sprite(v2, 16, 16, 64, "sprite2_file.png", 16, 0, 16, 16);
  Sprite* s3      = new_sprite(v3, 16, 16, 64, "sprite3_file.png", 32, 0, 16, 16);
  Sprite* sl1[1]  = { s1 };
  Sprite* sl2[1]  = { s2 };
  Sprite* sl3[1]  = { s3 };
  Body*   b1      = new_body(1, sl1);
  Body*   b2      = new_body(1, sl2);
  Body*   b3      = new_body(1, sl3);
  Scene*  s       = new_scene();

  scene_push_element(s, b1);
  scene_push_element(s, b2);
  scene_push_element(s, b3);

  TEST_ASSERT_EQUAL_UINT16(3, s->element_count);

  free_scene(s);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_new_scene);
  RUN_TEST(test_scene_push_element);
  
  return UNITY_END();
}

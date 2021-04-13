#include "unity.h"
#include "camera.h"

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
void test_new_camera(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 4.0, 5.0, 6.0, 1.0 };
  Camera* c     = new_camera(p, d);

  TEST_ASSERT_EQUAL_FLOAT(1.0, c->position[0]);
  TEST_ASSERT_EQUAL_FLOAT(2.0, c->position[1]);
  TEST_ASSERT_EQUAL_FLOAT(3.0, c->position[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, c->position[3]);

  TEST_ASSERT_EQUAL_FLOAT(4.0, c->direction[0]);
  TEST_ASSERT_EQUAL_FLOAT(5.0, c->direction[1]);
  TEST_ASSERT_EQUAL_FLOAT(6.0, c->direction[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, c->direction[3]);

  free_camera(c);
}

void test_camera_move_to(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 4.0, 5.0, 6.0, 1.0 };
  Camera* c     = new_camera(p, d);

  float   o1[4] = { 1.0, 2.0, 3.0, 1.0 };
  float   o2[4] = { 4.0, 5.0, 6.0, 1.0 };

  camera_move_to(c, o1);
  camera_move_to(c, o2);

  TEST_ASSERT_EQUAL_FLOAT(4.0, c->position[0]);
  TEST_ASSERT_EQUAL_FLOAT(5.0, c->position[1]);
  TEST_ASSERT_EQUAL_FLOAT(6.0, c->position[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, c->position[3]);

  free_camera(c);
}

void test_camera_translate(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 4.0, 5.0, 6.0, 1.0 };
  Camera* c     = new_camera(p, d);

  float   o1[4] = { 1.0, 2.0, 3.0, 1.0 };
  float   o2[4] = { 4.0, 5.0, 6.0, 1.0 };

  camera_translate(c, o1);
  camera_translate(c, o2);

  TEST_ASSERT_EQUAL_FLOAT(-3.0, c->position[0]);
  TEST_ASSERT_EQUAL_FLOAT(-2.0, c->position[1]);
  TEST_ASSERT_EQUAL_FLOAT(-1.0, c->position[2]);
  TEST_ASSERT_EQUAL_FLOAT( 1.0, c->position[3]);

  free_camera(c);
}

void test_camera_look_at(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 4.0, 5.0, 6.0, 1.0 };
  Camera* c     = new_camera(p, d);

  float   la[4] = { -3.0, -2.0, -1.0, 1.0 };
  camera_look_at(c, la);

  TEST_ASSERT_EQUAL_FLOAT(-3.0, c->direction[0]);
  TEST_ASSERT_EQUAL_FLOAT(-2.0, c->direction[1]);
  TEST_ASSERT_EQUAL_FLOAT(-1.0, c->direction[2]);
  TEST_ASSERT_EQUAL_FLOAT( 1.0, c->direction[3]);

  free_camera(c);
}

void test_camera_rotate_x(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 0.0, 0.0,-1.0, 1.0 };
  Camera* c     = new_camera(p, d);

  camera_rotate_x(c, M_PI_2);

  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 0.0, c->direction[0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 1.0, c->direction[1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 0.0, c->direction[2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 1.0, c->direction[3]);
}

void test_camera_rotate_y(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 1.0, 0.0, 0.0, 1.0 };
  Camera* c     = new_camera(p, d);

  camera_rotate_y(c, M_PI_2);

  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 0.0, c->direction[0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 0.0, c->direction[1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,-1.0, c->direction[2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 1.0, c->direction[3]);
}

void test_camera_rotate_z(void) {
  float   p[4]  = { 1.0, 2.0, 3.0, 1.0 };
  float   d[4]  = { 0.0, 1.0, 0.0, 1.0 };
  Camera* c     = new_camera(p, d);

  camera_rotate_z(c, M_PI_2);

  TEST_ASSERT_FLOAT_WITHIN( 0.0001,-1.0, c->direction[0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 0.0, c->direction[1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 0.0, c->direction[2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, 1.0, c->direction[3]);

  free_camera(c);
}

void test_camera_reset_view_matrix(void) {
}

void test_camera_compute_view_matrix(void) {
  float   p[4]  = { 0.0, 0.0, -10.0, 1.0 };
  float   d[4]  = { 1.0, 1.0,   0.0, 1.0 };
  Camera* c     = new_camera(p, d);

  camera_compute_view_matrix(c);

  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[0][0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[0][1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, -1.0,       c->view_matrix[0][2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,-10.0,       c->view_matrix[0][3]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001, -0.707106,  c->view_matrix[1][0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.707106,  c->view_matrix[1][1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[1][2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[1][3]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  1.0,       c->view_matrix[2][0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  1.0,       c->view_matrix[2][1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[2][2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[2][3]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[3][0]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[3][1]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  0.0,       c->view_matrix[3][2]);
  TEST_ASSERT_FLOAT_WITHIN( 0.0001,  1.0,       c->view_matrix[3][3]);

  free_camera(c);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_new_camera);
  RUN_TEST(test_camera_move_to);
  RUN_TEST(test_camera_look_at);
  RUN_TEST(test_camera_rotate_x);
  RUN_TEST(test_camera_rotate_y);
  RUN_TEST(test_camera_rotate_z);
  RUN_TEST(test_camera_compute_view_matrix);
  
  return UNITY_END();
}

#include "unity.h"
#include "vertex.h"

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
void test_new_vertex(void) {
  Vertex *v = new_vertex(1.0, 2.0, 3.0);

  TEST_ASSERT_EQUAL_FLOAT(1.0, v->local[0]);
  TEST_ASSERT_EQUAL_FLOAT(2.0, v->local[1]);
  TEST_ASSERT_EQUAL_FLOAT(3.0, v->local[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, v->local[3]);

  TEST_ASSERT_EQUAL_INT(UNPROCESSED, v->processed);
  TEST_ASSERT(!v->in_frustum);

  free_vertex(v);
}

void test_compute_world_coordinates(void) {
  Vertex* v         = new_vertex(1.0,2.0,3.0);
  float   bm[4][4]  = { { 1.0, 2.0, 3.0, 4.0},
                        { 5.0, 6.0, 7.0, 8.0},
                        { 9.0,10.0,11.0,12.0},
                        {13.0,14.0,15.0,16.0} };  // the transformation matrix is ...
                                                  // ... passed by the parent body 

  compute_world_coordinates(v, bm);

  TEST_ASSERT_EQUAL_FLOAT( 18.0, v->world[0]);
  TEST_ASSERT_EQUAL_FLOAT( 46.0, v->world[1]);
  TEST_ASSERT_EQUAL_FLOAT( 74.0, v->world[2]);
  TEST_ASSERT_EQUAL_FLOAT(102.0, v->world[3]);

  TEST_ASSERT_EQUAL_INT(WORLD_COORDS_CALCULATED, v->processed);

  free_vertex(v);
}

void test_compute_view_coordinates(void) {
  Vertex* v         = new_vertex(1.0,2.0,3.0);
  float   bm[4][4]  = { { 1.0, 2.0, 3.0, 4.0},
                        { 5.0, 6.0, 7.0, 8.0},
                        { 9.0,10.0,11.0,12.0},
                        {13.0,14.0,15.0,16.0} };  // the transformation matrix is ...
  // ... passed by the parent body 
  float   cm[4][4]  = { {17.0,18.0,19.0,20.0},
                        {21.0,22.0,23.0,24.0},
    {25.0,26.0,27.0,28.0},
    {29.0,30.0,31.0,32.0} };

  compute_world_coordinates(v, bm);
  compute_view_coordinates(v, cm);

  TEST_ASSERT_EQUAL_FLOAT(4580.0, v->view[0]);
  TEST_ASSERT_EQUAL_FLOAT(5540.0, v->view[1]);
  TEST_ASSERT_EQUAL_FLOAT(6500.0, v->view[2]);
  TEST_ASSERT_EQUAL_FLOAT(7460.0, v->view[3]);

  TEST_ASSERT_EQUAL_INT(VIEW_COORDS_CALCULATED, v->processed);

  free_vertex(v);
}

void test_vertex_reset(void) {
  Vertex* v = new_vertex(1.0,2.0,3.0);

  vertex_reset(v);

  TEST_ASSERT_EQUAL_FLOAT(0.0, v->local[0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, v->local[1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, v->local[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, v->local[3]);

  free_vertex(v);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_new_vertex);
  RUN_TEST(test_compute_world_coordinates);
  RUN_TEST(test_compute_view_coordinates);
  RUN_TEST(test_vertex_reset);
  
  return UNITY_END();
}

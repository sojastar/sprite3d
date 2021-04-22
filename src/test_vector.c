#include "unity.h"
#include "vector.h"

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
void test_vector_copy(void) {
  float   v[] = { 0.0, 1.0, 2.0, 3.0 };
  
  float*  c   = vector_copy(v);  // copying the vector

  TEST_ASSERT_EQUAL_FLOAT(v[0], c[0]);
  TEST_ASSERT_EQUAL_FLOAT(v[1], c[1]);
  TEST_ASSERT_EQUAL_FLOAT(v[2], c[2]);
  TEST_ASSERT_EQUAL_FLOAT(v[3], c[3]);
}

void test_vector_copy_over(void) {
  float s[] = { 0.0, 1.0, 2.0, 3.0 };
  float d[4];

  vector_copy_over(s, d);

  TEST_ASSERT_EQUAL_FLOAT(s[0], d[0]);
  TEST_ASSERT_EQUAL_FLOAT(s[1], d[1]);
  TEST_ASSERT_EQUAL_FLOAT(s[2], d[2]);
  TEST_ASSERT_EQUAL_FLOAT(s[3], d[3]);
}

void test_vector_set(void) {
  float v[] = { 0.0, 1.0, 2.0, 3.0 };

  vector_set(v, 4.0, 5.0, 6.0, 7.0);

  TEST_ASSERT_EQUAL_FLOAT(4.0, v[0]);
  TEST_ASSERT_EQUAL_FLOAT(5.0, v[1]);
  TEST_ASSERT_EQUAL_FLOAT(6.0, v[2]);
  TEST_ASSERT_EQUAL_FLOAT(7.0, v[3]);
}

void test_vector_translate(void) {
  float v[] = { 0.0, 1.0, 2.0, 3.0 };

  vector_translate(v, 4.0, 5.0, 6.0);

  TEST_ASSERT_EQUAL_FLOAT(4.0, v[0]);
  TEST_ASSERT_EQUAL_FLOAT(6.0, v[1]);
  TEST_ASSERT_EQUAL_FLOAT(8.0, v[2]);
  TEST_ASSERT_EQUAL_FLOAT(3.0, v[3]);
}

void test_vector_equality(void) {
  float v1[] = { 0.0, 1.0, 2.0, 3.0 };
  float v2[] = { 0.0, 1.0, 2.0, 3.0 };

  TEST_ASSERT(vector_equality(v1, v2));
}

void test_vector_reverse(void) {
  float v[] = { 0.0, 1.0, 2.0, 3.0 };

  vector_reverse(v);

  TEST_ASSERT_EQUAL_FLOAT( 0.0, v[0]);
  TEST_ASSERT_EQUAL_FLOAT(-1.0, v[1]);
  TEST_ASSERT_EQUAL_FLOAT(-2.0, v[2]);
  TEST_ASSERT_EQUAL_FLOAT( 3.0, v[3]);
}

void test_vector_scalar_mul(void) {
  float v[] = { 0.0, 1.0, 2.0, 3.0 };

  vector_scalar_mul(v, 1.5);

  TEST_ASSERT_EQUAL_FLOAT(0.0, v[0]);
  TEST_ASSERT_EQUAL_FLOAT(1.5, v[1]);
  TEST_ASSERT_EQUAL_FLOAT(3.0, v[2]);
  TEST_ASSERT_EQUAL_FLOAT(3.0, v[3]);
}

void test_vector_squared_magnitude(void) {
  float v[] = { 0.0, 1.0, 2.0, 3.0 };

  TEST_ASSERT_EQUAL_FLOAT(5.0, vector_squared_magnitude(v));
}

void test_vector_magnitude(void) {
  float v[] = { 0.0, 1.0, 2.0, 3.0 };

  TEST_ASSERT_EQUAL_FLOAT(sqrtf(5.0), vector_magnitude(v));
}

void test_vector_normalize(void) {
  float u[] = { 23.0,  0.0,  0.0,  1.0 };
  float v[] = {  0.0,  7.0,  0.0,  1.0 };
  float w[] = {  0.0,  0.0, 13.0,  1.0 };

  vector_normalize(u);
  vector_normalize(v);
  vector_normalize(w);

  TEST_ASSERT_EQUAL_FLOAT(1.0, u[0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, u[1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, u[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, u[3]);

  TEST_ASSERT_EQUAL_FLOAT(0.0, v[0]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, v[1]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, v[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, v[3]);

  TEST_ASSERT_EQUAL_FLOAT(0.0, w[0]);
  TEST_ASSERT_EQUAL_FLOAT(0.0, w[1]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, w[2]);
  TEST_ASSERT_EQUAL_FLOAT(1.0, w[3]);
}

void test_vector_rotate_x(void) {
  float u[] = { 1.0, 0.0, 0.0, 1.0 };
  float v[] = { 0.0, 1.0, 0.0, 1.0 };
  float w[] = { 0.0, 0.0, 1.0, 1.0 };

  float *rxu  = vector_copy(u);
  float *rxv  = vector_copy(v);
  float *rxw  = vector_copy(w);
  vector_rotate_x(rxu, M_PI_2);
  vector_rotate_x(rxv, M_PI_2);
  vector_rotate_x(rxw, M_PI_2);
  
  float* rv = vector_copy(v);
  vector_reverse(rv);

  TEST_ASSERT(vector_equality( u, rxu));
  TEST_ASSERT(vector_equality( w, rxv));
  TEST_ASSERT(vector_equality(rv, rxw));
}

void test_vector_rotate_y(void) {
  float u[] = { 1.0, 0.0, 0.0, 1.0 };
  float v[] = { 0.0, 1.0, 0.0, 1.0 };
  float w[] = { 0.0, 0.0, 1.0, 1.0 };

  float *ryu  = vector_copy(u);
  float *ryv  = vector_copy(v);
  float *ryw  = vector_copy(w);
  vector_rotate_y(ryu, M_PI_2);
  vector_rotate_y(ryv, M_PI_2);
  vector_rotate_y(ryw, M_PI_2);

  float* rw = vector_copy(w);
  vector_reverse(rw);

  TEST_ASSERT(vector_equality(rw, ryu));
  TEST_ASSERT(vector_equality( v, ryv));
  TEST_ASSERT(vector_equality( u, ryw));
}

void test_vector_rotate_z(void) {
  float u[] = { 1.0, 0.0, 0.0, 1.0 };
  float v[] = { 0.0, 1.0, 0.0, 1.0 };
  float w[] = { 0.0, 0.0, 1.0, 1.0 };

  float *rzu  = vector_copy(u);
  float *rzv  = vector_copy(v);
  float *rzw  = vector_copy(w);
  vector_rotate_z(rzu, M_PI_2);
  vector_rotate_z(rzv, M_PI_2);
  vector_rotate_z(rzw, M_PI_2);

  float* ru = vector_copy(u);
  vector_reverse(ru);

  TEST_ASSERT(vector_equality( v, rzu));
  TEST_ASSERT(vector_equality(ru, rzv));
  TEST_ASSERT(vector_equality( w, rzw));
}

void test_vector_cross_product(void) {
    float v1[]  = { 1.0, 2.0, 3.0, 1.0 };
    float v2[]  = { 4.0, 5.0, 6.0, 1.0 };

    float cp[4];
    vector_cross_product(v1, v2, cp);

    TEST_ASSERT_EQUAL_FLOAT(-3.0, cp[0]);
    TEST_ASSERT_EQUAL_FLOAT( 6.0, cp[1]);
    TEST_ASSERT_EQUAL_FLOAT(-3.0, cp[2]);
    TEST_ASSERT_EQUAL_FLOAT( 1.0, cp[3]);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_vector_copy);
  RUN_TEST(test_vector_set);
  RUN_TEST(test_vector_translate);
  RUN_TEST(test_vector_equality);
  RUN_TEST(test_vector_reverse);
  RUN_TEST(test_vector_scalar_mul);
  RUN_TEST(test_vector_squared_magnitude);
  RUN_TEST(test_vector_magnitude);
  RUN_TEST(test_vector_normalize);
  RUN_TEST(test_vector_rotate_x);
  RUN_TEST(test_vector_rotate_y);
  RUN_TEST(test_vector_rotate_z);
  RUN_TEST(test_vector_cross_product);
  
  return UNITY_END();
}

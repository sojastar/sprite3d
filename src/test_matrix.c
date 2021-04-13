#include "unity.h"
#include "matrix.h"

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
void test_matrix_copy(void) {
  float s[4][4] = { {  0.0,  1.0,  2.0,  3.0 },
                    {  4.0,  5.0,  6.0,  7.0 },
                    {  8.0,  9.0, 10.0, 11.0 }, 
                    { 12.0, 13.0, 14.0, 15.0 } };
  float d[4][4];

  matrix_copy(s,d);

  for(size_t i = 0; i < 4; i += 1)
    for(size_t j = 0; j < 4; j += 1)
      TEST_ASSERT_EQUAL_FLOAT(s[i][j], d[i][j]);
}

void test_matrix_negate(void) {
  float m[4][4] = { { 1,  2,  3,  4},
                    { 5,  6,  7,  8},
                    { 9, 10, 11, 12},
                    {13, 14, 15, 16} };

  matrix_negate(m);

  TEST_ASSERT_EQUAL_FLOAT( -1, m[0][0]);
  TEST_ASSERT_EQUAL_FLOAT( -2, m[0][1]);
  TEST_ASSERT_EQUAL_FLOAT( -3, m[0][2]);
  TEST_ASSERT_EQUAL_FLOAT( -4, m[0][3]);
  TEST_ASSERT_EQUAL_FLOAT( -5, m[1][0]);
  TEST_ASSERT_EQUAL_FLOAT( -6, m[1][1]);
  TEST_ASSERT_EQUAL_FLOAT( -7, m[1][2]);
  TEST_ASSERT_EQUAL_FLOAT( -8, m[1][3]);
  TEST_ASSERT_EQUAL_FLOAT( -9, m[2][0]);
  TEST_ASSERT_EQUAL_FLOAT(-10, m[2][1]);
  TEST_ASSERT_EQUAL_FLOAT(-11, m[2][2]);
  TEST_ASSERT_EQUAL_FLOAT(-12, m[2][3]);
  TEST_ASSERT_EQUAL_FLOAT(-13, m[3][0]);
  TEST_ASSERT_EQUAL_FLOAT(-14, m[3][1]);
  TEST_ASSERT_EQUAL_FLOAT(-15, m[3][2]);
  TEST_ASSERT_EQUAL_FLOAT(-16, m[3][3]);
}

void test_matrix_matrix_add(void) {
  float m1[4][4]  = { { 1,  2,  3,  4},
                      { 5,  6,  7,  8},
                      { 9, 10, 11, 12},
                      {13, 14, 15, 16} };
  float m2[4][4]  = { { 1,  2,  1,  2},
                      { 2,  1,  2,  1},
                      { 1,  2,  1,  2},
                      { 2,  1,  2,  1} };
  float r[4][4];

  matrix_matrix_add(m1, m2, r);

  TEST_ASSERT_EQUAL_FLOAT( 2, r[0][0]);
  TEST_ASSERT_EQUAL_FLOAT( 4, r[0][1]);
  TEST_ASSERT_EQUAL_FLOAT( 4, r[0][2]);
  TEST_ASSERT_EQUAL_FLOAT( 6, r[0][3]);
  TEST_ASSERT_EQUAL_FLOAT( 7, r[1][0]);
  TEST_ASSERT_EQUAL_FLOAT( 7, r[1][1]);
  TEST_ASSERT_EQUAL_FLOAT( 9, r[1][2]);
  TEST_ASSERT_EQUAL_FLOAT( 9, r[1][3]);
  TEST_ASSERT_EQUAL_FLOAT(10, r[2][0]);
  TEST_ASSERT_EQUAL_FLOAT(12, r[2][1]);
  TEST_ASSERT_EQUAL_FLOAT(12, r[2][2]);
  TEST_ASSERT_EQUAL_FLOAT(14, r[2][3]);
  TEST_ASSERT_EQUAL_FLOAT(15, r[3][0]);
  TEST_ASSERT_EQUAL_FLOAT(15, r[3][1]);
  TEST_ASSERT_EQUAL_FLOAT(17, r[3][2]);
  TEST_ASSERT_EQUAL_FLOAT(17, r[3][3]);
}

void test_matrix_matrix_mul(void) {
    float m1[4][4]  = { { 1,  2,  3,  4},
                        { 5,  6,  7,  8},
                        { 9, 10, 11, 12},
                        {13, 14, 15, 16} };
    float m2[4][4]  = { { 1,  2,  1,  2},
                        { 2,  1,  2,  1},
                        { 1,  2,  1,  2},
                        { 2,  1,  2,  1} };
    float r[4][4];

    matrix_matrix_mul(m1, m2, r);

    TEST_ASSERT_EQUAL_FLOAT(16, r[0][0]);
    TEST_ASSERT_EQUAL_FLOAT(14, r[0][1]);
    TEST_ASSERT_EQUAL_FLOAT(16, r[0][2]);
    TEST_ASSERT_EQUAL_FLOAT(14, r[0][3]);
    TEST_ASSERT_EQUAL_FLOAT(40, r[1][0]);
    TEST_ASSERT_EQUAL_FLOAT(38, r[1][1]);
    TEST_ASSERT_EQUAL_FLOAT(40, r[1][2]);
    TEST_ASSERT_EQUAL_FLOAT(38, r[1][3]);
    TEST_ASSERT_EQUAL_FLOAT(64, r[2][0]);
    TEST_ASSERT_EQUAL_FLOAT(62, r[2][1]);
    TEST_ASSERT_EQUAL_FLOAT(64, r[2][2]);
    TEST_ASSERT_EQUAL_FLOAT(62, r[2][3]);
    TEST_ASSERT_EQUAL_FLOAT(88, r[3][0]);
    TEST_ASSERT_EQUAL_FLOAT(86, r[3][1]);
    TEST_ASSERT_EQUAL_FLOAT(88, r[3][2]);
    TEST_ASSERT_EQUAL_FLOAT(86, r[3][3]);
}

void test_d_matrix_matrix_mul(void) {
    float m1[4][4]  = { { 1,  2,  3,  4},
                        { 5,  6,  7,  8},
                        { 9, 10, 11, 12},
                        {13, 14, 15, 16} };
    float m2[4][4]  = { { 1,  2,  1,  2},
                        { 2,  1,  2,  1},
                        { 1,  2,  1,  2},
                        { 2,  1,  2,  1} };

    d_matrix_matrix_mul(m1, m2, m1);

    TEST_ASSERT_EQUAL_FLOAT(16, m1[0][0]);
    TEST_ASSERT_EQUAL_FLOAT(14, m1[0][1]);
    TEST_ASSERT_EQUAL_FLOAT(16, m1[0][2]);
    TEST_ASSERT_EQUAL_FLOAT(14, m1[0][3]);
    TEST_ASSERT_EQUAL_FLOAT(40, m1[1][0]);
    TEST_ASSERT_EQUAL_FLOAT(38, m1[1][1]);
    TEST_ASSERT_EQUAL_FLOAT(40, m1[1][2]);
    TEST_ASSERT_EQUAL_FLOAT(38, m1[1][3]);
    TEST_ASSERT_EQUAL_FLOAT(64, m1[2][0]);
    TEST_ASSERT_EQUAL_FLOAT(62, m1[2][1]);
    TEST_ASSERT_EQUAL_FLOAT(64, m1[2][2]);
    TEST_ASSERT_EQUAL_FLOAT(62, m1[2][3]);
    TEST_ASSERT_EQUAL_FLOAT(88, m1[3][0]);
    TEST_ASSERT_EQUAL_FLOAT(86, m1[3][1]);
    TEST_ASSERT_EQUAL_FLOAT(88, m1[3][2]);
    TEST_ASSERT_EQUAL_FLOAT(86, m1[3][3]);
}

void test_matrix_vector_mul(void) {
    float m[4][4] = { { 1,  2,  3,  4},
                      { 5,  6,  7,  8},
                      { 9, 10, 11, 12},
                      {13, 14, 15, 16} };
    float v[4]    = {1, 2, 3, 4};
    float r[4];

    matrix_vector_mul(m, v, r);

    TEST_ASSERT_EQUAL_FLOAT( 30, r[0]);
    TEST_ASSERT_EQUAL_FLOAT( 70, r[1]);
    TEST_ASSERT_EQUAL_FLOAT(110, r[2]);
    TEST_ASSERT_EQUAL_FLOAT(150, r[3]);
}

void test_d_matrix_vector_mul(void) {
    float m[4][4] = { { 1,  2,  3,  4},
                      { 5,  6,  7,  8},
                      { 9, 10, 11, 12},
                      {13, 14, 15, 16} };
    float v[4]    = {1, 2, 3, 4};

    d_matrix_vector_mul(m, v);

    TEST_ASSERT_EQUAL_FLOAT( 30, v[0]);
    TEST_ASSERT_EQUAL_FLOAT( 70, v[1]);
    TEST_ASSERT_EQUAL_FLOAT(110, v[2]);
    TEST_ASSERT_EQUAL_FLOAT(150, v[3]);
}





/*******************************************************************************
 * Main :
 ******************************************************************************/
int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_matrix_copy);
  RUN_TEST(test_matrix_negate);
  RUN_TEST(test_matrix_matrix_add);
  RUN_TEST(test_matrix_matrix_mul);
  RUN_TEST(test_d_matrix_matrix_mul);
  RUN_TEST(test_matrix_vector_mul);
  RUN_TEST(test_d_matrix_vector_mul);
  
  return UNITY_END();
}


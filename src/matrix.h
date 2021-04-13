/*******************************************************************************
 * CONSTANTS :
 ******************************************************************************/
#define IDENTITY_MATRIX { {1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0} }





/*******************************************************************************
 * FUNCTION PROTOTYPES :
 ******************************************************************************/
void matrix_print(float m[static 4][4]);
void matrix_copy(float s[static 4][4],float d[static 4][4]);
void matrix_negate(float m[static 4][4]);
void matrix_matrix_add(float m1[static 4][4],float m2[static 4][4],float r[static 4][4]);
void matrix_matrix_mul(float m1[static 4][4],float m2[static 4][4],float r[static 4][4]);
void d_matrix_matrix_mul(float m1[static 4][4],float m2[static 4][4],float r[static 4][4]);
void matrix_vector_mul(float m[static 4][4],float v[static 4],float r[static 4]);
void d_matrix_vector_mul(float m[static 4][4],float v[static 4]);

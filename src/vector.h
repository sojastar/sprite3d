#include <stdbool.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES :
 ******************************************************************************/
float*  vector_copy(float v[static 4]);
void    vector_set(float v[static 4],float x,float y,float z,float w);
void    vector_translate(float v[static 4], float dx,float dy,float dz);
bool    vector_equality(float v1[static 4],float v2[static 4]);
void    vector_reverse(float v[static 4]);
void    vector_scalar_mul(float v[static 4],float s);
float   vector_squared_magnitude(float v[static 4]);
float   vector_magnitude(float v[static 4]);
void    vector_normalize(float v[static 4]);
void    vector_rotate_x(float v[static 4],float angle);
void    vector_rotate_y(float v[static 4],float angle);
void    vector_rotate_z(float v[static 4],float angle);
void    vector_cross_product(float v1[static 4],float v2[static 4],float p[static 4]);

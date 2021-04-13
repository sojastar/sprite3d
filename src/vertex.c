#include <stdlib.h>
#include "matrix.h"
#include "vertex.h"

Vertex* new_vertex(float x,float y,float z) {
  Vertex *v = (Vertex *)malloc(sizeof(Vertex));

  v->local[0]   = x;
  v->local[1]   = y;
  v->local[2]   = z;
  v->local[3]   = 1.0;

  v->processed  = UNPROCESSED;

  return v;
}

void free_vertex(Vertex* v) {
  free(v);
}

void compute_world_coordinates(Vertex* v,float m[static 4][4]) {
  matrix_vector_mul(m, v->local, v->world);
  v->processed = WORLD_COORDS_CALCULATED;
}

void compute_view_coordinates(Vertex* v,float m[static 4][4]) {
  matrix_vector_mul(m, v->world, v->view);
  v->processed = VIEW_COORDS_CALCULATED;
}

void vertex_reset(Vertex *v) {
  v->local[0]   = 0.0;
  v->local[1]   = 0.0;
  v->local[2]   = 0.0;
  v->local[3]   = 1.0;

  v->processed  = UNPROCESSED;
}

#include <stdlib.h>
#include "scene.h"

Scene* new_scene(void) {
  Scene* s = (Scene *)malloc(sizeof(Scene));

  s->element_count  = 0;
  s->first          = (void*)0;
  s->last           = (void*)0;

  return s;
}

void scene_push_element(Scene* s,Body* b) {
  Element* e = (Element*)malloc(sizeof(Element));

  e->body     = b;
  e->previous = s->last;
  e->next     = (void*)0;

  if(s->element_count == 0)
    s->first        = e;
  s->last           = e;
  s->element_count += 1;
}

void free_scene(Scene* s) {
  Element* current;
  Element* next;
  
  current = s->first;
  /*do {
    next = current->next;

    free_body(current->body);
    free(current);

    current = next;

  } while(current != (void*)0);*/
  while(current != (void*)0) {
    next    = current->next;

    free(current->body);
    free(current);

    current = next;
  }

  free(s);
}

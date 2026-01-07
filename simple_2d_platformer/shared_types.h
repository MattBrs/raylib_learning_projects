#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

#include <raylib.h>

typedef struct {
  Vector2 movement_direction;
  bool jump;
  bool interact;
  bool load_next_scene;
} InputState;

typedef struct {
  float fall_acceleration;
} GameState;

#endif

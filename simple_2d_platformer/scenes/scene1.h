#ifndef SCENE_1_H
#define SCENE_1_H

#include <raylib.h>
#include <stdint.h>

#include "../scene_manager.h"

typedef struct {
  Camera2D camera;
  Rectangle rect;
  Rectangle player_rect;
  float player_fall_speed;
  bool player_can_jump;
  Rectangle collision_objects[10];
  uint32_t collision_objects_count;
} Scene1;

Scene1 *scene1_load();
void scene1_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change);
void scene1_draw(void *data);
void scene1_unload(void *data);

#endif // !SCENE_1_H

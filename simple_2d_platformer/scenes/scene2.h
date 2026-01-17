#ifndef SCENE_2_H
#define SCENE_2_H

#include <raylib.h>

#include "../scene_manager.h"

typedef struct {
  Camera2D camera;
  Rectangle next_level_rect;
  Rectangle player_rect;
  bool player_can_jump;
  float player_fall_speed;
  Rectangle collision_objects[10];
  int collision_objects_count;
} Scene2;

Scene2 *scene2_load();
void scene2_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change);
void scene2_draw(void *data);
void scene2_unload(void *data);

#endif // !SCENE_2_H

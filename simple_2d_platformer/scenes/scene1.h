#ifndef SCENE_1_H
#define SCENE_1_H

#include <raylib.h>

#include "../scene_manager.h"

typedef struct {
  Camera2D camera;
  Rectangle rect;
  Rectangle player_rect;
} Scene1;

Scene1 *scene1_load();
void scene1_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change);
void scene1_draw(void *data);
void scene1_unload(void *data);

#endif // !SCENE_1_H

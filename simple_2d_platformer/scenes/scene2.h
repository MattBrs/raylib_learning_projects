#ifndef SCENE_2_H
#define SCENE_2_H

#include <raylib.h>

#include "../scene_manager.h"

typedef struct {
  Camera2D camera;
  Rectangle rect;
} Scene2;

Scene2 *scene2_load();
void scene2_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change);
void scene2_draw(void *data, float delta);
void scene2_unload(void *data);

#endif // !SCENE_2_H

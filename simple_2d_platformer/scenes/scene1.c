#include "scene1.h"
#include "raylib.h"
#include <stdlib.h>

Scene1 *scene1_load() {
  Scene1 *scene_data = malloc(sizeof(Scene1));

  scene_data->rect.width = 40.f;
  scene_data->rect.height = 40.f;
  scene_data->rect.x = 40.f;
  scene_data->rect.y = 40.f;

  scene_data->camera.zoom = 1.f;
  scene_data->camera.rotation = 0.f;
  scene_data->camera.target = (Vector2){scene_data->rect.x, scene_data->rect.y};
  scene_data->camera.offset =
      (Vector2){(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};

  return scene_data;
}

void scene1_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change) {}

void scene1_draw(void *data, float delta) {
  Scene1 *scene_data = (Scene1 *)data;

  Rectangle *rect = &scene_data->rect;
  Camera2D *camera = &scene_data->camera;

  BeginMode2D(*camera);
  DrawRectangle(rect->x, rect->y, rect->width, rect->height, RED);
  EndMode2D();
}

void scene1_unload(void *data) {
  Scene1 *scene_data = (Scene1 *)data;
  free(scene_data);
}

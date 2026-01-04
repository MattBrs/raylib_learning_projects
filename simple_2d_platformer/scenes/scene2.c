#include "scene2.h"
#include "raylib.h"
#include <stdlib.h>

Scene2 *scene2_load() {
  Scene2 *scene_data = malloc(sizeof(Scene2));

  scene_data->rect.width = 40.f;
  scene_data->rect.height = 40.f;
  scene_data->rect.x = 90.f;
  scene_data->rect.y = 90.f;

  scene_data->camera.zoom = 1.f;
  scene_data->camera.rotation = 0.f;
  scene_data->camera.target = (Vector2){scene_data->rect.x, scene_data->rect.y};
  scene_data->camera.offset =
      (Vector2){(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};

  return scene_data;
}

void scene2_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change) {}

void scene2_draw(void *data, float delta) {
  Scene2 *scene_data = (Scene2 *)data;

  Rectangle *rect = &scene_data->rect;
  Camera2D *camera = &scene_data->camera;

  BeginMode2D(*camera);
  DrawRectangle(rect->x, rect->y, rect->width, rect->height, GREEN);
  EndMode2D();
}

void scene2_unload(void *data) {
  Scene2 *scene_data = (Scene2 *)data;
  free(scene_data);
}

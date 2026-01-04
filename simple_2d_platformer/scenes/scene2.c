#include "scene2.h"
#include "raylib.h"
#include <stdlib.h>

Scene2 *scene2_load() {
  Scene2 *scene_data = malloc(sizeof(Scene2));
  float screen_width = GetScreenWidth();
  float screen_heigth = GetScreenHeight();

  scene_data->player_rect.width = 40.f;
  scene_data->player_rect.height = 40.f;
  scene_data->player_rect.x = screen_width / 2;
  scene_data->player_rect.y = screen_heigth / 2;

  scene_data->rect.width = 40.f;
  scene_data->rect.height = 40.f;
  scene_data->rect.x = 40.f;
  scene_data->rect.y = 40.f;

  scene_data->camera.zoom = 1.f;
  scene_data->camera.rotation = 0.f;
  scene_data->camera.offset =
      (Vector2){(screen_width / 2) - scene_data->player_rect.width / 2,
                (screen_heigth / 2) - scene_data->player_rect.height / 2};
  scene_data->camera.target =
      (Vector2){scene_data->player_rect.x, scene_data->player_rect.y};

  return scene_data;
}

void scene2_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change) {
  float frametime = GetFrameTime();
  Scene2 *scene_data = (Scene2 *)data;

  scene_data->player_rect.x +=
      input_state->movement_direction.x * frametime * 200.f;
  scene_data->player_rect.y +=
      input_state->movement_direction.y * frametime * 200.f;

  scene_data->camera.target =
      (Vector2){scene_data->player_rect.x, scene_data->player_rect.y};

  if (input_state->load_next_scene) {
    request_change(context, 0x01);
  }
}

void scene2_draw(void *data) {
  Scene2 *scene_data = (Scene2 *)data;

  BeginMode2D(scene_data->camera);

  DrawRectangleRec(scene_data->rect, GREEN);
  DrawRectangleRec(scene_data->player_rect, BLUE);

  EndMode2D();
}

void scene2_unload(void *data) {
  Scene2 *scene_data = (Scene2 *)data;
  free(scene_data);
}

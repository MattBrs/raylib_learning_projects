#include "scene1.h"
#include "raylib.h"
#include <stdlib.h>
#include <string.h>

Scene1 *scene1_load() {
  Scene1 *scene_data = malloc(sizeof(Scene1));

  float screen_width = GetScreenWidth();
  float screen_heigth = GetScreenHeight();

  scene_data->player_fall_speed = 0.f;
  scene_data->player_can_jump = true;
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

  Rectangle collision_objects[3];
  collision_objects[0] = (Rectangle){0, 300, 500, 50};
  collision_objects[1] = (Rectangle){
      (screen_width / 2) - 200,
      (screen_heigth / 2) + (scene_data->player_rect.height), 500, 50};
  collision_objects[2] = (Rectangle){1000, 300, 500, 50};

  scene_data->collision_objects_count = 3;
  memcpy(scene_data->collision_objects, collision_objects,
         sizeof(collision_objects));

  return scene_data;
}

void scene1_process(void *data, void *context, InputState *input_state,
                    RequestSceneCb request_change) {
  float frametime = GetFrameTime();
  Scene1 *scene_data = (Scene1 *)data;

  if (input_state->jump && scene_data->player_can_jump) {
    scene_data->player_fall_speed = -1000.f * 1.5f;
    scene_data->player_can_jump = false;
  }

  bool hit_obstacle = false;
  Rectangle *p = &scene_data->player_rect;
  float player_feet_x = p->x + (p->width / 2);
  float player_feet_y = p->y + p->height;
  for (int i = 0; i < scene_data->collision_objects_count; ++i) {
    Rectangle rect = scene_data->collision_objects[i];
    if (rect.x <= player_feet_x && rect.x + rect.width >= player_feet_x &&
        rect.y >= player_feet_y &&
        rect.y <= player_feet_y + (scene_data->player_fall_speed * frametime)) {
      hit_obstacle = true;
      scene_data->player_fall_speed = 0.f;
      p->y = rect.y - p->height;
      scene_data->player_can_jump = true;

      break;
    }
  }

  if (!hit_obstacle) {
    scene_data->player_fall_speed += 2000 * frametime * 3;
    scene_data->player_rect.y += scene_data->player_fall_speed * frametime;
    scene_data->player_can_jump = false;
  } else {
    scene_data->player_can_jump = true;
  }

  scene_data->player_rect.x +=
      input_state->movement_direction.x * frametime * 700.f;

  scene_data->camera.target =
      (Vector2){scene_data->player_rect.x, scene_data->player_rect.y};

  if (input_state->load_next_scene) {
    request_change(context, 0x02);
  }
}

void scene1_draw(void *data) {
  Scene1 *scene_data = (Scene1 *)data;

  BeginMode2D(scene_data->camera);

  DrawRectangleRec(scene_data->rect, RED);
  DrawRectangleRec(scene_data->player_rect, BLUE);

  for (int i = 0; i < scene_data->collision_objects_count; ++i) {
    DrawRectangleRec(scene_data->collision_objects[i], DARKGRAY);
  }

  EndMode2D();
}

void scene1_unload(void *data) {
  Scene1 *scene_data = (Scene1 *)data;
  free(scene_data);
}

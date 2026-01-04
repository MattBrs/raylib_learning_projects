
#include <raylib.h>
#include <stdio.h>

#include "main.h"
#include "raymath.h"
#include "scene_manager.h"
#include "shared_types.h"

int main(int argc, char **argv) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGTH,
             "A simple platformer");

  SceneManager scene_manager = {0};
  scene_manager_load(&scene_manager, 0x01);

  while (!WindowShouldClose()) {
    InputState input_state = handle_input();

    scene_manager_process(&scene_manager, &input_state);

    if (scene_manager.pending_scene != -1) {
      scene_manager_load(&scene_manager, scene_manager.pending_scene);
    }

    draw(&scene_manager);
  }

  scene_manager_load(&scene_manager, 0x00);

  CloseWindow();
  return 0;
}

void draw(SceneManager *scene_manager) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  scene_manager_draw(scene_manager, GetFrameTime());

  EndDrawing();
}

InputState handle_input() {
  Vector2 direction = {0, 0};
  InputState input_state = {0};

  if (IsKeyDown(KEY_N)) {
    input_state.load_next_scene = true;
  }

  if (IsKeyDown(KEY_SPACE)) {
    input_state.jump = true;
  }

  if (IsKeyDown(KEY_A)) {
    direction.x -= 1;
  }

  if (IsKeyDown(KEY_D)) {
    direction.x += 1;
  }

  if (Vector2Length(direction) != 0) {
    direction = Vector2Normalize(direction);
  }

  input_state.movement_direction = direction;

  return input_state;
}

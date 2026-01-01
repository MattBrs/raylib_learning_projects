#include <raylib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  const int window_width = 1280;
  const int window_heigth = 720;

  InitWindow(window_width, window_heigth, "raylib basic window");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Hello and welcome to my window!", 500, 300, 24, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

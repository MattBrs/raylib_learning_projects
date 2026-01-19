#include <raylib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720

int main(int argc, char *argv[]) {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Camera 3d");

  DisableCursor();

  Camera3D camera = {0};
  camera.position = (Vector3){0.f, 10.f, 10.f};
  camera.target = (Vector3){0.f, 0.f, 0.f};
  camera.up = (Vector3){0.f, 1.f, 0.f};
  camera.fovy = 40.f;
  camera.projection = CAMERA_PERSPECTIVE;

  Vector3 cube_position = {0.f, 0.f, 0.f};

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_Z)) {
      camera.position = (Vector3){0.f, 10.f, 10.f};
      camera.target = (Vector3){0.f, 0.f, 0.f};
      cube_position = (Vector3){0.f, 0.f, 0.f};
    }

    if (IsKeyDown(KEY_LEFT)) {
      cube_position.x -= 2.f * GetFrameTime();
    }

    if (IsKeyDown(KEY_RIGHT)) {
      cube_position.x += 2.f * GetFrameTime();
    }

    if (IsKeyDown(KEY_UP)) {
      cube_position.z -= 2.f * GetFrameTime();
    }

    if (IsKeyDown(KEY_DOWN)) {
      cube_position.z += 2.f * GetFrameTime();
    }

    if (IsKeyDown(KEY_SPACE)) {
      cube_position.y -= 2.f * GetFrameTime();
    }

    if (IsKeyDown(KEY_LEFT_CONTROL)) {
      cube_position.y += 2.f * GetFrameTime();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    UpdateCamera(&camera, CAMERA_FREE);
    DrawCube(cube_position, 2.f, 2.f, 2.f, RED);
    DrawCubeWires(cube_position, 2.f, 2.f, 2.f, BROWN);
    DrawGrid(10, 1.f);

    EndMode3D();

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
}

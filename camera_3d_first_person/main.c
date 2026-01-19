#include <raylib.h>

int main(int argc, char *argv[]) {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(1280, 720, "first person 3d camera");

  DisableCursor();
  SetTargetFPS(61);

  Camera3D camera = {0};
  camera.position = (Vector3){0.f, 2.f, 4.f};
  camera.target = (Vector3){0.f, 2.f, 0.f};
  camera.fovy = 70.f;
  camera.up = (Vector3){0.f, 1.f, 0.f};
  camera.projection = CAMERA_PERSPECTIVE;

  float movement_speed = 100.f;

  while (!WindowShouldClose()) {

    Vector3 velocity = {0};
    Vector2 direction = {0};
    float frametime = GetFrameTime();

    if (IsKeyDown(KEY_W)) {
      direction.y += 1;
    }

    if (IsKeyDown(KEY_A)) {
      direction.x -= 1;
    }

    if (IsKeyDown(KEY_S)) {
      direction.y -= 1;
    }

    if (IsKeyDown(KEY_D)) {
      direction.x += 1;
    }

    velocity = (Vector3){direction.y * movement_speed * frametime,
                         direction.x * movement_speed * frametime, 0.f};

    UpdateCameraPro(
        &camera, velocity,
        (Vector3){GetMouseDelta().x * 0.05f, GetMouseDelta().y * 0.05f, 0.f},
        GetMouseWheelMove() * 2.f);

    BeginDrawing();
    ClearBackground(SKYBLUE);

    BeginMode3D(camera);

    DrawPlane((Vector3){0.f, 0.f, 0.f}, (Vector2){100.f, 100.f}, BROWN);

    EndMode3D();

    DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2, 3.f, 3.f,
                  RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

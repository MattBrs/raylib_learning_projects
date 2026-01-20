#include <raylib.h>
#include <raymath.h>

#define MAX_PROPS 32

typedef struct {
  Color colors[MAX_PROPS];
  float heights[MAX_PROPS];
  Vector3 positions[MAX_PROPS];
} Props;

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
  Props props;

  for (int i = 0; i < MAX_PROPS; ++i) {
    props.heights[i] = (float)GetRandomValue(1, 32);
    props.positions[i] = (Vector3){
        GetRandomValue(-50, 50), props.heights[i] / 2, GetRandomValue(-50, 50)};
    props.colors[i] = (Color){GetRandomValue(20, 255), GetRandomValue(20, 255),
                              GetRandomValue(20, 255), 255};
  }

  while (!WindowShouldClose()) {

    Vector3 velocity = {0};
    Vector3 rotation = {0};
    Vector2 direction = {0};
    float frametime = GetFrameTime();
    Vector2 mouse_delta = GetMouseDelta();

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

    if (Vector2Length(direction) != 0) {
      direction = Vector2Normalize(direction);
    }

    if (Vector2Length(mouse_delta) != 0) {
      rotation = (Vector3){mouse_delta.x * 0.05f, mouse_delta.y * 0.05f, 0.f};
    }

    velocity = (Vector3){direction.y * movement_speed * frametime,
                         direction.x * movement_speed * frametime, 0.f};

    UpdateCameraPro(&camera, velocity, rotation, 0.f);

    BeginDrawing();
    ClearBackground(SKYBLUE);

    BeginMode3D(camera);

    DrawPlane((Vector3){0.f, 0.f, 0.f}, (Vector2){100.f, 100.f}, BROWN);

    for (int i = 0; i < MAX_PROPS; ++i) {
      DrawCube(props.positions[i], 8.f, props.heights[i], 8.f, props.colors[i]);
      DrawCubeWires(props.positions[i], 8.f, props.heights[i], 8.f,
                    (Color){100.f, 0.f, 0.f, 255});
    }

    DrawCube((Vector3){50.f, 30.f, 0.f}, 5.f, 60.f, 100.f, GOLD);
    DrawCube((Vector3){-50.f, 30.f, 0.f}, 5.f, 60.f, 100.f, GOLD);
    DrawCube((Vector3){0.f, 30.f, 50.f}, 100.f, 60.f, 5.f, GOLD);
    DrawCube((Vector3){0.f, 30.f, -50.f}, 100.f, 60.f, 5.f, GOLD);

    EndMode3D();

    DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2, 3.f, 3.f,
                  RAYWHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

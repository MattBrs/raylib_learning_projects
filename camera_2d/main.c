#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGTH 720

typedef struct Player {
  Rectangle body;
  float speed;
  Vector2 direction;
} Player;

typedef struct Scene {
  Player player;
  Rectangle prop1;
  Rectangle prop2;
  Rectangle prop3;
  Camera2D camera;
  Vector2 cursor_position;
  bool is_camera_moved;
} Scene;

static Scene scene;

void init();
void draw();
void process();
void handle_input();

int main(int argc, char *argv[]) {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "camera 2d movements");
  HideCursor();

  init();

  while (!WindowShouldClose()) {
    handle_input();
    process();
    draw();
  }

  CloseWindow();
  return 0;
}

void init() {
  scene.is_camera_moved = false;

  scene.player.body.x = (float)SCREEN_WIDTH / 2;
  scene.player.body.y = (float)SCREEN_HEIGTH / 2;
  scene.player.body.width = 50.f;
  scene.player.body.height = 100.f;
  scene.player.speed = 300.f;
  scene.player.direction = (Vector2){0, 0};

  scene.prop1.width = 20;
  scene.prop1.height = 40;
  scene.prop1.x = (float)SCREEN_WIDTH / 2 + 400.f;
  scene.prop1.y = (float)SCREEN_HEIGTH / 2 + 150.f;

  scene.prop2.width = 20;
  scene.prop2.height = 40;
  scene.prop2.x = (float)SCREEN_WIDTH / 2 + 1000.f;
  scene.prop2.y = (float)SCREEN_HEIGTH / 2;

  scene.prop3.width = 80;
  scene.prop3.height = 120;
  scene.prop3.x = (float)SCREEN_WIDTH / 2 - 300.f;
  scene.prop3.y = (float)SCREEN_HEIGTH / 2 - 300.f;

  scene.camera.target =
      (Vector2){scene.player.body.x + 20.f, scene.player.body.y + 20.f};
  scene.camera.offset =
      (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGTH / 2};
  scene.camera.zoom = 1.f;
  scene.camera.rotation = 0.f;
}

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  BeginMode2D(scene.camera);

  DrawRectangleRec(scene.player.body, DARKPURPLE);
  DrawRectangleRec(scene.prop1, BROWN);
  DrawRectangleRec(scene.prop2, BLUE);
  DrawRectangleRec(scene.prop3, YELLOW);

  EndMode2D();

  DrawCircleV(scene.cursor_position, 5.f, DARKGRAY);

  DrawText("Move player (purple) with WASD", 10.f, 10.f, 24, DARKGRAY);
  DrawText("Zoom camera with mouse wheel", 10.f, 30.f, 24, DARKGRAY);
  DrawText("Rotate camera with Q/E", 10.f, 50.f, 24, DARKGRAY);
  DrawText("Move around camera with mouse drag", 10.f, 70.f, 24, DARKGRAY);
  DrawText("Reset camera rotation, zoom and position with R", 10.f, 90.f, 24,
           DARKGRAY);

  EndDrawing();
}

void process() {
  float frametime = GetFrameTime();
  scene.player.body.x +=
      frametime * scene.player.direction.x * scene.player.speed;
  scene.player.body.y +=
      frametime * scene.player.direction.y * scene.player.speed;

  if (!scene.is_camera_moved) {
    scene.camera.target =
        (Vector2){scene.player.body.x + 20.f, scene.player.body.y + 20.f};
  }

  if (scene.camera.rotation > 45.f) {
    scene.camera.rotation = 45.f;
  }
  if (scene.camera.rotation < -45.f) {
    scene.camera.rotation = -45.f;
  }

  if (scene.camera.zoom > 2.f) {
    scene.camera.zoom = 2.f;
  }

  if (scene.camera.zoom < 0.3f) {
    scene.camera.zoom = 0.3f;
  }
}

void handle_input() {
  Vector2 direction = {0, 0};
  if (IsKeyDown(KEY_W)) {
    direction.y -= 1;
  }
  if (IsKeyDown(KEY_A)) {
    direction.x -= 1;
  }
  if (IsKeyDown(KEY_S)) {
    direction.y += 1;
  }
  if (IsKeyDown(KEY_D)) {
    direction.x += 1;
  }
  if (IsKeyDown(KEY_Q)) {
    --scene.camera.rotation;
  }
  if (IsKeyDown(KEY_E)) {
    ++scene.camera.rotation;
  }
  if (IsKeyDown(KEY_R)) {
    scene.camera.zoom = 1.f;
    scene.camera.rotation = 0.f;
    scene.is_camera_moved = false;
  }

  if (Vector2Length(direction) != 0) {
    direction = Vector2Normalize(direction);
  }

  scene.player.direction = direction;

  float scroll_whell_value = GetMouseWheelMove();
  scene.camera.zoom =
      expf(logf(scene.camera.zoom) + (scroll_whell_value * 0.1));

  scene.cursor_position = GetMousePosition();

  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse_delta = GetMouseDelta();
    if (Vector2Length(mouse_delta) != 0) {
      scene.is_camera_moved = true;
      mouse_delta = Vector2Scale(mouse_delta, -1.f / scene.camera.zoom);
      scene.camera.target = Vector2Add(scene.camera.target, mouse_delta);
    }
  }
}

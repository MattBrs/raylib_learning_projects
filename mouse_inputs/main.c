#include <raylib.h>
#include <raymath.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720

typedef struct Circle {
  Color color;
  float radius;
  Vector2 position;
} Circle;

typedef struct Player {
  Circle body;
  float movement_speed;
  Vector2 movement_direction;
} Player;

typedef struct Scene {
  Player player;

} Scene;

static Scene scene;

void init();
void draw();
void process();
void handle_input();

int main(int argc, char *argv[]) {
  init();
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Mouse inputs");
  SetConfigFlags(FLAG_VSYNC_HINT);
  // SetTargetFPS(60);

  while (!WindowShouldClose()) {
    handle_input();
    process();
    draw();
  }

  CloseWindow();

  return 0;
}

void init() {
  scene.player.body.position =
      (Vector2){(float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGTH / 2.f};
  scene.player.body.radius = 40.f;
  scene.player.body.color = BROWN;

  scene.player.movement_direction = (Vector2){0, 0};
  scene.player.movement_speed = 400.f;
}

void draw() {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawCircleV(scene.player.body.position, scene.player.body.radius,
              scene.player.body.color);

  EndDrawing();
}

void process() {
  float frametime = GetFrameTime();
  float player_x_velocity = scene.player.movement_direction.x *
                            scene.player.movement_speed * frametime;
  float player_y_velocity = scene.player.movement_direction.y *
                            scene.player.movement_speed * frametime;

  scene.player.body.position.x += player_x_velocity;
  scene.player.body.position.y += player_y_velocity;
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

  if (Vector2Length(direction) != 0) {
    direction = Vector2Normalize(direction);
  }

  scene.player.movement_direction = direction;
}

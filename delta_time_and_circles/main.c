#include <raylib.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720

struct Circle {
  Color color;
  float radius;
  Vector2 position;
};

struct Scene {
  struct Circle circle1;
  struct Circle circle2;
};

static int framerate;
static int speed;
static struct Scene scene;

void draw();
void init_scene();
void process();

int main(int argc, char *argv[]) {

  init_scene();
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "playing with delta time");
  SetTargetFPS(framerate);

  while (!WindowShouldClose()) {
    process();
    draw();
  }

  CloseWindow();
  return 0;
}

void init_scene() {
  speed = 20.f;
  framerate = 60;
  scene.circle1.color = RED;
  scene.circle1.radius = 60.f;
  scene.circle1.position = (Vector2){0, (float)WINDOW_HEIGTH / 3.f};

  scene.circle2.color = BLUE;
  scene.circle2.radius = 60.f;
  scene.circle2.position = (Vector2){0, (float)WINDOW_HEIGTH * 2.f / 3.f};
}

void draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawCircleV(scene.circle1.position, scene.circle1.radius,
              scene.circle1.color);
  DrawCircleV(scene.circle2.position, scene.circle2.radius,
              scene.circle2.color);

  const char *fps_text = 0;
  const char *frametime_text = 0;
  if (framerate == 0) {
    fps_text = TextFormat("FPS: unlimited (%i)", GetFPS());
  } else {
    fps_text = TextFormat("FPS: %i(%i)", framerate, GetFPS());
  }
  frametime_text = TextFormat("Frametime: %02.02f", GetFrameTime());

  DrawText(fps_text, 10, 10, 24, DARKBROWN);
  DrawText(frametime_text, 10, 50, 24, DARKBROWN);

  EndDrawing();
}

void process() {
  scene.circle1.position.x += GetFrameTime() * speed;
  scene.circle2.position.x += speed;

  int scroll_wheel_value = GetMouseWheelMove();
  if (scroll_wheel_value != 0) {
    framerate += (int)scroll_wheel_value;
    if (framerate < 0) {
      framerate = 0;
    }

    SetTargetFPS(framerate);
  }

  if (scene.circle1.position.x > WINDOW_WIDTH) {
    scene.circle1.position.x = 0;
  }

  if (scene.circle2.position.x > WINDOW_WIDTH) {
    scene.circle2.position.x = 0;
  }
}

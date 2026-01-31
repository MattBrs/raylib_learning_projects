#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define MAX_SPEED 100.f
#define CROUCH_SPEED 10.f
#define MAX_ACCEL 250.f
#define JUMP_FORCE 22.f

#define STAND_HEIGTH 1.5f
#define CROUCH_HEIGTH 0.5f
#define BOTTOM_HEIGTH 0.5f

#define MOUSE_SENSITIVITY 0.001f
#define CONTROLS_RESPONSIVITY 15.f

#define GRAVITY 64.f
#define FRICTION 0.9f
#define AIR_DRAG 0.95f

typedef struct {
  Vector3 position;
  Vector3 velocity;
  Vector3 direction;
  bool is_grounded;
  float movement_speed;

  Vector2 lean;
  Vector2 look_rotation;
} Player;

typedef struct {
  Vector2 mouse_delta;
  char sideway_movement;
  char straight_movement;
  bool crouch;
  bool jump;
} InputState;

static Player player = {0};
static float head_timer = 0.f;
static float walk_lerp = 0.f;
static float head_lerp = STAND_HEIGTH;
static InputState input_state = {0};

static void draw_level(Camera3D *camera);
static void update_player();
static void update_input_state();
static void update_camera_fps(Camera3D *camera);

int main(int argc, char *argv[]) {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(1280, 720, "FPS camera");
  SetTargetFPS(61);
  DisableCursor();

  Camera3D camera;
  camera.projection = CAMERA_PERSPECTIVE;
  camera.up = (Vector3){0.f, 1.f, 0.f};
  camera.fovy = 60.f;

  player.movement_speed = 100.f;
  player.position = (Vector3){0.f, 0.f, 0.f};
  camera.position = (Vector3){player.position.x,
                              player.position.y + BOTTOM_HEIGTH + head_lerp,
                              player.position.z};

  player.look_rotation = (Vector2){0.f, 0.f};

  update_camera_fps(&camera);

  while (!WindowShouldClose()) {
    float frametime = GetFrameTime();
    update_input_state();
    update_player();

    head_lerp =
        Lerp(head_lerp, (!input_state.crouch ? STAND_HEIGTH : CROUCH_HEIGTH),
             20.f * frametime);
    player.look_rotation.x -= input_state.mouse_delta.x * MOUSE_SENSITIVITY;
    player.look_rotation.y += input_state.mouse_delta.y * MOUSE_SENSITIVITY;

    camera.position = (Vector3){player.position.x,
                                player.position.y + BOTTOM_HEIGTH + head_lerp,
                                player.position.z};

    if (player.is_grounded && input_state.sideway_movement != 0 ||
        input_state.straight_movement != 0) {
      head_timer += frametime * 3.f;
      walk_lerp = Lerp(walk_lerp, 1.f, 10.f * frametime);
    } else {
      walk_lerp = Lerp(walk_lerp, 0.f, 10.f * frametime);
    }

    update_camera_fps(&camera);

    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);
    DrawPlane((Vector3){0.f, 0.f, 0.f}, (Vector2){100.f, 100.f}, BROWN);
    DrawGrid(10, 10);
    EndMode3D();

    DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2, 4, 4, WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void update_player() {
  float frametime = GetFrameTime();
  Vector2 movement_input = {input_state.sideway_movement,
                            input_state.straight_movement};

  if (Vector2Length(movement_input) != 0) {
    movement_input = Vector2Normalize(movement_input);
  }

  if (!player.is_grounded) {
    player.velocity.y -= GRAVITY * frametime;
  }

  if (player.is_grounded && input_state.jump) {
    player.velocity.y = JUMP_FORCE;
    player.is_grounded = false;
  }

  float rot = player.look_rotation.x;
  Vector3 front = {sinf(rot), 0.f, cosf(rot)};
  Vector3 right = {cosf(-rot), 0.f, sinf(-rot)};

  Vector3 target_direction = {
      movement_input.x * right.x + movement_input.y * front.x, 0.f,
      movement_input.x * right.z + movement_input.y * front.z};
  // player.direction = target_direction;
  player.direction = Vector3Lerp(player.direction, target_direction,
                                 CONTROLS_RESPONSIVITY * frametime);

  float deceleration = player.is_grounded ? FRICTION : AIR_DRAG;
  Vector3 target_velocity = {player.velocity.x * deceleration, 0.f,
                             player.velocity.z * deceleration};

  if (Vector3Length(target_velocity) < (MAX_SPEED * 0.01f)) {
    target_velocity = (Vector3){0};
  }

  float speed = Vector3DotProduct(target_velocity, player.direction);
  float max_speed = input_state.crouch ? CROUCH_SPEED : MAX_SPEED;
  float acceleration = Clamp(max_speed - speed, 0.f, MAX_ACCEL * frametime);

  target_velocity.x += player.direction.x * acceleration;
  target_velocity.z += player.direction.z * acceleration;

  player.velocity.x = target_velocity.x;
  player.velocity.z = target_velocity.z;

  player.position.x += player.velocity.x * frametime;
  player.position.y += player.velocity.y * frametime;
  player.position.z += player.velocity.z * frametime;

  if (player.position.y <= 0.f) {
    player.position.y = 0.f;
    player.velocity.y = 0.f;
    player.is_grounded = true;
  }
}

void update_input_state() {
  input_state.sideway_movement = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
  input_state.straight_movement = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
  input_state.crouch = IsKeyDown(KEY_LEFT_CONTROL);
  input_state.jump = IsKeyDown(KEY_SPACE);

  input_state.mouse_delta = GetMouseDelta();
}

void draw_level(Camera3D *camera) {}

void update_camera_fps(Camera3D *camera) {
  const Vector3 up = {0.f, 1.f, 0.f};
  const Vector3 target_offset = {0.f, 0.f, -1.f};
  Vector3 yaw =
      Vector3RotateByAxisAngle(target_offset, up, player.look_rotation.x);

  float max_angle_up = Vector3Angle(up, yaw);
  max_angle_up -= 0.001f;
  if (-(player.look_rotation.y) > max_angle_up) {
    player.look_rotation.y = -max_angle_up;
  }

  float max_angle_down = Vector3Angle(Vector3Negate(up), yaw);
  max_angle_down *= -1.f;
  max_angle_down += 0.001f;
  if (-(player.look_rotation.y) < max_angle_down) {
    player.look_rotation.y = -max_angle_down;
  }

  Vector3 right = Vector3Normalize(Vector3CrossProduct(yaw, up));
  float pitch_angle = -player.look_rotation.y - player.lean.y;
  pitch_angle = Clamp(pitch_angle, -PI / 2 + 0.0001f, +PI / 2 - 0.0001f);
  Vector3 pitch = Vector3RotateByAxisAngle(yaw, right, pitch_angle);

  float head_sin = sinf(head_timer * PI);
  float head_cos = cosf(head_timer * PI);
  const float step_rotation = 0.01f;

  camera->up = Vector3RotateByAxisAngle(
      up, pitch, head_sin * step_rotation + player.lean.x);

  const float bob_side = 0.1f;
  const float bob_up = 0.15f;
  Vector3 bobbing = Vector3Scale(right, head_sin * bob_side);

  bobbing.y = fabsf(head_cos * bob_up);

  camera->position =
      Vector3Add(camera->position, Vector3Scale(bobbing, walk_lerp));
  camera->target = Vector3Add(camera->position, pitch);
}

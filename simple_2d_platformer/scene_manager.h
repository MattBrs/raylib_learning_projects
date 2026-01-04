#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "shared_types.h"
typedef void (*RequestSceneCb)(void *context, int scene_id);

typedef struct {
  int id;
  void *data;
  void (*process)(void *data, void *context, InputState *input_state,
                  RequestSceneCb request_change);
  void (*draw)(void *data);
  void (*unload)(void *data);
} Scene;

typedef struct {
  Scene scene;
  int pending_scene;
} SceneManager;

void scene_manager_process(SceneManager *scene_mng, InputState *input_state);
void scene_manager_draw(SceneManager *scene_mng);
void scene_manager_load(SceneManager *scene_mng, int scene_id);
void scene_manager_request_scene(void *scene_mng, int scene_id);

#endif // !SCENE_MANAGER_H

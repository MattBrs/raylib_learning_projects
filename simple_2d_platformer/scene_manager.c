#include "scene_manager.h"
#include "scenes/scene1.h"
#include "scenes/scene2.h"
#include <stdio.h>
#include <stdlib.h>

void scene_manager_load(SceneManager *sc, int scene_id) {
  if (sc->scene.data != NULL) {
    sc->scene.unload(sc->scene.data);
  }

  switch (scene_id) {
  case 0x00:
    // dont load anything, closing game
    break;
  case 0x01: {
    sc->scene.id = 0x01;
    sc->scene.data = scene1_load();
    sc->scene.process = scene1_process;
    sc->scene.draw = scene1_draw;
    sc->scene.unload = scene1_unload;

    sc->pending_scene = -1;
    break;
  }
  case 0x02: {
    sc->scene.id = 0x02;
    sc->scene.data = scene2_load();
    sc->scene.process = scene2_process;
    sc->scene.draw = scene2_draw;
    sc->scene.unload = scene2_unload;

    sc->pending_scene = -1;
    break;
  }
  default:
    printf("scene not found!\n");
    exit(1);
  }
}

void scene_manager_draw(SceneManager *sc) {
  if (sc->scene.data != NULL && sc->scene.draw != NULL) {
    sc->scene.draw(sc->scene.data);
  }
}

void scene_manager_process(SceneManager *sc, InputState *input_state) {
  if (sc->scene.data != NULL && sc->scene.process != NULL) {
    sc->scene.process(sc->scene.data, sc, input_state,
                      scene_manager_request_scene);
  }
}

void scene_manager_request_scene(void *scene_mng, int scene_id) {
  SceneManager *mng = (SceneManager *)scene_mng;
  mng->pending_scene = scene_id;
}

#ifndef MAIN_H
#define MAIN_H

#include "scene_manager.h"
#include "shared_types.h"
#include <raylib.h>

#define SCREEN_DEFAULT_WIDTH 1280
#define SCREEN_DEFAULT_HEIGTH 720

int main(int argc, char *argv[]);
void draw(SceneManager *scene_manager);
InputState handle_input();

#endif

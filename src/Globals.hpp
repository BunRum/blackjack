#pragma once
#include <SDL3/SDL.h>
#include "Classes/Entity.hpp"
#include "Classes/Model.hpp"
#include <vector>

extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern float ResX;
extern float ResY;
extern float CenterX;
extern float CenterY;
extern bool MouseDown;
extern Entity* player;
extern Model* testModel;
extern std::vector<Object*> GameObjects;
extern double lastTime;
extern double deltaTime;

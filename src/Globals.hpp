// Globals.hpp
#pragma once
#include <vector>
#include <SDL3/SDL.h>

// forward declarations instead of includes
class Entity;
class Model;
class Object;
class PhysicsObject;

// global variables
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
extern double Seconds, Miliseconds;
extern double deltaTime;

extern float Gravity;
extern float Friction;
extern float TimeScale;

#include "Globals.hpp"
// define the globals
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;

float ResX = 1920.0f;
float ResY = 1080.0f;

float CenterX = ResX/2.0f;
float CenterY = ResY/2.0f;
bool MouseDown = false;
Entity* player = new Entity();
Model* testModel = new Model();
std::vector<Object*> GameObjects;
double lastTime = 0.0;
double deltaTime = SDL_GetTicks() / 1000.0;
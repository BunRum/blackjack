#include "Globals.hpp"
#include <Classes/Entity.hpp>
#include <Classes/Model.hpp>
#include <Classes/Object.hpp>
#include <Classes/PhysicsObject.hpp>
// define the globals
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;

float ResX = 1920.0f;
float ResY = 1080.0f;

float CenterX = ResX / 2.0f;
float CenterY = ResY / 2.0f;
bool MouseDown = false;
Entity* player = new Entity();
Model* testModel = new Model({0, 5000, 0, 0});
std::vector<Object*> GameObjects;
double lastTime = 0.0;
double Seconds, Miliseconds;
double deltaTime = SDL_GetTicks() / 1000.0;

float Gravity = 1000.0f; // default gravity value
float Friction = 0.9f; // default friction value
float TimeScale = 1.0f; // default time scale value
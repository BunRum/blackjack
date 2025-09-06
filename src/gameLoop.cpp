#include <format>
#include <string>

#include "Globals.hpp"
using namespace std;

void render() {
	SDL_RenderPresent(renderer);
}

void update() {
	double Seconds = SDL_GetTicks() / 1000.0; /* convert from milliseconds to seconds. */
	double Miliseconds = SDL_GetTicks();

	deltaTime = Seconds - lastTime;
	lastTime = Seconds;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); /* black, full alpha */
	SDL_RenderClear(renderer);									 /* start with a blank canvas. */

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); /* white, full alpha */

	string message = "super mario farted\nwoah awesome!";

	SDL_RenderDebugText(renderer, CenterX - 8 * message.size() / 2, CenterY, message.c_str());

	SDL_RenderDebugText(renderer, 0, 0, format("Ticks: {}", Miliseconds).c_str());

	SDL_RenderDebugText(renderer, 0, 10, format("Seconds: {}", Seconds).c_str());
	SDL_RenderDebugText(renderer, 0, 20, format("deltaTime: {}", deltaTime).c_str());

	SDL_RenderDebugText(renderer, 0, 30, format("PlayerX: {}", player->getX()).c_str());
	SDL_RenderDebugText(renderer, 0, 40, format("PlayerY: {}", player->getY()).c_str());
	SDL_RenderDebugText(renderer, 0, 50, format("VelocityX: {}", player->VelocityX).c_str());
	SDL_RenderDebugText(renderer, 0, 60, format("VelocityY: {}", player->VelocityY).c_str());
	SDL_RenderDebugText(renderer, 0, 70, format("Jumped: {}", player->Jumped).c_str());

	if (MouseDown) {
		float mouseX, mouseY;  // Use float for coordinates in SDL3
		SDL_GetMouseState(&mouseX, &mouseY);

		PhysicsObject* obj = new PhysicsObject();
		obj->setX(mouseX);
		obj->setY(mouseY);
		testModel->addChild(obj);
	}

	const bool* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		player->VelocityX = -500.0f;
	}
	if (state[SDL_SCANCODE_D]) {
		player->VelocityX = 500.0f;
	}
	if (state[SDL_SCANCODE_W]) {
		player->Jump();
	}

	// 1️⃣ Move children of models first
	for (auto* obj : GameObjects) {
		if (auto* model = dynamic_cast<Model*>(obj)) {
			model->updateChildrenPositions();
		}
	}

	// 2️⃣ Update physics of all non-Model objects
	for (auto* obj : GameObjects) {
		if (dynamic_cast<Model*>(obj)) continue;  // skip models here
		if (auto* physObj = dynamic_cast<PhysicsObject*>(obj)) {
			physObj->updatePhysics(deltaTime);	// children notify parent if they hit floor
		}
	}

	// 3️⃣ Update physics of all Models
	for (auto* obj : GameObjects) {
		if (auto* model = dynamic_cast<Model*>(obj)) {
			model->updatePhysics(deltaTime);
		}
	}

	// Render all objects
	for (auto* obj : GameObjects) {
		auto* physObj = dynamic_cast<PhysicsObject*>(obj);
		if (physObj) {
			SDL_RenderRect(renderer, &physObj->rect);
			SDL_RenderDebugText(renderer, physObj->getX(), physObj->getY() - 10, format("VX: {}, VY: {}", physObj->VelocityX, physObj->VelocityY).c_str());
		}
	}
}
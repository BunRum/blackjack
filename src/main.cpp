#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <format>
#include <iostream>

#include "Globals.hpp"
#include "gameLoop.hpp"

using namespace std;

// ----------------------
// SDL App Init
// ----------------------
/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", ResX, ResY, 0, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE; /* carry on with the program! */
}

// ----------------------
// SDL App Event Handling
// ----------------------
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	switch (event->type) {
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		MouseDown = true;
		break;

	case SDL_EVENT_MOUSE_BUTTON_UP:
		MouseDown = false;
		break;
	case SDL_EVENT_KEY_DOWN:
		switch (event->key.key) {
		case SDLK_R:
			player->setX(CenterX - 25.0f);
			player->setY(CenterY - 25.0f);
			player->VelocityX = 0.0f;
			player->VelocityY = 0.0f;
			break;

		case SDLK_F:
			testModel->Anchored = false;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return SDL_APP_CONTINUE;
}

// ----------------------
// SDL App Iteration (per frame)
// ----------------------
SDL_AppResult SDL_AppIterate(void* appstate) {
	update();  // from gameLoop.cpp

	// double Seconds = SDL_GetTicks() / 1000.0; /* convert from milliseconds to seconds. */
	// double Miliseconds = SDL_GetTicks();

	// deltaTime = Seconds - lastTime;
	// lastTime = Seconds;

	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); /* black, full alpha */
	// SDL_RenderClear(renderer);									 /* start with a blank canvas. */

	// SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); /* white, full alpha */

	// string message = "super mario farted\nwoah awesome!";

	// SDL_RenderDebugText(renderer, CenterX - 8 * message.size() / 2, CenterY, message.c_str());

	// SDL_RenderDebugText(renderer, 0, 0, format("Ticks: {}", Miliseconds).c_str());

	// SDL_RenderDebugText(renderer, 0, 10, format("Seconds: {}", Seconds).c_str());
	// SDL_RenderDebugText(renderer, 0, 20, format("deltaTime: {}", deltaTime).c_str());

	// SDL_RenderDebugText(renderer, 0, 30, format("PlayerX: {}", player->getX()).c_str());
	// SDL_RenderDebugText(renderer, 0, 40, format("PlayerY: {}", player->getY()).c_str());
	// SDL_RenderDebugText(renderer, 0, 50, format("VelocityX: {}", player->VelocityX).c_str());
	// SDL_RenderDebugText(renderer, 0, 60, format("VelocityY: {}", player->VelocityY).c_str());

	render();  // from gameLoop.cpp

	return SDL_APP_CONTINUE;
}

// ----------------------
// SDL App Quit
// ----------------------
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	// SDL will clean up window and renderer automatically
}

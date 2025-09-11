#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <Classes/Entity.hpp>
#include <Classes/Model.hpp>
#include <Classes/PhysicsObject.hpp>
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

	PhysicsObject* obstacle = new PhysicsObject({CenterX - 150, CenterY, 300, 300});
	PhysicsObject* obstacle2 = new PhysicsObject({CenterX - 200, CenterY + 300, 1920, 50});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(1);
	style.FontScaleDpi = 1.0f;
	// style

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	return SDL_APP_CONTINUE; /* carry on with the program! */
}

// ----------------------
// SDL App Event Handling
// ----------------------
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	ImGui_ImplSDL3_ProcessEvent(event);	 // Pass events to ImGui
	ImGuiIO& io = ImGui::GetIO();

	// If ImGui wants keyboard/mouse input, skip game logic
	if (io.WantCaptureKeyboard || io.WantCaptureMouse) {
		return SDL_APP_CONTINUE;
	}
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
		}
		break;
	}
	return SDL_APP_CONTINUE;
}

// ----------------------
// SDL App Iteration (per frame)
// ----------------------
SDL_AppResult SDL_AppIterate(void* appstate) {


	update();  // from gameLoop.cpp


	
	render();  // from gameLoop.cpp

	return SDL_APP_CONTINUE;
}

// ----------------------
// SDL App Quit
// ----------------------
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	// SDL will clean up window and renderer automatically
}

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <Classes/Entity.hpp>
#include <Classes/Model.hpp>
#include <Classes/PhysicsObject.hpp>
#include <format>
#include <string>

#include "DrawRequest.hpp"
#include "Globals.hpp"

using namespace std;

std::vector<DrawRequest> renderStack;
std::vector<int> lastColor = {255, 255, 255, 255};	// white with full alpha

void physicsLoop() {
	//  Update physics of all Models
	for (auto* obj : GameObjects) {
		if (auto* model = dynamic_cast<Model*>(obj)) {
			model->updateChildrenPositions();
			model->updatePhysics(deltaTime);
		}
	}
	// Update physics of all non-Model objects
	for (auto* obj : GameObjects) {
		if (dynamic_cast<Model*>(obj)) continue;  // skip models here
		if (auto* physObj = dynamic_cast<PhysicsObject*>(obj)) {
			physObj->updatePhysics(deltaTime);	// children notify parent if they hit floor
		}
	}
}

PhysicsObject* hoveredObject = nullptr;

void ImGuiLoop() {
	// Start ImGui frame
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	static PhysicsObject* selectedObject = nullptr;
	static float friction = 0.9f;
	static float timeScale = 1.0f;
	static bool showPhysicsBoxes = true;
	static bool showVelocityVectors = true;
	static bool showGrid = false;
	static float spawnX = 100, spawnY = 100, spawnW = 50, spawnH = 50;

	hoveredObject = nullptr;  // reset each frame

	// ------------------------------
	// GameObjects List Window
	// ------------------------------
	ImGui::Begin("Game Objects");
	for (size_t i = 0; i < GameObjects.size(); ++i) {
		auto* obj = GameObjects[i];
		if (!obj) continue;

		std::string label = "Object " + std::to_string(i) + " (" + obj->className + ")";
		if (ImGui::TreeNode(label.c_str())) {
			if (auto* phys = dynamic_cast<PhysicsObject*>(obj)) {
				ImGui::Text("Position: (%.1f, %.1f)", phys->getX(), phys->getY());
				ImGui::Text("Size: (%.1f x %.1f)", phys->Width, phys->Height);
				ImGui::Text("Velocity: (%.1f, %.1f)", phys->VelocityX, phys->VelocityY);
				ImGui::Text("Anchored: %s", phys->Anchored ? "Yes" : "No");
				ImGui::Text("Falling: %s", phys->isFalling ? "Yes" : "No");
			}
			ImGui::TreePop();
		}

		// Hover logic
		if (ImGui::IsItemHovered()) {
			if (auto* phys = dynamic_cast<PhysicsObject*>(obj)) {
				hoveredObject = phys;
			}
		}

		// Select on click
		if (ImGui::IsItemClicked()) {
			if (auto* phys = dynamic_cast<PhysicsObject*>(obj)) {
				selectedObject = phys;
			}
		}
	}
	ImGui::End();

	// ------------------------------
	// Object Inspector Window
	// ------------------------------
	ImGui::Begin("Object Inspector");
	if (selectedObject) {
		ImGui::Text("Class: %s", selectedObject->className.c_str());
		ImGui::DragFloat("X", &selectedObject->X, 1.0f);
		ImGui::DragFloat("Y", &selectedObject->Y, 1.0f);
		ImGui::DragFloat("Width", &selectedObject->Width, 1.0f);
		ImGui::DragFloat("Height", &selectedObject->Height, 1.0f);
		ImGui::DragFloat("VelocityX", &selectedObject->VelocityX, 1.0f);
		ImGui::DragFloat("VelocityY", &selectedObject->VelocityY, 1.0f);
		ImGui::Checkbox("Anchored", &selectedObject->Anchored);
		ImGui::Checkbox("Falling", &selectedObject->isFalling);
		if (selectedObject->className == "Entity") {
			auto* entity = static_cast<Entity*>(selectedObject);
			ImGui::DragFloat("Walk Speed", &entity->walkSpeed, 10.0f);
			ImGui::DragFloat("Jump Power", &entity->jumpPower, 10.0f);
			ImGui::Checkbox("Jumped", &entity->Jumped);
		}
	}
	ImGui::End();

	// ------------------------------
	// Physics Controls Window
	// ------------------------------
	ImGui::Begin("Physics Controls");
	ImGui::SliderFloat("Gravity", &Gravity, -2000.0f, 2000.0f);
	ImGui::SliderFloat("Friction", &friction, 0.0f, 1.0f);
	ImGui::SliderFloat("Time Scale", &timeScale, 0.1f, 3.0f);
	ImGui::End();

	// ------------------------------
	// Render Debug Window
	// ------------------------------
	ImGui::Begin("Render Debug");
	ImGui::Checkbox("Show Physics Boxes", &showPhysicsBoxes);
	ImGui::Checkbox("Show Velocity Vectors", &showVelocityVectors);
	ImGui::Checkbox("Show Grid", &showGrid);
	ImGui::End();

	// ------------------------------
	// Object Spawner Window
	// ------------------------------
	ImGui::Begin("Spawner");
	ImGui::DragFloat("X", &spawnX);
	ImGui::DragFloat("Y", &spawnY);
	ImGui::DragFloat("Width", &spawnW);
	ImGui::DragFloat("Height", &spawnH);
	if (ImGui::Button("Spawn PhysicsObject")) {
		auto* obj = new PhysicsObject(spawnX, spawnY, spawnW, spawnH, false);
		GameObjects.push_back(obj);
	}
	ImGui::End();

	// ------------------------------
	// Stats Window
	// ------------------------------
	ImGui::Begin("Stats");
	ImGui::Text("FPS: %.1f", 1.0f / deltaTime);
	ImGui::Text("GameObjects: %zu", GameObjects.size());
	ImGui::Text("Hovered: %s", hoveredObject ? hoveredObject->className.c_str() : "None");
	ImGui::End();

	// ------------------------------
	// Cheats / Utility Window
	// ------------------------------
	ImGui::Begin("Cheats");
	if (ImGui::Button("Reset Player")) {
		player->setX(CenterX - 25.0f);
		player->setY(CenterY - 25.0f);
		player->VelocityX = 0;
		player->VelocityY = 0;
	}
	if (ImGui::Button("Toggle Gravity")) {
		Gravity = (Gravity != 0 ? 0 : 500.0f);
	}
	ImGui::End();

	// Render ImGui
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void UILoop() {
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
}

void InputLoop() {
	if (MouseDown) {
		float mouseX, mouseY;  // Use float for coordinates in SDL3
		SDL_GetMouseState(&mouseX, &mouseY);

		// PhysicsObject* obj = new PhysicsObject(mouseX, mouseY, 50, 50, false);
	}

	const bool* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A]) {
		player->VelocityX = -player->walkSpeed;
	}
	if (state[SDL_SCANCODE_D]) {
		player->VelocityX = player->walkSpeed;
	}
	if (state[SDL_SCANCODE_W]) {
		player->Jump();
	}
}

void render() {
	renderStack.clear();

	for (auto* obj : GameObjects) {
		if (auto* physObj = dynamic_cast<PhysicsObject*>(obj)) {
			renderStack.push_back(physObj->Draw());
		}
	}

	// Highlight hovered object in the game
	if (hoveredObject) {
		DrawRequest highlight{
			1000,  // high z-index to render on top
			"Rect",
			{hoveredObject->getX(), hoveredObject->getY(),
			 hoveredObject->Width, hoveredObject->Height},
			{255, 0, 0, 255}  // red
		};
		renderStack.push_back(highlight);
	}

	if (!renderStack.empty()) {
		auto lowestIndex = min_element(
			renderStack.begin(), renderStack.end(),
			[](const DrawRequest& a, const DrawRequest& b) {
				return a.zIndex < b.zIndex;
			});

		auto highestIndex = max_element(
			renderStack.begin(), renderStack.end(),
			[](const DrawRequest& a, const DrawRequest& b) {
				return a.zIndex < b.zIndex;
			});

		for (int i = lowestIndex->zIndex; i <= highestIndex->zIndex; i++) {
			for (const auto& request : renderStack) {
				if (request.zIndex == i) {
					SDL_SetRenderDrawColor(renderer,
										   request.color[0], request.color[1],
										   request.color[2], request.color[3]);

					if (request.type == "Line") {
						SDL_RenderLine(renderer,
									   request.params[0], request.params[1],
									   request.params[2], request.params[3]);
					} else if (request.type == "Rect") {
						SDL_FRect r{request.params[0], request.params[1],
									request.params[2], request.params[3]};
						SDL_RenderRect(renderer, &r);
					}

					SDL_SetRenderDrawColor(renderer,
										   lastColor[0], lastColor[1],
										   lastColor[2], lastColor[3]);
				}
			}
		}
	}

	UILoop();
	ImGuiLoop();

	SDL_RenderPresent(renderer);
}

void update() {
	Seconds = SDL_GetTicks() / 1000.0; /* convert from milliseconds to seconds. */
	Miliseconds = SDL_GetTicks();
	deltaTime = Seconds - lastTime;
	lastTime = Seconds;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); /* black, full alpha */
	SDL_RenderClear(renderer);									 /* start with a blank canvas. */

	physicsLoop();
	InputLoop();
}
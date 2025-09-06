#include "PhysicsObject.hpp"

#include <Globals.hpp>
#include <cmath>
#include <vector>

#include "Model.hpp"

PhysicsObject::PhysicsObject() {
	GameObjects.push_back(this);
	className = "PhysicsObject";
}

float PhysicsObject::getX() const { return rect.x; }
float PhysicsObject::getY() const { return rect.y; }
void PhysicsObject::setX(float newX) { rect.x = newX; }
void PhysicsObject::setY(float newY) { rect.y = newY; }

void PhysicsObject::onGroundHit() {
	if (hasParent) {
		SDL_Log("PhysicsObject with parent hit the ground, notifying parent.");
		if (auto* parentModel = dynamic_cast<Model*>(Parent)) {
			parentModel->onGroundHit();
		}
	} else {
		// SDL_Log("PhysicsObject without parent hit the ground.");
		VelocityY = 0;
        setY(lastY);
	}
}

void PhysicsObject::updatePhysics(double deltaTime) {
	//  Move by current velocity
	lastX = getX();
	lastY = getY();
	setX(getX() + VelocityX * static_cast<float>(deltaTime));
	setY(getY() - VelocityY * static_cast<float>(deltaTime));

	//  Compute new velocity
	if (!Anchored) {
		VelocityY -= 500.0f * static_cast<float>(deltaTime);  // gravity
		VelocityX *= pow(0.9f, deltaTime * 60.0f);			  // friction
		isFalling = VelocityY < 0;
	}

	float newX = getX() + VelocityX * static_cast<float>(deltaTime);
	float newY = getY() - VelocityY * static_cast<float>(deltaTime);

	//  Detect collisions
	if (newY > ResY - rect.h) {
		//  Reset position/velocity
		if (hasParent) {
			auto* parentModel = dynamic_cast<Model*>(Parent);
			parentModel->onGroundHit();
		} else {
			VelocityY = 0;
			setY(ResY - rect.h);
			onGroundHit();
		}
	} else {
		setX(newX);
		setY(newY);
	}
}

#include "PhysicsObject.hpp"

#include <Globals.hpp>
#include <cmath>
#include <format>
#include <gameLoop.hpp>
#include <vector>

#include "Model.hpp"

void PhysicsObject::onGroundHit() {
	if (hasParent) {
		if (auto* parentModel = dynamic_cast<Model*>(Parent)) {
			parentModel->onGroundHit();
			parentModel->updateChildrenPositions();
		}
	} else {
		// SDL_Log("PhysicsObject without parent hit the ground.");
		VelocityY = 0;
		setY(lastY);
	}
}

void PhysicsObject::checkCollisions() {
	float thisTop = getY();
	float thisBottom = getY() + Height;
	float thisLeft = getX();
	float thisRight = getX() + Width;

	for (auto* _obj : GameObjects) {
		if (_obj == this) continue;
		if (auto* other = dynamic_cast<PhysicsObject*>(_obj)) {
			float otherTop = other->getY();
			float otherBottom = other->getY() + other->Height;
			float otherLeft = other->getX();
			float otherRight = other->getX() + other->Width;
			const float epsilon = 0.0f;
			// Expand the other object's bounds slightly to handle edge cases

			bool isNotColliding = (thisBottom <= otherTop + epsilon ||
								   thisTop >= otherBottom - epsilon ||
								   thisRight <= otherLeft + epsilon ||
								   thisLeft >= otherRight - epsilon);

			bool touchingTop = false, touchingBottom = false, touchingLeft = false, touchingRight = false;
			if (!isNotColliding) {
				// Collision detected, determine the side of collision
				float overlapX = (thisLeft < otherLeft) ? thisRight - otherLeft : thisLeft - otherRight;
				float overlapY = (thisTop < otherTop) ? thisBottom - otherTop : thisTop - otherBottom;
				if (std::abs(overlapX) < std::abs(overlapY)) {
					// Horizontal collision
					VelocityX = 0;
					setX(lastX);
					if (overlapX > 0) {
						touchingLeft = true;
					} else {
						touchingRight = true;
					}
				} else {
					// Vertical collision
					VelocityY = 0;
					setY(lastY);
					if (overlapY > 0) {
						touchingTop = true;
						onGroundHit();
					} else {
						touchingBottom = true;
					}
				}
			}
			auto Green = {0, 255, 0, 255};
			auto Red = {0, 0, 0, 0};
			renderStack.push_back(DrawRequest{1, "Line", {otherLeft, otherTop, otherRight, otherBottom}, touchingTop ? Green : Red});
		}
	}
}

void PhysicsObject::updatePhysics(double deltaTime) {
	float dt = static_cast<float>(deltaTime);

	// Save last position
	lastX = getX();
	lastY = getY();

	if (!Anchored) {
		// Apply forces
		VelocityY -= Gravity * dt;			 // gravity pulls down
		VelocityX *= pow(Friction, dt * 60.0f);	 // friction
		isFalling = VelocityY > 0;

		// Integrate position
		newX = lastX + (VelocityX * dt);
		newY = lastY - (VelocityY * dt);

		setX(newX);
		setY(newY);

		checkCollisions();
	}
}

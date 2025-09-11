#pragma once
#include "PhysicsObject.hpp"

class Entity : public PhysicsObject {
public:
	bool Jumped;
	float walkSpeed;
	float jumpPower;
	Entity(float X = 0, float Y = 0, float Width = 50, float Height = 50)
		: PhysicsObject(X, Y, Width, Height) {
		className = "Entity";
		Anchored = false;
		walkSpeed = 500.0f;
		jumpPower = 1000.0f;
	}
	void Jump();
	void onGroundHit() override;
};

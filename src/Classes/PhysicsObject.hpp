#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "../Globals.hpp"
#include "DrawRequest.hpp"
#include "Object.hpp"

class PhysicsObject : public Object {
public:
    float X, Y, Width, Height;

    float VelocityX = 0, VelocityY = 0;
    float lastX = 0, lastY = 0;
    float newX = 0, newY = 0;

    bool Anchored = true;
    bool isFalling = false;
    bool physicsEnabled = true;

    // Constructor with anchored option
    PhysicsObject(float x = 0, float y = 0, float width = 50, float height = 50, bool anchored = true)
        : X(x), Y(y), Width(width), Height(height), Anchored(anchored) {
        className = "PhysicsObject";
        GameObjects.push_back(this);
    }

    float getX() const { return X; }
    float getY() const { return Y; }
    float setX(float newX) { X = newX; return newX; }
    float setY(float newY) { Y = newY; return newY; }

    virtual void onGroundHit();
    void checkCollisions();
    void updatePhysics(double deltaTime);

    DrawRequest Draw() const {
        return DrawRequest{0, "Rect", {X, Y, Width, Height}, {255, 255, 255, 255}};
    }
};

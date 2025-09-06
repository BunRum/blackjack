#pragma once
#include "Object.hpp"
#include <SDL3/SDL.h>

class PhysicsObject : public Object {
public:
    SDL_FRect rect{};
    float VelocityX = 0, VelocityY = 0, lastX = 0, lastY = 0;
    bool Anchored = true, isFalling = false, physicsEnabled = true;

    PhysicsObject();
    float getX() const;
    float getY() const;
    void setX(float newX);
    void setY(float newY);
    virtual void onGroundHit();
    void updatePhysics(double deltaTime);
};

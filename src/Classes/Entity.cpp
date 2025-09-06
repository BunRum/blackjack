#include "Entity.hpp"
#include "PhysicsObject.hpp"
#include <vector>
#include <Globals.hpp>

Entity::Entity() {
    rect.x = 320 - 25;
    rect.y = 240 - 25;
    rect.w = 50;
    rect.h = 50;
    Anchored = false;
    GameObjects.push_back(this);
    className = "Entity";
}

void Entity::Jump() {
    if (!isFalling && !Jumped) {
        VelocityY = 300.0f;
        Jumped = true;
    } else {
        // SDL_Log("Jump not allowed: isFalling=%d, Jumped=%d", isFalling, Jumped);
    }
}

void Entity::onGroundHit() {
    PhysicsObject::onGroundHit();
    Jumped = false;
}

#include "Entity.hpp"
#include "PhysicsObject.hpp"
#include <vector>
#include <Globals.hpp>

void Entity::Jump() {
    if (isFalling == false && Jumped == false) {
        VelocityY = jumpPower;
        // Jumped = true;
    } else {
        // SDL_Log("Jump not allowed: isFalling=%d, Jumped=%d", isFalling, Jumped);
    }
}

void Entity::onGroundHit() {
    PhysicsObject::onGroundHit();
    Jumped = false;
}

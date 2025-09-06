#pragma once
#include "PhysicsObject.hpp"

class Entity : public PhysicsObject {
public:
    bool Jumped = false;
    Entity();
    void Jump();
    void onGroundHit() override;
};

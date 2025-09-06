#pragma once
#include "PhysicsObject.hpp"
#include <map>

class Model : public PhysicsObject {
public:
    map<PhysicsObject*, SDL_FPoint> ChildOffsets;

    Model();
    void addChild(PhysicsObject* child);
    void updateChildrenPositions();
};

#pragma once
#include "PhysicsObject.hpp"
#include <map>

class Model : public PhysicsObject {
public:
    map<PhysicsObject*, SDL_FPoint> ChildOffsets;

    Model(float X, float Y, float Width, float Height) : PhysicsObject(X, Y, Width, Height) {
        Anchored = true;
        className = "Model";
        physicsEnabled = true;
    };
    void addChild(PhysicsObject* child);
    void updateChildrenPositions();
};

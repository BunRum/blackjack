#include "Model.hpp"
#include "PhysicsObject.hpp"
#include <Globals.hpp>

Model::Model() {
    rect = {320 - 25, 240 - 25, 50, 50};
    Anchored = true;
    GameObjects.push_back(this);
    className = "Model";
    physicsEnabled = true;
}

void Model::addChild(PhysicsObject* child) {
    child->setParent(this);
    ChildOffsets[child] = {child->getX() - getX(), child->getY() - getY()};
}

void Model::updateChildrenPositions() {
    for (auto* obj : Children) {
        if (auto* phys = dynamic_cast<PhysicsObject*>(obj)) {
            auto offset = ChildOffsets[phys];
            phys->rect.x = rect.x + offset.x;
            phys->rect.y = rect.y + offset.y;
        }
    }
}

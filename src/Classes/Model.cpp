#include "Model.hpp"
#include "PhysicsObject.hpp"
#include <Globals.hpp>

void Model::addChild(PhysicsObject* child) {
    child->setParent(this);
    ChildOffsets[child] = {child->getX() - getX(), child->getY() - getY()};
}

void Model::updateChildrenPositions() {
    for (auto* obj : Children) {
        if (auto* phys = dynamic_cast<PhysicsObject*>(obj)) {
            auto offset = ChildOffsets[phys];
            phys->X = X + offset.x;
            phys->Y = Y + offset.y;
        }
    }
}

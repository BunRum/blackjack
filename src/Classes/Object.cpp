#include "Object.hpp"
#include <algorithm>

void Object::setParent(Object* obj) {
    if (Parent) {
        auto& siblings = Parent->Children;
        siblings.erase(remove(siblings.begin(), siblings.end(), this), siblings.end());
    }
    Parent = obj;
    if (Parent) {
        Parent->Children.push_back(this);
        hasParent = true;
    }
}

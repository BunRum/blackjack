#pragma once
#include <vector>
#include <string>
using namespace std;

class Object {
public:
    string className;
    Object* Parent = nullptr;
    bool hasParent = false;
    vector<Object*> Children = {};

    virtual ~Object() = default;

    virtual void setParent(Object* obj);
};

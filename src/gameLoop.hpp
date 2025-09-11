#include <Classes/DrawRequest.hpp>
#include <vector>
void update();
void render();
#pragma once

extern std::vector<DrawRequest> renderStack;
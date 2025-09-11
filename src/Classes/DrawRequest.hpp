#pragma once
#include <string>
#include <vector>

class DrawRequest {
public:
	int zIndex;
	std::string type;
	std::vector<float> params;
    std::vector<int> color; // RGBA color

	DrawRequest(int zIndex, const std::string& type, const std::vector<float>& params, const std::vector<int>& color)
		: zIndex(zIndex), type(type), params(params), color(color) {}
};
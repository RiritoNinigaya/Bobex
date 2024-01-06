#pragma once
#include <string>
#include "../Bobex/Includes.hpp"
auto HexToRGBA = [](const std::string& Hex) {
	int r, g, b;
	sscanf_s(Hex.c_str(), "%02x%02x%02x", &r, &g, &b);
	const ImVec4 color{ (static_cast<float>(r) / 255), (static_cast<float>(g) / 255), (static_cast<float>(b) / 255), 255 };
	return color;
};

#pragma once
#include "connectivity_type.hpp"
#include <string>

class ConnectivityLoader {
public:
	// Convert connectivity map from YAML to C++
	static ConnectivityMap loadFromFile(const std::string& filePath);
};

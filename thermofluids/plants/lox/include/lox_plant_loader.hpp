#pragma once
#include "lox_plant_params.hpp"
#include <string>

class LOxPlantLoader {
public:
	static LOxPlantParams load(const std::string& pipePath, const std::string& volumePath);
};

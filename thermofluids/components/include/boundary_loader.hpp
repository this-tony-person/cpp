#pragma once
#include "boundary_params.hpp"
#include <string>
#include <map>

class BoundaryLoader {
public: 
	static std::map<std::string, BoundaryParams> load(const std::string& filepath);
};

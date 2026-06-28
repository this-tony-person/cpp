#pragma once
#include "volume_params.hpp"
#include <string>
#include <map>

class VolumeLoader {
public:
	static std::map<std::string, VolumeParams> load(const std::string& filepath);
};



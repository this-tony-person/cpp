#pragma once
#include "../../../components/include/pipe_params.hpp"
#include "../../../components/include/volume_params.hpp"
#include <map>
#include <string>

struct LOxPlantParams {
	std::map<std::string, PipeParams> pipeRegistry;
	std::map<std::string, VolumeParams> volumeRegistry;
};

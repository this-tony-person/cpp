#include "../include/lox_plant_loader.hpp"
#include "../../../components/include/pipe_loader.hpp"
#include "../../../components/include/volume_loader.hpp"

LOxPlantParams LOxPlantLoader::load(const std::string& pipePath, const std::string& volumePath) {
	// Initialize plant registry
	LOxPlantParams params;
	
	// Append component registries
	params.pipeRegistry = PipeLoader::load(pipePath);
	params.volumeRegistry = VolumeLoader::load(volumePath);
	//params.boundaryRegistry = 
	
	return params;
};

#include "connectivity_loader.hpp"
#include <yaml-cpp/yaml.h>
#include <stdexcept>

// Convert connectivity map from YAML to C++
ConnectivityMap ConnectivityLoader::loadFromFile(const std::string& filePath) {
	ConnectivityMap map;
	
	// Load YAML connectivity file
	YAML::Node config = YAML::LoadFile(filePath);
	
	// Validate YAML file
	if (!config["connections"]) {
		throw std::runtime_error("Invalid YAML: Missing 'connections' root key.");
	}
	
	// For every component in plant
	for (auto it = config["connections"].begin(); it != config["connections"].end(); ++it) {
		std::string componentName = it->first.as<std::string>();
		auto ports = it->second;
		
		// For every port in component
		for (auto portIt = ports.begin(); portIt != ports.end(); ++portIt) {
			std::string portID = portIt->first.as<std::string>();
			auto targetNode = portIt->second;
			
			// Add connection data to C++ map
			map[componentName][portID] = {
				targetNode["name"].as<std::string>(),
				targetNode["port"].as<std::string>()
			};
		}
	} 
	
	// Return C++ connectivity map to caller
	return map;
}

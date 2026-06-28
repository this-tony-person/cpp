#include "volume_loader.hpp"
#include <fstream>
#include <sstream>

/**
 * @brief Utility class to create volumes registry from volumes parameterization file
 */

std::map<std::string, VolumeParams> VolumeLoader::load(const std::string& filepath) {
	// Create volume registry
	std::map<std::string, VolumeParams> registry;

	// Construct input file stream object
	std::ifstream file(filepath);

	// Read and ignore first (header) row
	std::string line;
	std::getline(file,line);
	
	// Read remaining (data) rows
	while (std::getline(file,line)) {
		// Construct string stream object 
		std::stringstream ss(line);
		std::string name, CHyd;
		
		// Extract fields separated by comma
		if (std::getline(ss,name,',') && std::getline(ss,CHyd)) {
			// Convert kLoss to double
			registry[name] = {std::stod(CHyd)};
		}
	}
	
return registry;
};

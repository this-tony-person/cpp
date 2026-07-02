#include "boundary_loader.hpp"
#include <fstream>
#include <sstream>

/**
 * @brief Utility class to create boundary registry from boundary parameterization file
 */

std::map<std::string, BoundaryParams> BoundaryLoader::load(const std::string& filepath) {
	// Create boundary registry
	std::map<std::string, BoundaryParams> registry;

	// Open CSV data file
	std::ifstream file(filepath);
	std::string line;

	// Read and ignore first row
	std::getline(file,line);
	
	// Read remaining rows
	while (std::getline(file,line)) {
		// Turn line into stream for parsing
		std::stringstream ss(line);
		std::string name, pressure;
		
		// Extract fields separated by comma
		if (std::getline(ss,name,',') && std::getline(ss,pressure)) {
			// Convert pressure to double
			registry[name] = {std::stod(pressure)};
		}
	}
	
return registry;
};

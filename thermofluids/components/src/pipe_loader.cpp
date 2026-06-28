#include "pipe_loader.hpp"
#include <fstream>
#include <sstream>

/**
 * @brief Utility class to create pipe registry from pipe parameterization file
 */

std::map<std::string, PipeParams> PipeLoader::load(const std::string& filepath) {
	// Create pipe registry
	std::map<std::string, PipeParams> registry;

	// Open CSV data file
	std::ifstream file(filepath);
	std::string line;

	// Read and ignore first row
	std::getline(file,line);
	
	// Read remaining rows
	while (std::getline(file,line)) {
		// Turn line into stream for parsing
		std::stringstream ss(line);
		std::string name, kLoss;
		
		// Extract fields separated by comma
		if (std::getline(ss,name,',') && std::getline(ss,kLoss)) {
			// Convert kLoss to double
			registry[name] = {std::stod(kLoss)};
		}
	}
	
return registry;
};

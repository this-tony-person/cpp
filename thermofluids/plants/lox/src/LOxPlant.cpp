#include "LOxPlant.hpp"
#include "../include/lox_plant_params.hpp"
#include "connectivity_loader.hpp"
#include <iostream>

// Constructor
LOxPlant::LOxPlant(const LOxPlantParams& params, const std::string& connectivityFilePath) {
    // 1. Convert PipeParams to active Pipe objects
    std::cout << "Loading pipes:" << std::endl;
    for (const auto& [name, p_params] : params.pipeRegistry) {
    	std::cout << " - " << name << std::endl;
    }
    
    for (const auto& [name, p_params] : params.pipeRegistry) {
        pipes.emplace(name, Pipe(p_params.KLoss));
    }

    // 2. Convert VolumeParams to active Volume objects
    std::cout << "Loading volumes:" << std::endl;
    for (const auto& [name, p_params] : params.volumeRegistry) {
    	std::cout << " - " << name << std::endl;
    }
    
    for (const auto& [name, v_params] : params.volumeRegistry) {
      volumes.emplace(name, CapacitiveVolume(v_params.CHyd));
    }
    
    // 3. Convert BoundaryParams to active Boundary objects
    std::cout << "Loading boundaries:" << std::endl;
    for (const auto& [name, b_params] : params.boundaryRegistry) {
    	std::cout << " - " << name << std::endl;
    }
    
    for (const auto& [name, b_params] : params.boundaryRegistry) {
      boundaries.emplace(name, BoundaryCondition(b_params.pressure));
    }
    
    // Initialize plant topology
		this->connectivity = ConnectivityLoader::loadFromFile(connectivityFilePath);
}

void LOxPlant::computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t) {
	// Update volume pressure states
	int i = 0;
	for (auto& [volName, volume] : volumes) {
		volume.pressure = x[i++];
	}
	
	// Compute state derivatives
	i = 0;
	for (auto& [volName,volume] : volumes) {
		double netMdot = 0.0;
		
		// Get volume neighbors
		auto& volNeighbors = connectivity.at(volName);
		
		for (auto& [portName,connection] : volNeighbors) {
			std::string pipeName = connection.name;
			auto& pipe = pipes.at(pipeName);
			
			// Get pressures at pipe terminals
			auto& pipeConns = connectivity.at(pipeName);
			double pA = getPressure(pipeConns.at("A").name);
			double pB = getPressure(pipeConns.at("B").name);
			
			// Compute raw mdot (A to B)
			double mdot = pipe.computeMassFlowRate(pA,pB);
			
			// Correct mdot sign
			if (connection.port == "A") {
				netMdot -= mdot; // Reverse flow
			} else {
				netMdot += mdot; // Positive flow
			}
		}
		
		// Update junction pressure state derivative
		dxdt[i++] = volume.computePressureStateDerivative(netMdot);
	}
}

// Get pressure state from capacitive volume or boundary condition component
double LOxPlant::getPressure(const std::string& name) const {
    if (volumes.count(name)) {
        return volumes.at(name).pressure;
    } 
    if (boundaries.count(name)) {
        return boundaries.at(name).pressure;
    }
    throw std::runtime_error("Component '" + name + "' not found in volumes or boundaries.");
}

// Get mass flow rate from pipe component
double LOxPlant::getPipeMdot(const std::string& pipeName, double p1, double p2) {
	return pipes.at(pipeName).computeMassFlowRate(p1,p2);
}

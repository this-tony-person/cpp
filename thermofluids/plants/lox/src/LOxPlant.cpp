#include "LOxPlant.hpp"
#include "../include/lox_plant_params.hpp"
#include "connectivity_loader.hpp"
#include <iostream>

// Constructor
LOxPlant::LOxPlant(const LOxPlantParams& params, const std::string& connectivityFilePath) {
    // 1. Convert PipeParams to active Pipe objects
    std::cout << "DEBUG: Pipes loaded:" << std::endl;
    for (const auto& [name, p_params] : params.pipeRegistry) {
    	std::cout << " - " << name << std::endl;
    }
    
    for (const auto& [name, p_params] : params.pipeRegistry) {
        pipes.emplace(name, Pipe(p_params.KLoss));
    }

    // 2. Convert VolumeParams to active Volume objects
    std::cout << "DEBUG: Volumes loaded:" << std::endl;
    for (const auto& [name, p_params] : params.volumeRegistry) {
    	std::cout << " - " << name << std::endl;
    }
    
    for (const auto& [name, v_params] : params.volumeRegistry) {
      volumes.emplace(name, CapacitiveVolume(v_params.CHyd));
    }
    
    // Initialize plant topology
		this->connectivity = ConnectivityLoader::loadFromFile(connectivityFilePath);
}

void LOxPlant::computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t) {
	// Get junction pressure state
	volumes.at("J1").pressure = x[0];
	
	// Get junction port connections
	auto& j1_neighbors = connectivity.at("J1");
	
	// Update mass flow rates
	double mdotA = pipes.at(j1_neighbors.at("A").name).computeMassFlowRate(boundaries.at("BC1").pressure,volumes.at("J1").pressure);
	double mdotB = pipes.at(j1_neighbors.at("B").name).computeMassFlowRate(boundaries.at("BC2").pressure,volumes.at("J1").pressure);
	double mdotC = 0.0;
	
	// Update junction pressure state derivative
	dxdt[0] = volumes.at("J1").computePressureStateDerivative(mdotA,mdotB,mdotC);
}

double LOxPlant::getPipeMdot(const std::string& pipeName, double p1, double p2) {
	return pipes.at(pipeName).computeMassFlowRate(p1,p2);
}

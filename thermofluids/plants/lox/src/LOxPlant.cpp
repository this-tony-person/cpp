#include "LOxPlant.hpp"
#include "../include/lox_plant_params.hpp"
#include <iostream>

// Constructor
LOxPlant::LOxPlant(const LOxPlantParams& params) : pBC1(3.0),
	pBC2(1.0) {
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
}

void LOxPlant::computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t) {
	// Get junction pressure state
	double p = x[0];
	
	// Update mass flow rates
	double mdotA = pipes.at("PO0001").computeMassFlowRate(pBC1,p);
	double mdotB = pipes.at("PO0002").computeMassFlowRate(pBC2,p);
	double mdotC = 0.0;
	
	// Update junction pressure state derivative
	dxdt[0] = volumes.at("J1").computePressureStateDerivative(mdotA,mdotB,mdotC);
}

std::vector<double> LOxPlant::getInitialState(double pJ1) {
	return {pJ1};
}

double LOxPlant::getMdotA(double p) {
	return pipes.at("PO0001").computeMassFlowRate(pBC1,p);
}

double LOxPlant::getMdotB(double p) {
	return pipes.at("PO0002").computeMassFlowRate(pBC2,p);
}

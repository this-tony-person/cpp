#pragma once
#include "lox_plant_params.hpp"
#include "connectivity_type.hpp"
#include "incl_capacitive_volume.hpp"
#include "incl_pipe.hpp"
#include <vector>
#include <map>
#include <string>

class LOxPlant {
private:
	// Component objects
	std::map<std::string, Pipe> pipes;
  std::map<std::string, CapacitiveVolume> volumes;
	
public:
	// Constructor
	explicit LOxPlant(const LOxPlantParams& params);
	
	// Plant boundary conditions
	const double pBC1;
	const double pBC2;
	
	// Core simulation methods
	void computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t);
	
	// Helper methods
	double getPipeMdot(const std::string& pipeName, double p1, double p2);
	};

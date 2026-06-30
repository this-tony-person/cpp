#pragma once
#include "lox_plant_params.hpp"
#include "connectivity_type.hpp"
#include "incl_capacitive_volume.hpp"
#include "incl_pipe.hpp"
#include "boundary_condition.hpp"
#include <vector>
#include <map>
#include <string>

class LOxPlant {
private:
	// Connectivity map
	ConnectivityMap connectivity;
	
public:
	// Component objects
	std::map<std::string, Pipe> pipes;
  std::map<std::string, CapacitiveVolume> volumes;
	std::map<std::string, BoundaryCondition> boundaries;

	// Constructor
	explicit LOxPlant(const LOxPlantParams& params, const std::string& connectivityFilePath);
	
	// Core simulation methods
	void computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t);
	
	// Helper methods
	double getPipeMdot(const std::string& pipeName, double p1, double p2);
	const ConnectivityMap& getConnectivity() const { return connectivity; }
	const std::map<std::string, Pipe>& getPipes() const { return pipes; }
	};

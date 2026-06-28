#pragma once
#include "incl_capacitive_volume.hpp"
#include "incl_pipe.hpp"
#include <vector>

class LOxPlant {
private:
	// Component objects
	Pipe PO0001;
	Pipe PO0002;
	CapacitiveVolume J1;
	
public:
	// Constructor
	LOxPlant();
	
	// Plant boundary conditions
	const double pBC1;
	const double pBC2;
	
	// Core simulation methods
	void computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t);
	
	// Helper methods
	std::vector<double> getInitialState(double pJ1);
	double getMdotA(double p);
	double getMdotB(double p);
};

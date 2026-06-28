#include "LOxPlant.hpp"

// Constructor
LOxPlant::LOxPlant() : 
	PO0001(1.0),
	PO0002(10.0),
	J1(1.0),
	pBC1(3.0),
	pBC2(1.0)
{}

void LOxPlant::computeStateDerivatives(const std::vector<double>& x, std::vector<double>& dxdt, double t) {
	// Get junction pressure state
	double p = x[0];
	
	// Update mass flow rates
	double mdotA = PO0001.computeMassFlowRate(pBC1,p);
	double mdotB = PO0002.computeMassFlowRate(pBC2,p);
	double mdotC = 0.0;
	
	// Update junction pressure state derivative
	dxdt[0] = J1.computePressureStateDerivative(mdotA,mdotB,mdotC);
}

std::vector<double> LOxPlant::getInitialState(double pJ1) {
	return {pJ1};
}

double LOxPlant::getMdotA(double p) {
	return PO0001.computeMassFlowRate(pBC1,p);
}

double LOxPlant::getMdotB(double p) {
	return PO0002.computeMassFlowRate(pBC2,p);
}

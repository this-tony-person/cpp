#include "incl_capacitive_volume.hpp"

// Constructor
CapacitiveVolume::CapacitiveVolume(double capacitance) : C(capacitance) {}
		
// Pressure state derivative method
double CapacitiveVolume::computePressureStateDerivative(double mdotA, double mdotB, double mdotC) const {
	double mdot_total = mdotA+mdotB+mdotC; // Total mass flow rate into fluid volume (kg/s)
	return mdot_total/C; // Pressure state derivative (bar/s)
};

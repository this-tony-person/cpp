#include "incl_capacitive_volume.hpp"
#include "common/constants.hpp"
#include "common/units.hpp"
#include <cmath>

// Constructor
Pipe::Pipe(double hydraulicCapacitance) : CHyd(hydraulicCapacitance) {}

// Pressure state method
double Pipe::computePressureState(double mdotA, double mdotB, double mdotC) const {
	
	Mdot = mdotA+mdotB+mdotC; // Total mass flow rate into fluid volume (kg/s)
	return runge_kutta4(Mdot/CHyd); 
};

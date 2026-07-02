#include "volume.hpp"

/**
 * @brief Component class for purely capacitive fluid volumes with hydraulic capacitance parameterization
 */

// Constructor
CapacitiveVolume::CapacitiveVolume(double capacitance) : C(capacitance) {}
		
// Pressure state derivative method
double CapacitiveVolume::computePressureStateDerivative(double netMdot) const {
	return netMdot/C; // Pressure state derivative (bar/s)
};

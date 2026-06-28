#include "incl_valve.hpp"
#include "common/constants.hpp"
#include "common/units.hpp"
#include <cmath>

/**
 * @brief Component class for purely resistive valves with Kv flow coefficient parameterization
 */

// Constructor
Valve::Valve(double flowCoefficient) : Kv(flowCoefficient) {}

// Mass flow rate method
double Valve::computeMassFlowRate(double pA, double pB) const {
	
	double dp = std::abs(pA-pB);
	double sign = (pA > pB) ? 1.0 : -1.0; 
	return sign*(Kv/Units::HR_TO_S)*std::sqrt(dp*(FluidProperties::DENSITY_FLUID*FluidProperties::DENSITY_WATER));
};

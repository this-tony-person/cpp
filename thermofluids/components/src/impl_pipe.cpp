#include "incl_pipe.hpp"
#include "common/constants.hpp"
#include "common/units.hpp"
#include <cmath>

/**
 * @brief Component class for purely resistive pipes with lumped pressure loss coefficient parameterization
 */

// Constructor
Pipe::Pipe(double lossCoefficient) : KLoss(lossCoefficient) {}

// Mass flow rate method
double Pipe::computeMassFlowRate(double pA, double pB) const {

	double dp = std::abs(pA-pB);
	double sign = (pA > pB) ? 1.0 : -1.0; 
	return sign*std::sqrt(dp)/KLoss;
};

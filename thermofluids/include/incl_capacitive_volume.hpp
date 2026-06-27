#pragma once

class CapacitiveVolume {
	private: 
	/**
	 * @brief Hydraulic capacitance (kg/bar)
	 */
	double C; 
	
	public:
	/**
	 * @brief Construct capacitive fluid volume object
	 * @param capacitance Ratio of fluid mass to bulk modulus (kg/bar)
	 */
	CapacitiveVolume(double capacitance);
	 
	/**
	 * @brief Compute pressure state by integration
	 * @param mdotA Mass inflow rate through port A (kg/s)
	 * @param mdotB Mass inflow rate through port B (kg/s)
	 * @param mdotC Mass inflow rate through port C (kg/s)
	 */
	double computePressureStateDerivative(double mdotA, double mdotB, double mdotC) const;
};

#pragma once

class CapacitiveVolume {
	private: 
	/**
	 * @brief Hydraulic capacitance (kg/bar)
	 */
	double CHyd; 
	
	public:
	/**
	 * @brief Construct capacitive fluid volume object
	 * @param hydraulicCapacitance Ratio of fluid mass to bulk modulus (kg/bar)
	 */
	CapacitiveVolume(double hydraulicCapacitance);
	 
	/**
	 * @brief Compute pressure state by integration
	 * @param mdotA Mass inflow rate through port A (kg/s)
	 * @param mdotB Mass inflow rate through port B (kg/s)
	 * @param mdotC Mass inflow rate through port C (kg/s)
	 */
	double computePressureState(double mdotA, double mdotB, double mdotC) const;
};

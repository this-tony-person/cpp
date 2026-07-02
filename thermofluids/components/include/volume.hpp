#pragma once

class CapacitiveVolume {
	private: 
	/**
	 * @brief Hydraulic capacitance (kg/bar)
	 */
	double C; 
	
	public:
	double pressure; // Internal pressure state (bar)
	double pressureDerivative; // Internal pressure state derivative (bar/s)
	
	/**
	 * @brief Construct capacitive fluid volume object
	 * @param capacitance Ratio of fluid mass to bulk modulus (kg/bar)
	 */
	CapacitiveVolume(double capacitance);
	 
	/**
	 * @brief Compute pressure state derivative
	 * @param netMdot Total mass inflow rate through all ports (kg/s)
	 */
	double computePressureStateDerivative(double netMdot) const;
};

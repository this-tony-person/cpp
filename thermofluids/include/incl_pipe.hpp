#pragma once

class Pipe {
	public: 
		/**
		 * @brief Pressure loss coefficient (unitless)
		 */
		double KLoss;
		
		/**
		 * @brief Construct purely resistive (quasi-steady) pipe object 
		 * @param lossCoefficient Pressure loss coefficient of pipe (unitless)
		 */
		Pipe(double lossCoefficient);
	
		/**
		 * @brief Calculates mass flow rate from pressure boundary conditions
		 * @param pA Pressure boundary condition at port A (bar)
		 * @param pB Pressure boundary condition at port B (bar)
		 */
		double computeMassFlowRate(double pA, double pB) const;
};

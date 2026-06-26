#pragma once 

class Valve {
	private:
		/**
		 * @brief Flow coefficient (kg/hr/sqrt(bar))
		 */
		double Kv;
		
	public:
		/**
		 * @brief Construct purely resistive (quasi-steady) valve object
		 * @param flowCoefficient Kv flow coefficient of valve (kg/hr/sqrt(bar))
		 */
		Valve(double flowCoefficient);
		
		/**
		 * @brief Compute steady-state mass flow rate from pressure boundary conditions
		 * @param pA Pressure boundary condition at port A (bar)
		 * @param pB Pressure boundary condition at port B (bar)
		 */
		double computeMassFlowRate(double pA, double pB) const;
};

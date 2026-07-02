#pragma once

class BoundaryCondition {
	/**
	 * @brief Fixed pressure boundary condition (bar)
	 */
	public:
		double pressure; 
		
		BoundaryCondition(double p);
};

#include "valve.hpp"
#include <iostream>

int main() {
	double input_Kv = 10;
	Valve RSV_O0001(input_Kv);
	
	double mdot = RSV_O0001.computeMassFlowRate(10,1);
	std::cout << "Mass flow rate from port A to port B (kg/s): " << mdot << std::endl;
	
	return 0;
};

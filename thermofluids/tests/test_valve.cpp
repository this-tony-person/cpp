#include "incl_valve.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	double input_Kv = 0.0;
	input_Kv = std::stod(argv[1]);
	Valve RSV_O0001(input_Kv);
	
	double mdot = RSV_O0001.computeMassFlowRate(10,1);
	std::cout << "Mass flow rate from port A to port B (kg/s): " << mdot << std::endl;
	
	return 0;
};

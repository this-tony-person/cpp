#include "pipe.hpp"
#include <iostream>

int main(){
	
	double KLoss = 2.0;
	Pipe Pipe_O0001(KLoss);
	
	double mdot = Pipe_O0001.computeMassFlowRate(10,1);
	std::cout << "Mass flow rate from port A to port B (kg/s): " << mdot << std::endl;
	
	return 0;
};

#include "incl_pipe.hpp"
#include <iostream>

int main(int argc, char* argv[]){
	
	double KLoss = 1.0;
	KLoss = std::stod(argv[1]);
	Pipe Pipe_O0001(KLoss);
	
	double mdot = Pipe_O0001.computeMassFlowRate(10,1);
	std::cout << "Mass flow rate from port A to port B (kg/s): " << mdot << std::endl;
	
	return 0;
};

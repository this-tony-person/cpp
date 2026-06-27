#include "incl_capacitive_volume.hpp"
#include <vector>
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <fstream>

int main() {
	// Test parameters
	double capacitance = 0.5; // Hydraulic capacitance (kg/bar)
	double initial_pressure = 1.0; // Initial pressure (bar)
	double mdotA = 0.02; // Mass inflow rate through port A (kg/s)
	double mdotB = 0.01; // Mass inflow rate through port B (kg/s)
	double mdotC = -0.005; // Mass inflow rate through port C (kg/s)
	double tStart = 0.0; // Simulation start time (s)
	double tEnd = 10.0; // Simulation end time (s)
	double dt = 0.01; // Solver time step (s)

	// Initialize capacitive fluid component
	CapacitiveVolume junction(capacitance);
	
	// System state vector for ODE solver
	std::vector<double> p = {initial_pressure};
	
	// System assembly
	auto system = [&](const std::vector<double> &x, std::vector<double> &dxdt, double t) {
	dxdt[0] = junction.computePressureStateDerivative(mdotA,mdotB,mdotC);
	};
	
	// ODE solver setup
	boost::numeric::odeint::runge_kutta4<std::vector<double>> stepper;
	
	// Runtime execution loop
	double t = tStart;
	std::cout << "Time (s), Pressure (bar)" << std::endl;
	std::ofstream outfile("output_test_capacitive_volume.csv");
	outfile << "Time,Pressure\n"; 
	
	while (t < tEnd) {
		std::cout << t << "," << p[0] << std::endl;
		outfile << t << "," << p[0] << "\n";
		
		stepper.do_step(system,p,t,dt);
		t += dt;
	}
	outfile.close();
	
	return 0;
};

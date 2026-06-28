#include "LOxPlant.hpp"
#include "lox_plant_loader.hpp"
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <fstream>

int main() {
	// Load plant parameters
	LOxPlantParams params = LOxPlantLoader::load("./plants/lox/data/pipe_params.csv", "./plants/lox/data/volume_params.csv");

	// Instantiate plant model
	LOxPlant lox(params);
	
	// Initialize differential states
	double pJ1 = 1.0;
	double pJ2 = 1.0;
	std::vector<double> p = lox.getInitialState(pJ1);
	
	// Configure ODE solver
	double t = 0.0;
	double tStop = 10.0;
	double dt = 0.01;
	
	boost::numeric::odeint::runge_kutta4<std::vector<double>> stepper;
	
	// Configure I/O logging
	std::ofstream outfile("output_test_lox_plant.csv");
	outfile << "Time,pJunction,pBC1,pBC2,mdotA,mdotB,mdotC\n";
	
	// Execute integration loop
	while (t<tStop) {
		// Get mass flow rates
		double mdotA = lox.getMdotA(p[0]);
		double mdotB = lox.getMdotB(p[0]);
		double mdotC = 0.0;
		
		// Log current state
		outfile << t << "," << p[0] << "," << lox.pBC1 << "," << lox.pBC2 << "," << mdotA << "," << mdotB << "," << mdotC << "\n";
		
		// Integrate state derivatives
		stepper.do_step([&](const std::vector<double>& x, std::vector<double>& dxdt, double t) {
			lox.computeStateDerivatives(x,dxdt,t);
		},p,t,dt);

		t+=dt;		
	}
	
	outfile.close();
	std::cout << "Simulation complete" << std::endl;
	
	return 0;
}

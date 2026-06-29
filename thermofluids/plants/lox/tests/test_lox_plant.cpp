#include "LOxPlant.hpp"
#include "lox_plant_loader.hpp"
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <fstream>

int main() {
	// Load plant parameters
	LOxPlantParams params = LOxPlantLoader::load("./plants/lox/data/pipe_params.csv", "./plants/lox/data/volume_params.csv");

	// Instantiate plant model
	std::string connectivityFilePath = "./plants/lox/data/connectivity_map.yaml";
	LOxPlant lox(params,connectivityFilePath);
	
	// Initialize differential states
	double pJ1 = 1.0;
	std::vector<double> p = {pJ1};
	
	// Configure ODE solver
	double t = 0.0;
	double tStop = 10.0;
	double dt = 0.01;
	
	boost::numeric::odeint::runge_kutta4<std::vector<double>> stepper;
	
	// Configure I/O logging
	std::ofstream outfile("output_test_lox_plant.csv");
	outfile << "Time,pJunction,pBC1,pBC2";
	for (const auto& [name,pipe] : lox.pipes) {
		outfile << "," << "mdot_" << name;
	}
	outfile << "\n";
	
	// Get connectivity data
	const auto& j1_connections = lox.getConnectivity().at("J1");
	
	// Execute integration loop
	while (t<tStop) {
	
		// Get mass flow rates
		double mdotA = lox.getPipeMdot(j1_connections.at("A").name,lox.pBC1,p[0]);
		double mdotB = lox.getPipeMdot(j1_connections.at("B").name,lox.pBC2,p[0]);
		double mdotC = 0.0;
		
		// Log current state
		outfile << t << "," << p[0] << "," << lox.pBC1 << "," << lox.pBC2;
		for (const auto& [name, pipe] : lox.pipes) {
			double mdot = pipe.computeMassFlowRate(name,p[0]);
			outfile << "," << mdot;
		}
		outfile << "\n";
		
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

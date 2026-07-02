#include "LOxPlant.hpp"
#include "lox_plant_loader.hpp"
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <fstream>

int main() {
	// Load plant parameters
	LOxPlantParams params = LOxPlantLoader::load("./plants/lox/data/pipe_params.csv", "./plants/lox/data/volume_params.csv", "./plants/lox/data/boundary_params.csv");

	// Instantiate plant model
	std::string connectivityFilePath = "./plants/lox/data/connectivity_map.yaml";
	LOxPlant lox(params,connectivityFilePath);
	
	// Initialize differential states
	for (auto& [volName, volume] : lox.volumes) {
		volume.pressure = 1.0;
	}
	std::vector<double> p;
	p.reserve(lox.volumes.size());
	
	for (auto& [volName,volume] : lox.volumes) {
		p.push_back(volume.pressure);
	}
	
	
	// = {lox.volumes.at("J1").pressure};
	
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
	const auto& PO0001_connections = lox.getConnectivity().at("PO0001");
	const auto& PO0002_connections = lox.getConnectivity().at("PO0002");
	
	// Execute integration loop
	while (t<tStop) {
		
		// Log current state
		outfile << t << "," << p[0] << "," << lox.boundaries.at("BC1").pressure << "," << lox.boundaries.at("BC2").pressure;
		
		for (const auto& [name, pipe] : lox.pipes) {
			const auto& pipeConnections = lox.getConnectivity().at(name); // Pipe connections	
					
			std::string connA = pipeConnections.at("A").name; // Port-A neighbor
			std::string connB = pipeConnections.at("B").name; // port-B neighbor
			
			double mdot = lox.getPipeMdot(name,lox.getPressure(connA),lox.getPressure(connB));
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

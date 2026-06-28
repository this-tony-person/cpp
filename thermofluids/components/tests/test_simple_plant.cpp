#include "incl_capacitive_volume.hpp"
#include "incl_valve.hpp"
#include "incl_pipe.hpp"
#include <vector>
#include <boost/numeric/odeint.hpp>
#include <fstream>

int main() {
	// Component parameterization
	double KLoss1 = 1; // Pipe pressure loss coefficient (1)
	double KLoss2 = 10; // Pipe pressure loss coefficient (1)
	double C1 = 1; // Hydraulic capacitance (kg/bar)
	
		// Component object definitions
	Pipe PO0001(KLoss1); 
	Pipe PO0002(KLoss2);
	CapacitiveVolume J1(C1);
	
	// Plant boundary conditions
	double pBC1 = 3; // Pressure boundary condition 1 (bar)
	double pBC2 = 1; // Pressure boundary condition 2 (bar)
	
	// Plant initial states
	double pJ1 = 1; // Pressure at capacitive volume J1 (bar)
	double mdotA = PO0001.computeMassFlowRate(pBC1,pJ1); // Mass inflow rate through port A (kg/s)
	double mdotB = PO0001.computeMassFlowRate(pBC2,pJ1); // Mass inflow rate through port B (kg/s)
	double mdotC = 0; // Mass inflow rate through port C (kg/s)
	
	// Solver parameterization
	double tStart = 0; // Simulation start time (s)
	double tStop = 10.0; // Simulation stop time (s)
	double dt = 0.01; // Simulation time step size (s)
	
	// Plant assembly definition
	auto plant = [&](const std::vector<double> &x, std::vector<double> &dxdt, double t) {
	
		// Get junction pressure state
		double p = x[0];
	
		// Update mass flow rates into junction
		mdotA = PO0001.computeMassFlowRate(pBC1,p);
		mdotB = PO0002.computeMassFlowRate(pBC2,p);
		mdotC = 0;
		
		// Update junction pressure state derivative
		dxdt[0] = J1.computePressureStateDerivative(mdotA,mdotB,mdotC);
	};
	
	// Plant state vector initialization
	std::vector<double> p = {pJ1};
	
	// Time stepper configuration
	boost::numeric::odeint::runge_kutta4<std::vector<double>> stepper;
	
	// Time stepper loop
	double t = tStart;
	std::ofstream outfile("output_test_simple_plant.csv");
	outfile << "Time,pJunction,pBC1,pBC2,mdotA,mdotB,mdotC\n";
	
	while (t<tStop) {
		outfile << t << "," << p[0] << "," << pBC1 << "," << pBC2 << "," << mdotA << "," << mdotB << "," << mdotC << "\n";
		
		// Integrate pressure states
		stepper.do_step(plant,p,t,dt);
		t += dt;
	}
	outfile.close();
	
	return 0;
};

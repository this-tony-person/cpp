import sys # To access CLI variables passed to Python interpreter
import subprocess # To run C++ sim from Python code
import pandas as pd # To handle sim output data files (e.g., CSV)
import matplotlib.pyplot as plt # To plot simulation data
import os # To access file paths and names (e.g., for plot titles)

def run_test(cpp_executable):
	# Construct CSV output file name
	exe_name = os.path.basename(cpp_executable)
	csv_output = f"output_{exe_name}.csv"
	
	# Run C++ simulation
	print(f"Running: {cpp_executable}")
	subprocess.run([cpp_executable], check=True)
	
	# Load sim data
	df = pd.read_csv(csv_output)
	
	# Create figure with two subplots
	fig, (ax1,ax2) = plt.subplots(2,1,figsize=(10,8),sharex=True)
	
	# Subplot 1: pressures
	ax1.plot(df['Time'],df['p_J1'],label='Junction Pressure')
	ax1.plot(df['Time'],df['p_BC1'],'--',label='Pressure BC 1')
	ax1.plot(df['Time'],df['p_BC2'],'--',label='Pressure BC 2')
	ax1.set_xlabel('Time (s)')
	ax1.set_ylabel('Pressure (bar)')
	ax1.legend()
	ax1.grid(True)
	
	# Subplot 2: mass flow rates
	ax2.plot(df['Time'],df['mdot_PO0001'],label='Port A mass inflow rate')
	ax2.plot(df['Time'],df['mdot_PO0002'],label='Port B mass outflow rate')
	ax2.set_xlabel('Time (s)')
	ax2.set_ylabel('Mass Flow Rate (kg/s)')
	ax2.legend()
	ax2.grid(True)
	
	# Show plot
	plt.tight_layout()
	plt.show()

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print("Usage: python3 run_test.py <path_to_executable>")
	else: 
		run_test(sys.argv[1])

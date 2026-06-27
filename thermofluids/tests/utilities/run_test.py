import sys
import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os

def run_test(cpp_executable):
	# Construct CSV output file name
	exe_name = os.path.basename(cpp_executable)
	csv_output = f"output_{exe_name}.csv"
	
	# Run C++ simulation
	print(f"Running: {cpp_executable}")
	subprocess.run([cpp_executable], check=True)
	
	# Plot sim results
	data_file = pd.read_csv(csv_output)
	x_col = data_file.columns[0]
	
	plt.figure(figsize=(10,6))
	for col in data_file.columns[1:]:
		plt.plot(data_file[x_col], data_file[col], label=col, marker='.', markersize=2)
		
	plt.title(f"{exe_name}")
	plt.xlabel(x_col)
	plt.ylabel("Value")
	plt.legend()
	plt.grid(True)
	plt.show()

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print("Usage: python3 run_test.py <path_to_executable>")
	else: 
		run_test(sys.argv[1])

import sys
import pandas as pd
import matplotlib.pyplot as plt
import os

filename = sys.argv[1]
title = os.path.basename(filename)

datafile = pd.read_csv(filename)
x_col = datafile.columns[0]

for col in datafile.columns[1:]:
	plt.plot(datafile[x_col],datafile[col], label=col)
	
plt.title(title)	
plt.xlabel(x_col)
plt.ylabel("Value")
plt.legend()
plt.grid(True)
plt.show()

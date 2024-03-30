import sys
import matplotlib.pyplot as plt
import numpy as np

# Reading data
datano3 = np.loadtxt('./data/tcompno3Div.dat', delimiter='\t', skiprows=1)
datao3 = np.loadtxt('./data/tcompo3Div.dat', delimiter='\t', skiprows=1)
# time = np.arange(len(data))

fig, ax = plt.subplots(figsize=(6,4))

# Plot data
ax.plot(datano3[:,0], datano3[:,1], 'k', label='Normal')
ax.plot(datao3[:,0], datao3[:,1], 'r', label='O3')

ax.set_ylabel('Time')
ax.set_xlabel('Divisions')
ax.grid(alpha=.2)
ax.legend()

plt.savefig("./graficas/tcomp.pdf")

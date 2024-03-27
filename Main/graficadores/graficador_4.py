import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# General regression function, can be applied anywhere pretty much
def regression(x, y, expected):
    popt, pcov = curve_fit(expected, xdata = x, ydata = y)
    reg = expected(x, popt[0], popt[1])
    perr = np.sqrt(np.diag(pcov))
    R2 = 1-((np.sum((expected(x, popt[0], popt[1])-y)**2))/(np.var(y)*y.shape[0]))

    return reg, popt, perr, R2

# Exponential function
def exp(x, a, tau):
    return a*np.exp(-x/tau)

def plot(data_path):
    # Reading data
    data = np.loadtxt(data_path, delimiter=',')
    time = np.arange(len(data))

    fig, ax = plt.subplots(figsize=(6,4))

    # Plot data
    ax.plot(time, data, 'k', label='Data')

    # Regression
    reg, popt, perr, R2 = regression(time, data, exp)
    ax.plot(time, reg, 'r--', label='Regression')

    ax.set_ylabel('Number of Particles Inside Container')
    ax.set_xlabel('Time')
    ax.grid(alpha=.2)
    ax.legend()

    # Display the results
    print("R2:",R2)
    print(f"a: {popt[0]}  ,  tau: {popt[1]}")

    plt.savefig("./graficas/punto4.pdf")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python graficador.py <data_path>")
        sys.exit(1)

    data_path = sys.argv[1]
    
    plot(data_path)
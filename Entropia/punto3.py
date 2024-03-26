import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

def readfile(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    return [float(line.split()[0]) for line in lines], [float(line.split()[1]) for line in lines]


def rw(data_path):
    t, rw = readfile(data_path)

    log_t = np.log(t)
    log_size = np.log(rw)
    slope, intercept, r_value, p_value, std_err = linregress(log_t, log_size)

    n = len(log_t)
    se_intercept = std_err * np.sqrt(np.sum(log_t**2) / n)

    teorica_x = np.linspace(min(log_t), max(log_t), n)
    teorica_y = intercept + slope * teorica_x

    fig, ax = plt.subplots()
    ax.scatter(t, rw, label='Random Walk', s=5)
    label_ajuste=f'Ajuste: k*log(x)+b\nk={slope:.2f}±{std_err:.2f}, b={intercept:.2f}±{se_intercept:.2f}'
    ax.plot(np.exp(teorica_x), np.exp(teorica_y), label=label_ajuste, color="red")

    ax.set_xlabel("t")
    ax.set_ylabel("Drop Size")
    ax.set_xscale('log')
    ax.set_yscale('log')
    ax.legend()
    ax.grid(True, linewidth=0.1)
    ax.set_title(f'Random Walk Performed')

    # Display the results
    print(f"Slope: {slope:.2f}±{std_err:.2f}")
    print(f"Intercept: {intercept:.2f}±{se_intercept:.2f}")
    print(f"R-squared: {r_value**2}")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python graficador.py <data_path>")
        sys.exit(1)

    data_path = sys.argv[1]
    
    rw(data_path)
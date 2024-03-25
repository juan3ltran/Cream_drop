import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

def dispercion(data_path):
    datos=pd.read_csv(data_path, sep='\t', header=0)
    
    log_size = np.log(datos['size'])
    log_equilibrio = np.log(datos['equilibrio'])

    # Performing linear regression with scipy
    slope, intercept, r_value, p_value, std_err = linregress(log_size, log_equilibrio)

    # Calculate the standard error of the intercept
    n = len(log_size)
    se_intercept = std_err * np.sqrt(np.sum(log_size**2) / n)

    # Generating theoretical values for plotting
    teorica_x = np.linspace(min(log_size), max(log_size), 40)
    teorica_y = intercept + slope * teorica_x

    # Plotting
    fig, ax = plt.subplots()
    ax.scatter(datos['size'], datos['equilibrio'], label='Entropia', s=5)

    label_ajuste=f'Ajuste: k*log(x)+b\nk={slope:.2f}±{std_err:.2f}, b={intercept:.2f}±{se_intercept:.2f}'
    ax.plot(np.exp(teorica_x), np.exp(teorica_y), label=label_ajuste, color="red")

    ax.set_xlabel("Size")
    ax.set_ylabel("Tiempo para el equilibrio")
    ax.set_xscale('log')
    ax.set_yscale('log')
    ax.legend()
    ax.grid(True, linewidth=0.1)
    ax.set_title(f'Tiempo de equilibrio en funcion del tamaño del contenedor')

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
    
    dispercion(data_path)
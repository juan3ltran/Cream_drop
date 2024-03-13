import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

def dispercion(data_path):
    datos=pd.read_csv(data_path, sep='\t', header=0)

    fig, ax = plt.subplots()
    ax.plot(datos['x'], datos['y'], label = 'Posicion', marker='.')
    ax.set_xlabel("x")
    ax.set_ylabel("Gamma (x)")
    ax.legend()
    ax.grid(True)
    ax.set_title('Funcon Gamma')
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python graficador.py <data_path>")
        sys.exit(1)

    data_path = sys.argv[1]
    
    dispercion(data_path)
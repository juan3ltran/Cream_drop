import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

def dispercion(data_path):
    datos=pd.read_csv(data_path, sep='\t', header=0)

    fig, ax = plt.subplots()
    ax.scatter(datos['x'], datos['y'], label = 'Cream', s=10)
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_xlim(-10,10)
    ax.set_ylim(-10,10)
    ax.legend()
    ax.grid(True, linewidth=0.1)
    ax.set_title('Cream Drop')
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python graficador.py <data_path>")
        sys.exit(1)

    data_path = sys.argv[1]
    
    dispercion(data_path)
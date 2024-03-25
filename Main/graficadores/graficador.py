import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

def dispercion(data_path):
    divisions=8

    datos=pd.read_csv(data_path, sep='\t', names=['t','entropia'])
    data_size = len(datos['t'])

    diferencia = abs(datos['entropia'])

    fig, ax = plt.subplots( )
    ax.scatter(datos['t'], datos['entropia'], label = 'Entropia', s=1)
    ax.set_xlabel("Tiempo")
    ax.set_ylabel("Entropia")
    ax.hlines(-np.log(1/divisions**2), 0, data_size, linestyles='dotted')
    ax.set_ylim(0,5)
    ax.legend()
    ax.grid(True, linewidth=0.1)
    ax.set_title(f'Entropia en funcion del tiempo (divisiones: {divisions})')
    print(f"Entropia final: {datos['entropia'][data_size-1]}")
    print(f"Tiempo equilibrio: {datos['t'][data_size-1]}")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python graficador.py <data_path>")
        sys.exit(1)

    data_path = sys.argv[1]
    
    dispercion(data_path)
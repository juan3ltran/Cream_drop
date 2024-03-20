import sys
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm

def dispercion(data_path):
    datos=pd.read_csv(data_path, sep='\t', header=0)

    diferencia = abs(datos['entropia1']/datos['entropia2']-1)

    fig, ax = plt.subplots(2,1, figsize=(8,8))
    ax[0].scatter(datos['t'], datos['entropia1'], label = 'Entropia 1', s=7)
    ax[0].scatter(datos['t'], datos['entropia2'], label = 'Entropia 2', s=5)
    ax[0].set_xlabel("Tiempo")
    ax[0].set_ylabel("Entropia")
    ax[0].legend()
    ax[0].grid(True, linewidth=0.1)
    ax[0].set_title('Entropia en funcion del tiempo')

    ax[1].scatter(datos['t'], diferencia, label = 'Entropia 1', s=5)
    ax[1].set_yscale('log')
    ax[1].set_xlabel("Tiempo")
    ax[1].set_ylabel("Dif relativa Entropia")
    ax[1].legend()
    ax[1].grid(True, linewidth=0.1)
    ax[1].set_title('Diferencia Entropia en funcion del tiempo con ambos metodos')

    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python graficador.py <data_path>")
        sys.exit(1)

    data_path = sys.argv[1]
    
    dispercion(data_path)
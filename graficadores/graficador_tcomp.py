import matplotlib.pyplot as plt
import numpy as np


def plotit(data_path, subplotInd, label):
    # Read data
    datano3 = np.loadtxt('./data/'+data_path[0], delimiter='\t', skiprows=1)
    datao3 = np.loadtxt('./data/'+data_path[1], delimiter='\t', skiprows=1)

    axs[subplotInd].plot(datano3[:,0], datano3[:,1], 'k', label='Normal')
    axs[subplotInd].plot(datao3[:,0], datao3[:,1], 'r', label='O3')

    if subplotInd==0: axs[subplotInd].set_ylabel('Tiempo de cómputo [ms]')
    axs[subplotInd].set_xlabel(label)
    axs[subplotInd].grid(alpha=.2)
    axs[subplotInd].legend()


if __name__ == "__main__":

    dataPaths = np.array([['tcompno3Div.dat','tcompo3Div.dat'], ['tcompno3Npart.dat','tcompo3Npart.dat'], ['tcompno3Size.dat','tcompo3Size.dat']])
    labels= ['Divisiones para la entropía', 'Número de partículas', 'Tamaño del lado del contenedor']

    fig, axs = plt.subplots(1,3, figsize=(12,4))

    for i in range(len(dataPaths)):
        plotit(dataPaths[i], i, labels[i])

    plt.tight_layout()
    plt.savefig('./graficas/tcomp.pdf')
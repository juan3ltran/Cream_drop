import matplotlib.pyplot as plt
import numpy as np

# Parámetros de la distribución normal
media = 50
desviacion = 15

# Número de puntos a dispersar
num_puntos = 100

# Generar coordenadas siguiendo una distribución normal
x = np.random.normal(media, desviacion, num_puntos)
y = np.random.normal(media, desviacion, num_puntos)

# Guardar los puntos en un archivo .dat
data = np.column_stack((x, y))
np.savetxt(f'data/datos{desviacion}.dat', data, fmt='%.18e', delimiter=' ', newline='\n')


# Crear la figura y el eje
fig, ax = plt.subplots()

# Dibujar el cuadrado
lado = 100
ax.add_patch(plt.Rectangle((0, 0), lado, lado, fill=None, color='black'))

# Dibujar los puntos
ax.scatter(x, y)

# Configurar el tamaño del eje
ax.set_xlim(0, lado)
ax.set_ylim(0, lado)

# Mostrar la gráfica
plt.gca().set_aspect('equal', adjustable='box')
plt.show()
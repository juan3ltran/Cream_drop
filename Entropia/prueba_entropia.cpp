#include <iostream>
#include <vector>
#include <cmath> 

int main() {

    const int N_particles = 100; // Número de partículas
    const double x_min = 0, x_max = 100; // Límites para x
    const double y_min = 0, y_max = 100; // Límites para y
    const int divisions = 8; // Divisiones en x e y

    // Calcula el tamaño de cada subdivisión
    double x_step = (x_max - x_min) / divisions;
    double y_step = (y_max - y_min) / divisions;

    // Inicializa un vector para contar las partículas en cada subdivisión
    std::vector<std::vector<int>> particle_counts(divisions, std::vector<int>(divisions, 0));

    // Lee las posiciones de las partículas y cuenta en qué subdivisión caen
    double x, y;
    for (int i = 0; i < N_particles; ++i) {
        
        //Posicion de Particula iesima
        std::cin >> x >> y;

        //Verifica la posicion dentro de los limites
        if ((x_min < x) && (x < x_max) && (y_min < y) && (y < y_max))
        {
            // Calcula el índice de la subdivisión para x e y
            int ix = int((x - x_min) / x_step);
            int iy = int((y - y_min) / y_step);

            // Incrementa el contador para esa subdivisión
            particle_counts[ix][iy]++;
        }
    }

    // Calcula la entropía
    double entropy = 0.0;
    for (int ix = 0; ix < divisions; ++ix) {
        for (int iy = 0; iy < divisions; ++iy) {
            if (particle_counts[ix][iy] > 0) {
                double p = double(particle_counts[ix][iy]) / N_particles;
                entropy -= p * log(p);
            }
        }
    }

    std::cout << "Entropía: " << entropy << std::endl;

    return 0;
}
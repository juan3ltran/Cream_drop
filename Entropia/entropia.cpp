#include <iostream>
#include <vector>
#include <cmath> 

//Function declaration
void counts(std::vector<std::vector<int>>& grid_counts, double x, double y, const double x_min, 
const double x_max, const double y_min, const double y_max, int divisions);

double compute_entropy(std::vector<std::vector<int>>& grid_counts, int N_particles);


int main(int argc, char **argv) {
    //Parametros para calcular la entropia
    const int N_particles = 400; // Número de partículas
    const double x_min = 0, x_max = 100; // Límites para x
    const double y_min = 0, y_max = 100; // Límites para y
    const int divisions = 8; // Subdivisiones de la grilla

    // Inicializa una matriz para contar las partículas en cada subdivisión
    std::vector<std::vector<int>> grid_counts(divisions, std::vector<int>(divisions, 0));

    // Lee las posiciones de las partículas y cuenta en qué subdivisión caen
    double x, y;
    for (int i = 0; i < N_particles; ++i) {
        
        //Posicion de Particula iesima
        std::cin >> x >> y;
        //Conteo de particula en la subdivision
        counts(grid_counts, x, y, x_min, x_max, y_min, y_max, divisions);
    }

    // Calcula la entropía
    double entropy;
    entropy = compute_entropy(grid_counts, N_particles);

    std::cout << "Entropía: " << entropy << std::endl;

    return 0;
}


//implementacion de funciones
double compute_entropy(std::vector<std::vector<int>>& grid_counts, int N_particles)
{
    // Calcula la entropía
    double entropy = 0.0;
    int divisions = grid_counts.size();

    for (int ix = 0; ix < divisions; ++ix) {
        for (int iy = 0; iy < divisions; ++iy) {
            if (grid_counts[ix][iy] > 0) {
                double p = double(grid_counts[ix][iy]) / N_particles;
                entropy -= p * log(p);
            }
        }
    }
    return entropy;
}

void counts(std::vector<std::vector<int>>& grid_counts, double x, double y, double x_min, 
double x_max, double y_min, double y_max, int divisions)
{
    //Compute the size of each subdivision
    double x_step = (x_max - x_min) / divisions;
    double y_step = (y_max - y_min) / divisions;

    //Verifica la posicion dentro de los limites
        if ((x_min < x) && (x < x_max) && (y_min < y) && (y < y_max))
        {
            // Calcula el índice de la subdivisión para x e y
            int ix = int((x - x_min) / x_step);
            int iy = int((y - y_min) / y_step);

            // Incrementa el contador para esa subdivisión
            grid_counts[ix][iy]++;
        }
}
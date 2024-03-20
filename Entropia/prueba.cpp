#include "entropia_h.hpp"
#include<iostream>

/*int main(int argc, char **argv) {
    //Parametros para calcular la entropia
    const int N_particles = 50; // Número de partículas
    const double x_min = -5, x_max = 5; // Límites para x
    const double y_min = -5, y_max = 5; // Límites para y
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
}*/
#include <fstream>
#include <sstream>
#include <string>

void processFiles(const std::string& filePath1, const std::string& filePath2) {
    std::ifstream file1(filePath1), file2(filePath2);
    std::string line1, line2;

    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        // Procesa la fila del primer archivo
        std::istringstream iss1(line1);
        double x1, y1;
        if (!(iss1 >> x1 >> y1)) { std::cerr << "Error de lectura del primer archivo." << std::endl; break; }

        // Procesa la fila del segundo archivo
        std::istringstream iss2(line2);
        double x2, y2;
        if (!(iss2 >> x2 >> y2)) { std::cerr << "Error de lectura del segundo archivo." << std::endl; break; }

        // Aquí puedes manipular x1, y1 (valores del primer archivo) y x2, y2 (valores del segundo archivo) como necesites
        // Por ejemplo, solo imprimirlos:
        std::cout << "Archivo 1: " << x1 << ", " << y1 << " | Archivo 2: " << x2 << ", " << y2 << std::endl;
    }

    file1.close();
    file2.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo1.dat> <archivo2.dat>" << std::endl;
        return 1;
    }

    std::string filePath1 = argv[1];
    std::string filePath2 = argv[2];

    processFiles(filePath1, filePath2);

    return 0;
}
#include "utils.hpp"


int main(int argc, char *argv[]) {
    //Declara variables
    int t_final, N_particles, divisions, seed;    
    double x_min, x_max, y_min, y_max;
    //lee el input
    std::string archivoEntrada = argv[1];
    std::ifstream archivo(archivoEntrada);
    std::string linea;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            std::istringstream iss(linea);
            std::string valor;
            std::string comentario;
            iss >> valor >> comentario;
            if (comentario == "#N_moleculas") {
                N_particles = std::stoi(valor);
            } else if (comentario == "#size") {
                // Asume que x_max, x_min, y_max, y_min usan el mismo valor de "size"
                double size = std::stod(valor);
                x_min = -size;
                x_max = size;
                y_min = -size;
                y_max = size;
            } else if (comentario == "#t_final") {
                t_final = std::stoi(valor);
            } else if (comentario == "#divisiones") {
                divisions = std::stoi(valor);
            } else if (comentario == "#seed"){
                seed = std::stoi(valor);
            }

        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo de configuración.\n";
        return 1;
    }
    //Crea el archivo que resuelve el punto
    std::ofstream entropia ("./data/punto1.dat"); 
    std::vector<Particle> balls;

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles);
    //grid entropy
    std::vector<int> grid_counts2(divisions*divisions,0);
    for (auto ball : balls){
        counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy = compute_entropy(grid_counts2, N_particles);
   
    int coin;
    for (int i = 0; i < t_final; i++)
    {
        
        coin = getRandomInt(N_particles-1, seed); //Selecciona que particula se movera
        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        double old_x = balls[coin].getX();
        double old_y = balls[coin].getY();
        balls[coin].moveRandom(1, x_min, x_max, y_min, y_max, seed);        
        
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        double new_x = balls[coin].getX();
        double new_y = balls[coin].getY();
        
        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy += ds;

        entropia<<i<<"\t"<<entropy<<std::endl;
       
        
    }
    entropia.close();
    return 0;
}
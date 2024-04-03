#include "utils.hpp"


int main(int argc, char *argv[]) {
    //Declara variables
    int t_final, N_particles, divisions, seed;    
    double size, x_min, x_max, y_min, y_max;

    //lee el input asumiendo que cada valor tiene un comentario (que debe ser ignorado)
    std::cin >> N_particles; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> size; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> t_final; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> divisions; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> seed; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // limites del contenedor
    x_min=-size;
    x_max=size;
    y_min=-size;
    y_max=size;

    //Crea el vector de particulas y el generador aleatorio
    std::vector<Particle> balls;
    std::mt19937 gen(seed);

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles, size);
    //grid entropy
    std::unordered_map<int,int> grid_counts;
    for (auto ball : balls){
        counts(grid_counts, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy = compute_entropy(grid_counts, N_particles);
   
    int coin;
    for (int i = 0; i < t_final; i++)
    {
        
        coin = getRandomInt(N_particles-1, gen); //Selecciona que particula se movera
        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        double old_x = balls[coin].getX();
        double old_y = balls[coin].getY();
        balls[coin].moveRandom(1, x_min, x_max, y_min, y_max, gen);        
        
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        double new_x = balls[coin].getX();
        double new_y = balls[coin].getY();
        
        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy += ds;
     
        
    }
    std::cout<<"Entropía final: "<<entropy;
    return 0;
}
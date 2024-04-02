#include "utils.hpp"
#include <chrono>
#include <fstream>

auto simulation(int t_final, int N_particles, int divisions, int seed, double size){
    // Initializing time-measuring variables
    auto t_start = std::chrono::steady_clock::now();

    double x_min, x_max, y_min, y_max;
    // limites del contenedor
    x_min=-size/2;
    x_max=size/2;
    y_min=-size/2;
    y_max=size/2;

    //Crea el vector de particulas y el generador aleatorio
    std::vector<Particle> balls;
    std::mt19937 gen(seed);

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles, size);
    //grid entropy
    std::vector<int> grid_counts2(divisions*divisions,0);
    for (auto ball : balls){
        counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy = compute_entropy(grid_counts2, N_particles);

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
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy += ds;

        // std::cout<<i<<"\t"<<entropy<<std::endl;
    }

    auto t_end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count();
}
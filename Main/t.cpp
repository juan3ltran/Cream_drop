#include "utils.hpp"
#include <chrono>
#include <fstream>

auto simulation(int t_final, int N_particles, int divisions, int seed, double size){
    // Initializing time-measuring variables

    double x_min, x_max, y_min, y_max;
    // limites del contenedor
    x_min=-size/2;
    x_max=size/2;
    y_min=-size/2;
    y_max=size/2;

    //Crea el vector de particulas y el generador aleatorio
    std::vector<Particle> balls;
    std::mt19937 gen(seed);



    auto t_start = std::chrono::steady_clock::now();
    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles, size);
    //grid entropy
    std::vector<int> grid_counts2(divisions*divisions,0);
    for (auto ball : balls){
        counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy = compute_entropy(grid_counts2, N_particles);

    auto t_end = std::chrono::steady_clock::now();

    //std::cout<< "Cálculo entropía inicial: " <<t_start-t_end<< std::endl;

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
        
        if (i==0) t_start = std::chrono::steady_clock::now();
        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy += ds;
        if (i==t_final-1){
            t_end = std::chrono::steady_clock::now();
            //std::cout<< "Cálculo total deltas entropía: " <<t_start-t_end<< std::endl;
            }

        // std::cout<<i<<"\t"<<entropy<<std::endl;
    }


    return std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count();
}

int main(int argc, char **argv) {
    //Declara variables
    int t_final = 1e6;
    int N_particles = 16;
    int divisions = 10000;
    int seed = 10;
    double size = 1001;
    double x_min, x_max, y_min, y_max;

    double meanTime;
    int times2Repeat = 1;


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
    auto t_start0 = std::chrono::steady_clock::now();
    std::vector<int> grid_counts2(divisions*divisions,0);
    auto t_end0 = std::chrono::steady_clock::now();
    
    auto t_start1 = std::chrono::steady_clock::now();
    for (auto ball : balls){
        counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy = compute_entropy(grid_counts2, N_particles);
    auto t_end1 = std::chrono::steady_clock::now();

    std::cout<< "Pidiendo memoria: "<<std::chrono::duration_cast<std::chrono::milliseconds>(t_end0-t_start0).count()<< std::endl;
    std::cout<< "Calculando entropía inicial: "<<std::chrono::duration_cast<std::chrono::milliseconds>(t_end1-t_start1).count()<< std::endl;

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
        
        if (i==0) {t_start0 = std::chrono::steady_clock::now();}
        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy += ds;
        if (i==t_final-1){
            t_end0 = std::chrono::steady_clock::now();
            std::cout<< "Cálculo total deltas entropía: "<<std::chrono::duration_cast<std::chrono::milliseconds>(t_end0-t_start0).count()<< std::endl;
            }

        // std::cout<<i<<"\t"<<entropy<<std::endl;
    }
    
    return 0;
}
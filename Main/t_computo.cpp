#include "utils.hpp"
#include <chrono>

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

int main(int argc, char *argv[]) {
    //Declara variables
    int t_final = 1e6;
    int N_particles = 100;
    int divisions = 10;
    int seed = 10;
    double size = 1001;
    double x_min, x_max, y_min, y_max;

    std::cout<< "Divs" <<"\t"<< "Time [ms]" <<std::endl;

    double meanTime;
    int times2Repeat = 5;

    // divisions es el que más afecta el tiempo
    for (divisions=5; divisions<size*100; divisions+=50){
        meanTime = 0.;
        for (int repeat=0; repeat<times2Repeat; repeat++){
            meanTime += simulation(t_final, N_particles, divisions, seed, size);
        }
        meanTime /= times2Repeat;
        std::cout<< divisions <<"\t"<< meanTime <<"\n";
    }

    // times2Repeat = 1;

    // Np afecta pero no mucho al tiempo
    // for (int N_particles_sqrt=40; N_particles_sqrt<1000; N_particles_sqrt+=10){
    //     meanTime = 0.;
    //     for (int repeat=0; repeat<times2Repeat; repeat++){
    //         meanTime += simulation(t_final, N_particles_sqrt*N_particles_sqrt, divisions, seed, size);
    //     }
    //     meanTime /= times2Repeat;
    //     std::cout<< N_particles_sqrt*N_particles_sqrt <<"\t"<< meanTime <<"\n";
    // }

    // Size no afecta casi nada del tiempo de cómputo
    // for (size=10; size<1e3; size+=10){
    //     meanTime = 0.;
    //     for (int repeat=0; repeat<times2Repeat; repeat++){
    //         meanTime += simulation(t_final, N_particles, divisions, seed, size);
    //     }
    //     meanTime /= times2Repeat;
    //     std::cout<< size <<"\t"<< meanTime <<"\n";
    // }

    return 0;
}
#include "utils.hpp"
#include <chrono>


template <typename T>
void print_elapsed(T start, T end, double size);


int main(int argc, char *argv[]) {
    //Declara variables
    int t_final = 1e6;
    int N_particles = 100; // Not relevant to compute time
    int divisions = 10;
    int seed = 10;

    double size = 100; // Grid size is irrelevant to compute time
    double x_min, x_max, y_min, y_max;

    std::cout<< "Divs" <<"\t"<< "Time [ms]" <<std::endl;

    auto t_start = std::chrono::steady_clock::now();
    auto t_end = std::chrono::steady_clock::now();

    // limites del contenedor
    x_min=-size/2;
    x_max=size/2;
    y_min=-size/2;
    y_max=size/2;

    // for (int N_particles_sqrt=40; N_particles_sqrt<100; N_particles_sqrt++){
    for (divisions=5; divisions<size*100; divisions+=50){
        // N_particles = N_particles_sqrt*N_particles_sqrt;

        t_start = std::chrono::steady_clock::now();

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

        t_end = std::chrono::steady_clock::now();

        print_elapsed(t_start, t_end, divisions);
    }


    return 0;
}

template <typename T>
void print_elapsed(T start, T end, double size)
{
  std::cout << size << "\t";
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
        << "\n";
}
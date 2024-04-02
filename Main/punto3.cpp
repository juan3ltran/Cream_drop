#include "utils.hpp"

int main(void){

    //Environment variables (size = 100)
    const int t_final = 6e+6, N_particles = 400, divisions = 8, seed = 42;    
    const double x_min = -100, x_max = 100, y_min = -100, y_max = 100;
    const double step = (x_max - x_min) / divisions;
    const double size = x_max - x_min;
    
    //Start writing 
    /*const std::string output_data_file_name = "rms_values.txt";
    std::ofstream outputFile(output_data_file_name);
    outputFile << std::fixed << std::setprecision(20);*/

    //Declare set of particles and random generator
    std::vector<Particle> balls;
    std::mt19937 gen(seed);

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles, size, 1);

    int coin = 0;
    const double max_size = std::sqrt(x_max-step);
    std::cout<< "time" << "\t" << "rms" << "\n";
    for (int i = 0; i < t_final; i++){
        double rms = rms_distance(balls);
        //stop simulation if rms is near to limit
        if(std::fabs(1-rms/57) < 0.005) break;
        if(i > 0){
            //outputFile << i << "\t" << rms << "\n";
            std::cout<< i << "\t" << rms << "\n";
        }
    
        coin = getRandomInt(N_particles, gen); //Selecciona que particula se movera
        balls[coin].moveRandom(step, x_min, x_max,  y_min,  y_max, gen); //Movimiento aleatorio
    }
    //outputFile.close();
    return EXIT_SUCCESS;
}
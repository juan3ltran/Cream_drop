#include "utils.hpp"
#include <unordered_map>

int main(void){

    //Environment variables (size = 100)
    const int t_final = 6e+6, N_particles = 400, divisions = 8, seed = 42;    
    const double x_min = -5, x_max = 5, y_min = -5, y_max = 5;
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
    const double max_drop = 3.555;
    double rms;
    double tol=0.02;
    std::cout<< "time" << "\t" << "rms" << "\t" << "entropia" << "\n";
    for (int i = 1; i < t_final; i++){
        
        coin = getRandomInt(N_particles-1, gen); //Selecciona que particula se movera
        balls[coin].moveRandom(0.125, x_min, x_max,  y_min,  y_max, gen); //Movimiento aleatorio
        if (i%5000==0)
        {
            std::unordered_map<int, int> entropyGrid; // 1: índice de la celda, 2: cantidad de partículas en esa celda
            for (auto ball : balls)
            {
                counts(entropyGrid, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
            }
            double entropy = compute_entropy(entropyGrid, N_particles);
            rms = rms_distance(balls);
            //stop simulation if rms is near to limit
            if(std::fabs(1-rms/max_drop) < tol) break;
            std::cout<< i << "\t" << rms << "\t" << entropy << "\n"; 
        } 
    }
    //outputFile.close();
    return EXIT_SUCCESS;
}
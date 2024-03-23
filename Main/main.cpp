#include "utils.hpp"


int main() {
    //Crea los archivos que resuelven cada punto
    std::ofstream entropia ("./data/punto1.dat");
    std::vector<Particle> balls;
    //Configuracion de parametros
    const int t_final = 6000000;
    const int N_particles = 400;
    const double x_min = -10, x_max = 10;
    const double y_min = -10, y_max = 10;
    const int divisions = 8;
    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles);
    //grid entropy
    std::vector<int> grid_counts2(divisions*divisions,0);
    for (auto ball : balls){
        counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy2 = compute_entropy(grid_counts2, N_particles);
   
    int coin;
    for (int i = 0; i < t_final; i++)
    {
        
        coin = getRandomInt(N_particles-1); //Selecciona que particula se movera
        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        double old_x = balls[coin].getX();
        double old_y = balls[coin].getY();
        balls[coin].moveRandom(0.1, x_min, x_max, y_min, y_max);        
        
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        double new_x = balls[coin].getX();
        double new_y = balls[coin].getY();
        
        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy2 += ds;

        entropia<<i<<"\t"<<entropy2<<std::endl;
       
        
    }
    entropia.close();
    return 0;
}
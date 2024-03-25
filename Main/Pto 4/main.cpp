#include "utils.hpp"
#include <iostream>


int main() {
    //Crea los archivos que resuelven cada punto
    std::vector<Particle> balls;

    //Configuracion de parametros
    const int t_final = 100;
    const int N_particles = 4;
    const double x_min = -20, x_max = 20;
    const double y_min = -20, y_max = 20;
    const int divisions = 8;

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles);
    // //grid entropy
    // std::vector<int> grid_counts2(divisions*divisions,0);
    // for (auto ball : balls){
    //     counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    // }
    // double entropy = compute_entropy(grid_counts2, N_particles);
   
    int coin;

    double holeLength = 20.;
    std::vector<double> holeinWall = {(x_max-x_min)/2. - holeLength, y_max, holeLength}; // x, y, length


    for (int i = 0; i < t_final; i++)
    {   
        coin = getRandomInt(N_particles-1); //Selecciona que particula se movera
        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        // double old_x = balls[coin].getX();
        // double old_y = balls[coin].getY();

        balls[coin].moveRandom2(5., x_min, x_max, y_min, y_max);

        // if ( hasGoneOut(balls[coin], holeinWall) ){
        //     // std::cout<<"Outtttttttttttt"<<std::endl;
        //     balls.erase(balls.begin() + coin);
        // }

        for (auto ball : balls){
            std::cout<< ball.getX() <<","<< ball.getY() <<",";
        }
        std::cout<<"0"<<std::endl;
    }

    return 0;
}
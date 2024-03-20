#include "utils.hpp"


int main() {

    std::vector<Particle> balls;
    //Configuracion de parametros
    int t_final = 1000000;
    int N_particles = 400;
    double x_min = -10, x_max = 10;
    double y_min = -10, y_max = 10;

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles);
    
    int coin;
    for (int i = 0; i < t_final; i++)
    {
        coin = getRandomInt(N_particles-1); //Selecciona que particula se movera
 
        balls[coin].moveRandom(0.1, x_min, x_max, y_min, y_max);
        
        if (i==t_final-1) //Imprime la posicion final de todas las particulas
        {
            for (auto& ball : balls)
            {
                std::cout << ball.getX()<<'\t'<< ball.getY()<<std::endl;
            }
        }           
    }
    return 0;
}
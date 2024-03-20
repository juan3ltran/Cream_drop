#include "utils.hpp"


int main() {

    std::vector<Particle> balls;
    //Configuracion de parametros
    const int t_final = 100;
    const int N_particles = 50;
    const double x_min = -10, x_max = 10;
    const double y_min = -10, y_max = 10;
    const int divisions = 8;
    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles);
    //grid entropy
    //////////////////////////////////////////
    std::vector<std::vector<int>> grid_counts1(divisions, std::vector<int>(divisions, 0.0));
    std::vector<std::vector<int>> grid_counts2(divisions, std::vector<int>(divisions, 0.0));
    for (auto ball : balls){
        counts(grid_counts1, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
        counts(grid_counts2, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }
    double entropy1 = compute_entropy(grid_counts1, N_particles);
    double entropy2 = compute_entropy(grid_counts2, N_particles);
    /////////////////////////////
    int coin;
    for (int i = 0; i < t_final; i++)
    {
        
        coin = getRandomInt(N_particles-1); //Selecciona que particula se movera
        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        double old_x = balls[coin].getX();
        double old_y = balls[coin].getY();
        balls[coin].moveRandom(0.1, x_min, x_max, y_min, y_max);        
        ///////////////////////////////////////////
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        double new_x = balls[coin].getX();
        double new_y = balls[coin].getY();
        
        //grid_counts1 en 0 para evitar sobreconteo
        for (int ix = 0; ix < divisions; ix++) 
        {
            std::fill(grid_counts1[ix].begin(), grid_counts1[ix].end(), 0.0);
        }

        for (auto& ball : balls)
        {
            //Posicion de Particula iesima (ball.getX(),ball.getY())

            //Conteo de particula en la subdivision
            counts(grid_counts1, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
        }        
        entropy1 = compute_entropy(grid_counts1, N_particles);

        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy2 += ds;

        std::cout<<entropy1<<"\t"<<entropy2<<std::endl;
        //////////////////////////////////////////////////
        
    }
    return 0;
}
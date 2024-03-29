#include "utils.hpp"


int simulacion(int t_final, int N_particles, double mitad_lado, int divisions, int seed) {

    //Calculo del tiempo de equilibrio para multiples tamaños
    std::mt19937 gen(seed);
    std::vector<Particle> balls;
    //Configuracion de parametros
    const double x_min = -mitad_lado, x_max = mitad_lado;
    const double y_min = -mitad_lado, y_max = mitad_lado;

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(balls, N_particles);
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
        balls[coin].moveRandom(0.125, x_min, x_max, y_min, y_max, gen);        
        
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        double new_x = balls[coin].getX();
        double new_y = balls[coin].getY();
        
        // %%%%%%%%%%%%% Calcula el cambio en la entropia (2 casos) %%%%%%%%%%%%%
        double ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy += ds;

        //%%%%%%%%%%%%% Comprobacion del equilibrio %%%%%%%%%%%%%
        double tol = 0.03;
        double equilibrio = log(divisions*divisions);

        //para evitar comprobarlo en cada intante de tiempo
        if ((i%500 == 0) && (std::fabs(entropy/equilibrio-1) < tol)) 
        {
            //std::cout<<"Error relativo: "<<std::fabs(entropy/equilibrio-1)<<std::endl;
            return i;
        }
    }
    return 1;
}

int main()
{
    int tiempo_final;
    const int t_final = 6e6;
    const int N_particles = 400;
    const int divisiones = 8;
    const int seed = 0;

    std::cout<<"size"<<"\t"<<"equilibrio"<<std::endl;

    // Variando el tamaño para diferentes valores de mitad_lado
    for (double i = 1.5 ; i < 20; i+=0.5)
    {
        tiempo_final = simulacion(t_final, N_particles, i, divisiones, seed);
        std::cout<<i*2<<"\t"<<tiempo_final<<std::endl;
    }
    return 0;
}
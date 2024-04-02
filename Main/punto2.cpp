#include "utils.hpp"
#include <unordered_map>

int simulacion(int t_final, int N_particles, double size, int divisions, int seed) {

    //Calculo del tiempo de equilibrio para multiples tamaños

    std::mt19937 gen(seed);
    std::vector<Particle> balls;
    
    //Configuracion de parametros
    const double x_min = -size/2, x_max = size/2;
    const double y_min = -size/2, y_max = size/2;

    // Inicializa n objetos de la clase Particle y los añade al vector, todos empiezan en el centro
    inicializar(balls, N_particles, size, true); // ####################### TRUE ####################33
    //entropy grid
    std::unordered_map<int, int> entropyGrid; // 1: índice de la celda, 2: cantidad de partículas en esa celda

    for (auto ball : balls){
        counts(entropyGrid, ball.getX(), ball.getY(), x_min, x_max, y_min, y_max, divisions);
    }

    double entropy = compute_entropy(entropyGrid, N_particles);
    
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
        double ds = delta_entropy(entropyGrid, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        // std::cout<<entropyGrid[36]<<std::endl;
        entropy += ds;

        //%%%%%%%%%%%%% Comprobacion del equilibrio %%%%%%%%%%%%%
        double tol = 0.03;
        double equilibrio = log(divisions*divisions);

        //para evitar comprobarlo en cada intante de tiempo
        if ((i%1024 == 0) && (std::fabs(entropy/equilibrio-1) < tol)) 
        {
            double rms = rms_distance(balls);
            std::cout<<entropy<<'\t'<<rms<<'\t';
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

    std::cout<<"entropia"<<"\t"<<"rms"<<"\t"<<"size"<<"\t"<<"equilibrio"<<std::endl;

    // Variando el tamaño para diferentes valores de mitad_lado
    for (double i = 3 ; i < 30; i+=0.2)
    {
        tiempo_final = simulacion(t_final, N_particles, i, divisiones, seed);
        //Multiplicacion por 2 para tener la longitud de un lado 
        std::cout<<i<<"\t"<<tiempo_final<<std::endl;
    }
    return 0;
}
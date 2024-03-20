#include "utils.hpp"

//Implementación de funciones
int getRandomInt(int max) {
    static std::mt19937 gen(18);
    std::uniform_int_distribution<int> dist_(0, max);
    return dist_(gen);
}

void inicializar(std::vector<Particle> &balls, int N_particles){
    for (int i = 0; i < N_particles; ++i) {
        balls.emplace_back(0, 0); // Cada partícula inicia en (0,0)
    }
    // Se genera el cuadrado inicial
    int square_size = std::sqrt(N_particles);
    for (int i; i< balls.size();){
        for(double ix=0; ix < square_size; ix++){
            for (double iy=0; iy < square_size; iy++){
                balls[i].setX(ix/10 - square_size/20);
                balls[i].setY(iy/10 - square_size/20);
                i++;
            }
        }           
    }
}
//Funciones de entropía

double compute_entropy(std::vector<std::vector<int>>& particle_counts, int N_particles)
{
    // Calcula la entropía
    double entropy = 0.0;
    int divisions = particle_counts.size();

    for (int ix = 0; ix < divisions; ++ix) {
        for (int iy = 0; iy < divisions; ++iy) {
            if (particle_counts[ix][iy] > 0) {
                double p = double(particle_counts[ix][iy]) / N_particles;
                entropy -= p * std::log(p);
            }
        }
    }
    return entropy;
}

void counts(std::vector<std::vector<int>>& particle_counts, double x, double y, double x_min, 
double x_max, double y_min, double y_max, int divisions)
{
    //Compute the size of each subdivision
    double x_step = (x_max - x_min) / divisions;
    double y_step = (y_max - y_min) / divisions;

    //Verifica la posicion dentro de los limites
        if ((x_min < x) && (x < x_max) && (y_min < y) && (y < y_max))
        {
            // Calcula el índice de la subdivisión para x e y
            int ix = int((x - x_min) / x_step);
            int iy = int((y - y_min) / y_step);

            // Incrementa el contador para esa subdivisión
            particle_counts[ix][iy]++;
        }
}





//Implementación de la clase Particle

Particle::Particle(double initialX, double initialY): x(initialX), y(initialY){}

double Particle::getX() const{
    return x;
}

double Particle::getY() const{
    return y;
}

void Particle::setX(double newX){
    x=newX;
}

void Particle::setY(double newY){
    y=newY;
}

void Particle::move(double dx, double dy){
    x+=dx;
    y+=dy;
}

void Particle::moveRandom(double delta, double x_min, double x_max, double y_min, double y_max){
    std::vector<std::pair<double, double>> possibleMoves;

    // Agrega movimientos posibles teniendo en cuenta los límites
    if (x > x_min) possibleMoves.emplace_back(-delta, 0); // Izquierda
    if (x < x_max) possibleMoves.emplace_back(delta, 0); // Derecha
    if (y > y_min) possibleMoves.emplace_back(0, -delta); // Arriba
    if (y < y_max) possibleMoves.emplace_back(0, delta); // Abajo
    if (x > x_min && y > y_min) possibleMoves.emplace_back(-delta, -delta); // Diagonal superior izquierda
    if (x > x_min && y < y_max) possibleMoves.emplace_back(-delta, delta); // Diagonal inferior izquierda
    if (x < x_max && y > y_min) possibleMoves.emplace_back(delta, -delta); // Diagonal superior derecha
    if (x < x_max && y < y_max) possibleMoves.emplace_back(delta, delta); // Diagonal inferior derecha

    if (!possibleMoves.empty()) {
        int index = getRandomInt(possibleMoves.size() - 1);
        move(possibleMoves[index].first, possibleMoves[index].second);
    }
}

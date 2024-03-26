#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include "entropia_h.hpp"

int getRandomInt(int max);
template<class T>
double rms_distance(const std::vector<T> &walkers);

class Particle {
private:
    double x, y;
public:
    // Constructor para inicializar x e y.
    Particle(double initialX, double initialY) : x(initialX), y(initialY) {}

    // Getters para x e y.
    double getX() const { return x; }
    double getY() const { return y; }

    // Setters para x e y.
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    // Función move para cambiar x e y.
    // Agrega deltaX a x y deltaY a y.
    void move(double dx, double dy) {
        x += dx;
        y += dy;
    }

    // Nuevo método para mover la posición aleatoriamente
    void moveRandom(double delta, double x_min, double x_max, double y_min, double y_max) {
        std::vector<std::pair<double, double>> possibleMoves;

        // Agrega movimientos posibles teniendo en cuenta los límites
        if (x > (x_min+delta)) possibleMoves.emplace_back(-delta, 0); // Izquierda
        if (x < (x_max-delta)) possibleMoves.emplace_back(delta, 0); // Derecha
        if (y > (y_min+delta)) possibleMoves.emplace_back(0, -delta); // Arriba
        if (y < (y_max-delta)) possibleMoves.emplace_back(0, delta); // Abajo
        if (x > (x_min+delta) && y > (y_min+delta)) possibleMoves.emplace_back(-delta, -delta); // Diagonal superior izquierda
        if (x > (x_min+delta) && y < (y_max-delta)) possibleMoves.emplace_back(-delta, delta); // Diagonal inferior izquierda
        if (x < (x_max-delta) && y > (y_min+delta)) possibleMoves.emplace_back(delta, -delta); // Diagonal superior derecha
        if (x < (x_max-delta) && y < (y_max-delta)) possibleMoves.emplace_back(delta, delta); // Diagonal inferior derecha

        if (!possibleMoves.empty()) {
            int index = getRandomInt(possibleMoves.size() - 1);
            move(possibleMoves[index].first, possibleMoves[index].second);
        }
    }
};

int main(int argc, char **argv) {

    std::vector<Particle> balls;
    //Configuracion de parametros
    const int t_final = 1e+2;
    const int N_particles = 100;
    const double x_min = -5, x_max = 5;
    const double y_min = -5, y_max = 5;
    const int divisions = 8;

    const std::string output_data_file_name = "rms_values.txt";
    std::ofstream outputFile(output_data_file_name);
    outputFile << std::fixed << std::setprecision(20);

    // Inicializa N objetos de la clase Particle y los añade al vector
    for (int i = 0; i < N_particles; ++i) {
        balls.emplace_back(0, 0); // Cada partícula inicia en (0,0)
        
    }
    
    int coin = 0;
    double old_x = 0.0, old_y = 0.0, new_x = 0.0, new_y = 0.0;

    for (int i = 0; i < t_final; i++)
    {
        double rms = rms_distance(balls);
        const double max_size = 2.0;
        //stop simulation if rms is near to limit
        if(std::fabs(1-rms/max_size) < 0.007) break;

        if(i > 0){
            outputFile << i << "\t" << rms << "\n";
        }
        
        coin = getRandomInt(N_particles-1); //Selecciona que particula se movera

        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        old_x = balls[coin].getX();
        old_y = balls[coin].getY();
 
        balls[coin].moveRandom(0.5, x_min, x_max, y_min, y_max); //Movimiento aleatorio
        
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        new_x = balls[coin].getX();
        new_y = balls[coin].getY();

    }
    outputFile.close();

    return 0;
}


int getRandomInt(int max) {
    static std::mt19937 gen(18);
    std::uniform_int_distribution<int> dist_(0, max);
    return dist_(gen);
}
template<class T>
double rms_distance(const std::vector<T> &walkers){
    double square_sum = 0.0;
    for(const Particle walker : walkers){
        double x = 0.0, y = 0.0, norm = 0.0;
        x = walker.getX();
        y = walker.getY();
        norm = std::sqrt((x*x)+(y*y));
        square_sum += norm;
    }

    return std::sqrt(square_sum/walkers.size());
}
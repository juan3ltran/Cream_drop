#include <iostream>
#include <random>
#include <vector>


int getRandomInt(int max);

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
};

int main() {

    std::vector<Particle> balls;
    //Configuracion de parametros
    int t_final = 100000;
    int N_particles = 100;
    double x_min = -10, x_max = 10;
    double y_min = -10, y_max = 10;

    // Inicializa n objetos de la clase Particle y los añade al vector
    for (int i = 0; i < N_particles; ++i) {
        balls.emplace_back(0, 0); // Cada partícula inicia en (0,0)
    }
    
    std::cout << 'x'<<'\t'<< 'y'<<std::endl;

    int coin;
    /*/double entropy = delta_entropy(old_x, old_y, N_particles, x_min, x_max, y_min, y_max, divisions); */
    for (int i = 0; i < t_final; i++)
    {
        coin = getRandomInt(N_particles); //Selecciona que particula se movera
 
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


int getRandomInt(int max) {
    static std::mt19937 gen(18);
    std::uniform_int_distribution<int> dist_(0, max);
    return dist_(gen);
}
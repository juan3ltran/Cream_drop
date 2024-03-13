#include <iostream>
#include <random>


double getRandomInt(int max);

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
        std::vector<std::pair<int, int>> possibleMoves;

        // Agrega movimientos posibles teniendo en cuenta los límites
        if (x > x_min) possibleMoves.emplace_back(-delta, 0); // Izquierda
        if (x < x_max) possibleMoves.emplace_back(delta, 0); // Derecha
        if (y > y_min) possibleMoves.emplace_back(0, -delta); // Arriba
        if (y < y_max) possibleMoves.emplace_back(0, delta); // Abajo
        if (x > x_min && y > y_min) possibleMoves.emplace_back(-delta, -delta); // Diagonal superior izquierda
        if (x > 0 && y < y_max) possibleMoves.emplace_back(-delta, delta); // Diagonal inferior izquierda
        if (x < x_max && y > y_min) possibleMoves.emplace_back(delta, -delta); // Diagonal superior derecha
        if (x < x_max && y < y_max) possibleMoves.emplace_back(delta, delta); // Diagonal inferior derecha

        if (!possibleMoves.empty()) {
            int index = getRandomInt(possibleMoves.size() - 1);
            move(possibleMoves[index].first, possibleMoves[index].second);
        }
    }
};

int main() {
    Particle ball(0, 0); // Inicia en (0,0).
    
    std::cout << 'x'<<'\t'<< 'y'<<std::endl;
    for (int i = 0; i < 500; i++)
    {
        
        std::cout << ball.getX()<<'\t'<< ball.getY()<<std::endl;
        ball.moveRandom(1, -10, 10,-5, 5);
    }

    return 0;
}


double getRandomInt(int max) {
    static std::mt19937 gen(18);
    std::uniform_int_distribution<int> dist_(0, max);

    return dist_(gen);
}
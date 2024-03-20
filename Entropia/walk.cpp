#include <iostream>
#include <random>
#include <vector>
#include "entropia_h.hpp"

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

int main(int argc, char **argv) {

    std::vector<Particle> balls;
    //Configuracion de parametros
    const int t_final = 21;
    const  int N_particles = 5;
    const double x_min = -5, x_max = 5;
    const double y_min = -5, y_max = 5;
    const int divisions = 8 ;


    ////%%%%%%%%%%%%% Inizializacion de la grid_entropy %%%%%%%%%%%%%
    std::vector<std::vector<int>> grid_counts1(divisions, std::vector<int>(divisions, 0.0));
    std::vector<std::vector<int>> grid_counts2(divisions, std::vector<int>(divisions, 0.0));

    // Inicializa N objetos de la clase Particle y los añade al vector
    for (int i = 0; i < N_particles; ++i) {

        balls.emplace_back(0, 0); // Cada partícula inicia en (0,0)
        
        //%%%%%%%%%%%%% Conteo de esa particula en la grid_entropy %%%%%%%%%%%%%
        counts(grid_counts1, 0, 0, x_min, x_max, y_min, y_max, divisions);
        counts(grid_counts2, 0, 0, x_min, x_max, y_min, y_max, divisions);
    }
    
    // %%%%%%%%%%%%% Valor inicial de entropia %%%%%%%%%%%%%
    double entropy1 = compute_entropy(grid_counts1, N_particles);
    double entropy2 = compute_entropy(grid_counts2, N_particles);


    //std::cout << 'x'<<'\t'<< 'y'<<std::endl;
    std::cout << 't'<<'\t'<< "entropia1"<<'\t'<< "entropia2"<<'\t'<< "deltaentropy"<<'\t'<< "old_x"<<'\t'<< "old_y"<<'\t'<< "new_x"<<'\t'<< "new_y"<<'\t'<< "grid[3][3]"<<'\t'<< "grid[3][4]"<<'\t'<< "grid[4][3]"<<'\t'<< "grid[4][4]"<<std::endl;
    std::cout << 0.0 <<'\t'<< entropy1<<'\t'<< entropy2<<'\t'<< 0.0<<std::endl;

    int coin;
    double old_x, old_y, new_x, new_y, ds=0;

    for (int i = 0; i < t_final; i++)
    {
        

        coin = getRandomInt(N_particles-1); //Selecciona que particula se movera

        // %%%%%%%%%%%%% Posicion antigua %%%%%%%%%%%%%
        old_x = balls[coin].getX();
        old_y = balls[coin].getY();
 
        balls[coin].moveRandom(0.125, x_min, x_max, y_min, y_max); //Movimiento aleatorio
        
        // %%%%%%%%%%%%% Posicion actual %%%%%%%%%%%%%
        new_x = balls[coin].getX();
        new_y = balls[coin].getY();
        
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
        ds = delta_entropy(grid_counts2, new_x, new_y, x_min, x_max, y_min, y_max, divisions, old_x, old_y, N_particles);
        entropy2 += ds;

        std::cout << i+1 <<'\t'<< entropy1<<'\t'<< entropy2<<'\t'<< ds<<'\t'<< old_x<<'\t'<< old_y<<'\t'<< new_x<<'\t'<< new_y<<'\t'<< grid_counts1[3][3]<<'\t'<< grid_counts1[3][4]<<'\t'<< grid_counts1[4][3]<<'\t'<< grid_counts1[4][4]<<std::endl;
        

        // %%%%%%%%%%%%% Output para las posiciones finales de las particulas %%%%%%%%%%%%%
        /*if (i==t_final-1) //Imprime la posicion final de todas las particulas
        {
            for (auto& ball : balls)
            {
                std::cout << ball.getX()<<'\t'<< ball.getY()<<std::endl;
            }
        }*/
            
    }

    return 0;
}


int getRandomInt(int max) {
    static std::mt19937 gen(18);
    std::uniform_int_distribution<int> dist_(0, max);
    return dist_(gen);
}
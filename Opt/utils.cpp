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
    if(square_size*square_size != balls.size()){throw std::logic_error(" \n  Number of particles does not form a perfect square.\n");}    
    int i=0;
    for(double ix=0; ix < square_size; ix++){
        for (double iy=0; iy < square_size; iy++){            
            balls[i].setX(ix/10 - square_size/20);
            balls[i].setY(iy/10 - square_size/20);
            i++;
        }
    }           
}

//Funciones de entropía

double compute_entropy(std::vector<int>& particle_counts, int N_particles)
{
    // Calcula la entropía
    double entropy = 0.0;
    int divisions = std::sqrt(particle_counts.size());

    for (int ix = 0; ix < divisions; ++ix) {
        for (int iy = 0; iy < divisions; ++iy) {
            if (particle_counts[ix*divisions + iy] > 0) {
                double p = double(particle_counts[ix*divisions + iy]) / N_particles;
                entropy -= p * std::log(p);
            }
        }
    }
    return entropy;
}

void counts(std::vector<int>& grid_counts, double x, double y, 
            double x_min, double x_max, double y_min, double y_max, int divisions)
{
    //Calcula el tamaño de cada subdivision en terminos de las coordenadas de posicion
    double x_step = (x_max - x_min) / static_cast<double>(divisions);
    double y_step = (y_max - y_min) / static_cast<double>(divisions);

    //Verifica la posicion dentro de los limites
        if ((x_min <= x) && (x <= x_max) && (y_min <= y) && (y <= y_max))
        {
            // Calcula el índice de la subdivisión para x e y
            int ix = int((x - x_min) / x_step);
            int iy = int((y - y_min) / y_step);

            // Incrementa el contador para esa subdivisión
            grid_counts[ix*divisions + iy]++;
        }
}


double delta_entropy(std::vector<int>& grid_counts, double new_x, double new_y, 
                    double x_min, double x_max, double y_min, double y_max, int divisions, double old_x, double old_y, int N_particles)
{
    //Calcula el cambio en la entropia teniendo en cuenta la subdivision de donde sale y a que llega una particula

    double x_step = (x_max - x_min) / divisions;
    double y_step = (y_max - y_min) / divisions;

    int old_ix = int((old_x - x_min) / x_step); //Indices de la subdivision con la posicion anterior (origen)
    int old_iy = int((old_y - y_min) / y_step);

    int new_ix = int((new_x - x_min) / x_step); //Indices de la subdivision con la posicion actual (destino)
    int new_iy = int((new_y - y_min) / y_step);

    if ((old_ix == new_ix) && (old_iy == new_iy))
    {
        //Si la particula no cambio de subdivision entonces la entropia no cambio
        return 0.0;
    }
    else //la particula cambio de subdivision por lo que se calcula los terminos de probabilidad antes y despues del cambio 
    {
        double old_p1 = double(grid_counts[old_ix*divisions + old_iy]) / N_particles; //probabilidad antigua de la subdivision 1 (origen)
        double old_p2 = double(grid_counts[new_ix*divisions + new_iy]) / N_particles; //probabilidad antigua de la subdivision 2 (destino)

        // Ajusta el contador para la subdivision donde estaba la particula y a la cual llego
        grid_counts[new_ix*divisions + new_iy]++;
        grid_counts[old_ix*divisions + old_iy]--;
        

        double new_p1 = double(grid_counts[old_ix*divisions + old_iy]) / N_particles; //probabilidad nueva de la subdivision 1 (origen)
        double new_p2 = double(grid_counts[new_ix*divisions + new_iy]) / N_particles; //probabilidad nueva de la subdivision 2 (destino)

        double ds = 0;
        //old_p1*log(old_p1)-new_p1*log(new_p1) + old_p2*log(old_p2)-new_p2*log(new_p2); //Cambio en la entropia 
        if (old_p1!=0){ds+=old_p1*log(old_p1);}
        if (new_p1!=0){ds-=new_p1*log(new_p1);}
        if (old_p2!=0){ds+=old_p2*log(old_p2);}
        if (new_p2!=0){ds-=new_p2*log(new_p2);}
        return ds;
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

// Otra función para el mov de las partículas
void Particle::moveRandom2(double delta, double x_min, double x_max, double y_min, double y_max){
    
        std::vector<double> possibleMoves = {-delta, 0.0, delta};

        // Se inicializan valores fuera de límites para garantizar que se haga el while de abajo
        double newX = x_min - delta*2;
        double newY = y_min - delta*2;

        // Se hará este ciclo hasta que se encuentre una nueva posición válida para la partícula
        // Siempre habrá un movimiento posible (mínimo 3 creo)
        while (newX < x_min || newX > x_max || newY < y_min || newY > y_max){
            int index0 = getRandomInt(possibleMoves.size() - 1);
            int index1 = getRandomInt(possibleMoves.size() - 1);
            newX = x + possibleMoves[index0];
            newY = y + possibleMoves[index1];
        }

        // Se actualiza la posición
        setX(newX); setY(newY);
}


#include "utils.hpp"

//Implementación de funciones
int getRandomInt(int max, std::mt19937& gen, bool positive) {
    if (positive)
    {
        std::uniform_int_distribution<int> dist_(0, max);
        return dist_(gen);
    }
    else
    {
        std::uniform_int_distribution<int> dist_(-max, max);
        return dist_(gen);
    }
    
}

void inicializar(std::vector<Particle> &balls, int N_particles, double Size, bool initCenter){
    for (int i = 0; i < N_particles; ++i) {
        balls.emplace_back(0, 0); // Cada partícula inicia en (0,0)
    }

    // Si se quiere que empiecen en el centro, se salta esto, si no, sigue
    if (!initCenter){
        // Se genera el cuadrado inicial
        if(std::sqrt(N_particles) > Size){throw std::logic_error(" \n Particles can't fit in the container, increase its size or decrease number of particles.\n");}
        int square_size = std::sqrt(N_particles);
        if(square_size*square_size != balls.size()){throw std::logic_error(" \n  Number of particles does not form a perfect square.\n");}

        int i=0;
        for(double ix=0; ix < square_size; ix++){
            for (double iy=0; iy < square_size; iy++){            
                balls[i].setX(ix - square_size/2);
                balls[i].setY(iy - square_size/2);
                // std::cout<< balls[i].getX() <<","<< balls[i].getY() <<std::endl;
                i++;
            }
        }     
    }      
}

//Calcula la distancia RMS de las particulas desde el origen
double rms_distance(const std::vector<Particle> &walkers){
    double square_sum = 0.0;
    double x = 0.0, y = 0.0, norm = 0.0;
    for(const Particle walker : walkers){
        x = walker.getX();
        y = walker.getY();
        norm = (x*x)+(y*y);
        square_sum += norm;
    }

    return std::sqrt(square_sum/walkers.size());
}

//Funciones de entropía


void counts(std::unordered_map<int,int>& entropyGrid, double x, double y, 
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

            // Se suma uno a ese índice (esa celda)
            entropyGrid[ix*divisions + iy]++;
        }
}

double compute_entropy(std::unordered_map<int, int>& entropyGrid, int N_particles)
{
    // Calcula la entropía
    double entropy = 0.0;

    for (const auto& pair : entropyGrid) {
        double p = double(pair.second) / N_particles;
        entropy -= p * std::log(p);
    }

    return entropy;
}


double delta_entropy(std::unordered_map<int, int>& entropyGrid, double new_x, double new_y, 
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
        double old_p1 = double(entropyGrid[old_ix*divisions + old_iy]) / N_particles; //probabilidad antigua de la subdivision 1 (origen)
        double old_p2 = double(entropyGrid[new_ix*divisions + new_iy]) / N_particles; //probabilidad antigua de la subdivision 2 (destino) Si el índice no está en el mapa, su valor es 0 por default

        // Ajusta el contador para la subdivision donde estaba la particula y a la cual llego
        entropyGrid[new_ix*divisions + new_iy]++;
        entropyGrid[old_ix*divisions + old_iy]--;
        

        double new_p1 = double(entropyGrid[old_ix*divisions + old_iy]) / N_particles; //probabilidad nueva de la subdivision 1 (origen)
        double new_p2 = double(entropyGrid[new_ix*divisions + new_iy]) / N_particles; //probabilidad nueva de la subdivision 2 (destino)

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

// Otra función para el mov de las partículas
void Particle::moveRandom(double delta, double x_min, double x_max, double y_min, double y_max, std::mt19937& gen){
    
        std::vector<double> possibleMoves = {-delta, 0.0, delta};

        // Se inicializan valores fuera de límites para garantizar que se haga el while de abajo
        double newX = x_min - delta*2;
        double newY = y_min - delta*2;

        // Se hará este ciclo hasta que se encuentre una nueva posición válida para la partícula
        // Siempre habrá un movimiento posible (mínimo 3 creo)
        while (newX <= x_min || newX >= x_max || newY <= y_min || newY >= y_max){
            int index0 = getRandomInt(possibleMoves.size() - 1, gen);
            int index1 = getRandomInt(possibleMoves.size() - 1, gen);
            newX = x + possibleMoves[index0];
            newY = y + possibleMoves[index1];
        }

        // Se actualiza la posición
        setX(newX); setY(newY);
}


// Función para mover las partículas. Devuelve el estado de la partícula (0: dentro, 1: salió por el hueco)
int Particle::moveRandomwHole(double delta, double x_min, double x_max, double y_min, double y_max, std::vector<double> holeinWall, std::mt19937& gen){

    std::vector<double> possibleMoves = {-delta, 0.0, delta};
    double newX;
    double newY;

    while (true){
        // Escoge aleatoriamente alguna dirección
        int index0 = getRandomInt(possibleMoves.size() - 1, gen);
        int index1 = getRandomInt(possibleMoves.size() - 1, gen);
        newX = x + possibleMoves[index0];
        newY = y + possibleMoves[index1];

        // Se ve primero si salió por el hueco
        if ( goneThroughWhole(newX, newY, holeinWall, delta) ){
            return 1; // devuelve status 1 para saber que salió
        }
        // Si no, se ve si intenta salir por alguna pared
        else if (newX < x_min || newX > x_max || newY < y_min || newY > y_max){
            continue;
        }
        // Si tampoco, movimiento válido
        else{
            // Se actualiza la posición
            setX(newX); setY(newY);
            return 0; // devuelve status 0 para saber que no salió
        }
    }
}

// Determina si la partícula salió por el hueco
bool goneThroughWhole(double x, double y, std::vector<double> holeinWall, double delta){
    return (x > holeinWall[0]-delta && x < holeinWall[0]+delta + holeinWall[2] && y > holeinWall[1]);
    // Se suma el delta para tener en cuenta los casos en los que la partícula esté cerca al hueco y salga en diagonal
}


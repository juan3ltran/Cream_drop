#include "utils.hpp"
#include <iostream>


int main() {
    std::vector<Particle> particles;

    //Configuracion de parametros
    const int N_particles = 100;
    const double containerSize = 50;
    double holeLength = 10.;
    int seed = 1;

    std::mt19937 gen(seed);

    // Se definen los límites usando el tamaño del contenedor (dx=1)
    const double x_min = -containerSize/2., x_max = containerSize/2.;
    const double y_min = -containerSize/2., y_max = containerSize/2.;

    // Inicializa n objetos de la clase Particle y los añade al vector
    inicializar(particles, N_particles);

    // Parámetros del hueco (creo que toda la implementación es dependiente de que el hueco esté en la pared de arriba, se podría hacer más general hm)
    std::vector<double> holeinWall = {-holeLength/2., y_max, holeLength}; // x, y, length

    int choice;
    int t=-1;
    while (true){
        t++; // paso de tiempo

        // Se detiene cuando ya no hayan partículas
        if (particles.size() < 1){
            break;
        }

        choice = getRandomInt(N_particles-1, gen); //Selecciona qué particula se moverá, escoge entre las iniciales

        // std::cout<<choice<<std::endl;

        // Verifica que la partícula escogida no sea una que ya salió, si sí, hace otro ciclo
        if (choice > particles.size()-1){
            // Imprime la cantidad de partículas en este paso de tiempo
            std::cout<< particles.size() <<std::endl;
            continue;
        }

        // Mueve la partícula, y devuelve su estado (0 si sigue dentro, 1 si salió por el hueco)
        int status = particles[choice].moveRandomwHole(1., x_min, x_max, y_min, y_max, holeinWall, gen);

        // Si la partícula salió, la elimina del vector de partículas
        if (status==1){
            particles.erase(particles.begin() + choice);
        }

        // Imprime la cantidad de partículas en este paso de tiempo
        std::cout<< particles.size() <<std::endl;

        // Por si se quiere graficar
        // for (int i=0; i<N_particles; i++){
        //     if (i>=particles.size()){
        //        std::cout<< 0 <<","<< 0 <<",";
        //     }
        //     else{
        //        std::cout<< particles[i].getX() <<","<< particles[i].getY() <<",";
        //     }
        // }
        // std::cout<<"0"<<std::endl; // Dummy value

    }

    return 0;
}
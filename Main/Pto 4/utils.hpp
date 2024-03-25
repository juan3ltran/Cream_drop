#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>

//Clases necesarias
class Particle{
    
private:
    double x, y;
    
public:
    //constructor
    Particle(double initialX, double initialY);

    //Getters para x e y
    double getX() const;
    double getY() const;

    //Setters para x e y
    void setX(double newX);
    void setY(double newY);

    //Desplazamiento
    void move(double dx, double dy);
    int moveRandom(double delta, double x_min, double x_max, double y_min, double y_max, std::vector<double> holeinWall);
};

//Funciones Necesarias
int getRandomInt(int max);

//Funciones para Calcular entropía
void counts(std::vector<int>& grid_counts, double x, double y, double x_min, double x_max, double y_min, double y_max, int divisions);

double compute_entropy(std::vector<int>& particle_counts, int N_particles);

double delta_entropy(std::vector<int>& grid_counts, double new_x, double new_y, double x_min, double x_max, double y_min, double y_max, int divisions, double old_x, double old_y, int N_particles);
//Funcion para inicializar el cuadrado

void inicializar(std::vector<Particle> &balls, int N_particles);

bool goneThroughWhole(double x, double y, std::vector<double> holeinWall);
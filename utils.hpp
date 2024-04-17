#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <unordered_map>
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
    void moveRandom(double delta, double x_min, double x_max, double y_min, double y_max, std::mt19937& gen);
    int moveRandomwHole(double delta, double x_min, double x_max, double y_min, double y_max, std::vector<double> holeinWall, std::mt19937& gen);
};

//Funciones Necesarias
int getRandomInt(int max, std::mt19937& gen, bool positive=true);

//Funciones para Calcular entropía
void counts(std::unordered_map<int,int>& entropyGrid, double x, double y, double x_min, double x_max, double y_min, double y_max, int divisions);

double compute_entropy(std::unordered_map<int, int>& entropyGrid, int N_particles);

double delta_entropy(std::unordered_map<int, int>& entropyGrid, double new_x, double new_y, double x_min, double x_max, double y_min, double y_max, int divisions, double old_x, double old_y, int N_particles);
//Funcion para inicializar el cuadrado

void inicializar(std::vector<Particle> &balls, int N_particles, double LatticeSize, bool initCenter=false);

bool goneThroughWhole(double x, double y, std::vector<double> holeinWall, double delta);

//Funcion para calcular el drop size pt *3
double rms_distance(const std::vector<Particle> &walkers);
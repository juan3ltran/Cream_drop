#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <random>

// Initializing functions
std::map<int, int> InitializeGrid(std::map<int, int> Grid, int Ngrid, int partsNsqrt);
int getRandomInt(int max);


int main(int argc, char **argv){
    double cupSize = 100; // Length of the sides of the domain (cup)
    double partR = 1.; // Particle radius, basically size of a cell in the grid
    int Ngrid = cupSize/partR; // Amount of cells per row of Grid
    int partNsqrt = 5; // Square root number of initial particles (to guarantee an square)
    int steps = 300; // Total number of 'steps'. One step = one particle RW

    std::map<int, int> RWGrid; // Map to store particle information

    // Initialize the grid in the cream drop positions
    RWGrid = InitializeGrid(RWGrid, Ngrid, partNsqrt);

    // 'time loop', 1 particle moves each step
    for (int t=0; t<steps; t++){
        // Perform random walk on one particle
        RWGrid = randomWalk(RWGrid, Ngrid);
    }

    // Print particles
    for (const auto& pair : RWGrid) {
        std::cout << pair.first << std::endl;
    }

    return EXIT_SUCCESS;
}

// Fills the values corresponding to the initial cream drop in the grid (1 per cell)
std::map<int, int> InitializeGrid(std::map<int, int> Grid, int Ngrid, int partsNsqrt){
    int iniInd2D = std::ceil(Ngrid/2) - std::floor(partsNsqrt/2); // 2D index of upper-left side of cream drop
    int iniInd1D = iniInd2D + iniInd2D*Ngrid; // 1D index of upper-left side of cream drop

    int iniCellOcup = 1; // Initial cell ocuppancy (how many parts per cell)

    // loop over all the relative positions in the square
    for (int n=0; n<partsNsqrt*partsNsqrt; n++){
        int index = iniInd1D + (n%partsNsqrt) + (int)(n/partsNsqrt)*Ngrid; // Assign index
        // std::cout<<index<<std::endl;
        Grid[index] = iniCellOcup; // Store set amount of particles in that cell
    }

    return Grid;
}

// Function to perform RW on a random particle from the grid
std::map<int, int> randomWalk(std::map<int, int> RWGrid, int Ngrid){
    auto it = RWGrid.begin(); // Define iterator
    std::advance(it, getRandomInt(RWGrid.size() - 1)); // Choose random element from map

    int cell = it->first, particles = it->second; // Get cell information

    // possible options for particle to move to (E,W,N,S)
    std::vector<int> options = {cell+1, cell-1, cell-Ngrid, cell+Ngrid};

    int newCell = options[getRandomInt(options.size()-1)]; // Cell to which to move next

    RWGrid[cell]--; // Remove 1 particle from this cell
    if (RWGrid[cell] == 0){
        RWGrid.erase(cell); // Delete cells with no particles
    }

    // Add 1 particle to new cell
    RWGrid[newCell]++;

    // // Print particles (maybe not ideal since only one changes hm)
    // if (t==steps/2){
    //     for (const auto& pair : RWGrid) {
    //         std::cout << pair.first << std::endl;
    //     }
    // }

    return RWGrid;
}

// This should be in a separate function.h and function.cpp file, later
int getRandomInt(int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_(0, max);

    return dist_(gen);
}
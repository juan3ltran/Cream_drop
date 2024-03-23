#pragma once
#include <vector>
#include <cmath> 

void counts(std::vector<int>& grid_counts, double x, double y, 
            double x_min, double x_max, double y_min, double y_max, int divisions);

double compute_entropy(std::vector<int>& grid_counts, int N_particles);

double delta_entropy(std::vector<int>& grid_counts, double new_x, double new_y, 
                    double x_min, double x_max, double y_min, double y_max, int divisions, double old_x, double old_y, int N_particles);
#include "funtions.hpp"

void counts(std::vector<int>& grid_counts, double x, double y, 
            double x_min, double x_max, double y_min, double y_max, int divisions)
{
    //Calcula el tamaño de cada subdivision en terminos de las coordenadas de posicion
    double x_step = (x_max - x_min) / static_cast<double>(divisions);
    double y_step = (y_max - y_min) / static_cast<double>(divisions);

    //Verifica la posicion dentro de los limites
        if ((x_min < x) && (x < x_max) && (y_min < y) && (y < y_max))
        {
            // Calcula el índice de la subdivisión para x e y
            int ix = int((x - x_min) / x_step);
            int iy = int((y - y_min) / y_step);

            // Incrementa el contador para esa subdivisión
            grid_counts[ix * divisions + iy]++;
        }
}

double compute_entropy(std::vector<int>& grid_counts, int N_particles)
{
    // Calcula la entropía
    double entropy = 0.0;
    int divisions = sqrt(grid_counts.size());

    for (int ix = 0; ix < divisions; ++ix) {
        for (int iy = 0; iy < divisions; ++iy) {
            if (grid_counts[ix*divisions + iy] > 0) {
                double p = double(grid_counts[ix*divisions + iy]) / N_particles;
                entropy -= p * log(p);
            }
        }
    }
    return entropy;
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
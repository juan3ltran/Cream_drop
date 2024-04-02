#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch_test_macros.hpp"
#include "utils.hpp"
TEST_CASE("Grid_counts is working correctly","[Grid]"){
    std::vector<Particle> balls;
    int N_particles = 400;
    std::vector<int> grid_counts(4*4,0);
    for (int i = 0; i < N_particles; ++i) {
            balls.emplace_back(0, 0); // Cada partícula inicia en (0,0)
        }
    SECTION("Todas las partículas en 0"){
        for (auto ball : balls){
            counts(grid_counts, ball.getX(), ball.getY(), -100, 100, -100, 100, 4);
        }
        REQUIRE(grid_counts[10]==N_particles);
    }
    SECTION("MOVIMIENTO DE UNA PARTICULA"){
        balls[10].setX(-99); balls[10].setY(-99);
        for (auto ball : balls){
            counts(grid_counts, ball.getX(), ball.getY(), -100, 100, -100, 100, 4);
        }
        REQUIRE(grid_counts[10]==N_particles-1);
        REQUIRE(grid_counts[0]==1);
    }  
}

TEST_CASE("rms_distance is working correctly","[rms_distance]"){
    std::vector<Particle> balls;
    int N_particles = 1000;
    std::mt19937 gen(18);
    double half_size = 5;
    for (int i = 0; i < N_particles; ++i) {
            double x = (getRandomInt(1000, gen, false)/1000.0)*half_size;
            double y = (getRandomInt(1000, gen, false)/1000.0)*half_size;
            balls.emplace_back(x, y); // Cada partícula inicia al azar
        }
    SECTION("Todas las partículas uniformemente distribuidas"){
        std::cout<<"x de particula 3 \t"<<balls[6].getX()<<std::endl;
        REQUIRE(rms_distance(balls) == 2);
    }
    
}

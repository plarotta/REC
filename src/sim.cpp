#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <string>
#include "sim.hpp"
#include "robot.hpp"
#include <vector>


using namespace Eigen;
using namespace std;

Simulation::Simulation (float a, int b, float c, float d, float e) {
    dt = a;
    num_robots = b;
    mu_k = c;
    mu_s = d;
    T = e;

    // Resize the vector to hold the desired number of robots
    robots.resize(num_robots);

    for (int i = 0; i < num_robots; i++){
        // use default constructor for all the robots for now
        robots[i] = Robot();
    }
}
Simulation::Simulation() {
    dt = 0.01;
    num_robots = 5;
    mu_k = 0.7;
    mu_s = 0.8;
    T = 5;

    // Resize the vector to hold the desired number of robots
    robots.resize(num_robots);

    for (int i = 0; i < num_robots; i++){
        // use default constructor for all the robots for now
        robots[i] = Robot();
    }
}

int main () {
    Simulation simy = Simulation();
    cout << "SUCCESS!" << endl;
    return 0;
}
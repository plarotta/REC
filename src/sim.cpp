#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <string>
// #include <Robot> //TODO: implement robot class
// #include <REC/src/robot>

using namespace Eigen;
using namespace std;

class Simulation {
    float dt;
    int num_robots;
    float mu_k;
    float mu_s;
    float T;

public:
    Simulation (float, int, float, float, float);
};

Simulation::Simulation (float a, int b, float c, float d, float e) {
    dt = a;
    num_robots = b;
    mu_k = c;
    mu_s = d;
    T = e;
}

int main () {
    return 0;
}
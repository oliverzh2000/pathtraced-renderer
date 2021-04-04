//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_UTIL_H
#define PATHTRACED_FLIGHT_SIM_UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degToRad(double degrees) {
    return degrees * pi / 180.0;
}

inline double randomDouble(double min, double max) {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return min + (max - min) * distribution(generator);
}

#endif //PATHTRACED_FLIGHT_SIM_UTIL_H

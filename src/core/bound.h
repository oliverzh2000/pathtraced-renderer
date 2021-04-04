//
// Created by Oliver Zhang on 2021-04-02.
//

#ifndef PATHTRACED_FLIGHT_SIM_BOUND_H
#define PATHTRACED_FLIGHT_SIM_BOUND_H


/**
 * Holds a min, max value for each dimension.
 * Can test a point if it is in this bound or not.
 */
template <typename T>
class Bound1 {
public:
    T min, max;

    Bound1(T min, T max);

    bool contains(T x) {
        return min < x && x < max;
    }
};

typedef Bound1<double> Bound1d;

// TODO: Bound2, Bound3, and have them do set operations, intersection with ray, etc.

#endif //PATHTRACED_FLIGHT_SIM_BOUND_H

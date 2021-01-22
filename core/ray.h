//
// Created by Oliver Zhang on 2021-01-10.
//

#ifndef PATHTRACED_FLIGHT_SIM_RAY_H
#define PATHTRACED_FLIGHT_SIM_RAY_H

#include "geometry.h"


template<typename T>
class Ray3 {
public:
    Point3<T> origin;
    Vector3<T> direction;

    Ray3(const Point3<T> &origin, const Vector3<T> &direction);

    Point3<T> at(T t) const;
};

typedef Ray3<double> Ray3d;


#endif //PATHTRACED_FLIGHT_SIM_RAY_H

//
// Created by Oliver Zhang on 2021-04-02.
//

#ifndef PATHTRACED_RENDERER_BOUND_H
#define PATHTRACED_RENDERER_BOUND_H

#include "geometry.h"
#include "ray.h"

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

template <typename T>
class Bound3 {
public:
    Point3<T> min;
    Point3<T> max;

    Bound3();
    Bound3(Point3<T> min, Point3<T> max);

//    bool contains(Point3<T> x);

//    Bound3<T> unionWith(const Bound3<T> other);

    /*
     * Return true if the ray hits this Bound in the time interval.
     */
    bool hitRay(const Ray3<T> &ray, double minTime, double maxTime) const;
};


typedef Bound1<double> Bound1d;
typedef Bound3<double> Bound3d;

// TODO: Bound2, Bound3, and have them do set operations, intersection with ray, etc.

#endif //PATHTRACED_RENDERER_BOUND_H

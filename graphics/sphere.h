//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_SPHERE_H
#define PATHTRACED_FLIGHT_SIM_SPHERE_H


#include "hittable.h"
#include "geometry.h"

class Sphere : public Hittable {
public:
    Point3d center;
    double radius;

public:
    Sphere(Point3d center, double radius) : center(center), radius(radius) {};

    bool hit(const Ray3d &r, double t_min, double t_max, HitRecord &rec) const override;
};

#endif //PATHTRACED_FLIGHT_SIM_SPHERE_H

//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_HITTABLE_H
#define PATHTRACED_FLIGHT_SIM_HITTABLE_H

#include "geometry.h"
#include "ray.h"

struct HitRecord {
    Point3d p;
    Vector3d normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray3d & r, const Vector3d & outward_normal) {
        front_face = r.direction.dot(outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray3d& r, double t_min, double t_max, HitRecord& rec) const = 0;
};


#endif //PATHTRACED_FLIGHT_SIM_HITTABLE_H

//
// Created by Oliver Zhang on 2021-01-16.
//

#include "sphere.h"
#include <cmath>

bool Sphere::hit(const Ray3d &r, double t_min, double t_max, HitRecord &rec) const {
    Vector3d oc = r.origin - center;
    auto a = r.direction.lengthSquared();
    auto half_b = oc.dot(r.direction);
    auto c = oc.lengthSquared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vector3d outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

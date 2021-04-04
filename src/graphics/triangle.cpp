//
// Created by Oliver Zhang on 2021-03-15.
//

#include "triangle.h"

#include "matrix.h"


template<typename T>
Triangle<T>::Triangle(Point3<T> v1, Point3<T> v2, Point3<T> v3, const Material &material)
        : v1(v1), v2(v2), v3(v3), outwardNormal((v2 - v1).cross(v3 - v1).normalized()), material(material) {
}

template<typename T>
bool Triangle<T>::hit(const Ray3<T> &incidentRay, double minTime, double maxTime, LightInteraction &interaction) const {
    // Try to intersect the ray with an infinite plane in the same plane as this triangle.
    // Note that the triangle is represented with barycentric coordinates.

    // Find solution for t, beta, and gamma in the linear equation:
    // ray.origin + ray.direction * t = v1 + beta * (v2 - v1) + gamma * (v3 - v1)
    // Can be rearranged to:
    // (v1 - v2) * beta + (v1 - v3) * gamma + ray.direction * t = v1 - ray.origin.
    // TODO: handle the case where the solution has NaNs.
    Vector3<T> solution = Matrix3x3<T>(v1 - v2, v1 - v3, incidentRay.direction).solve(v1 - incidentRay.origin);
    const double &beta = solution.x;
    const double &gamma = solution.y;
    const double &time = solution.z;

    // Is the intersection point inside the triangle, and also within time constraint?
    if (minTime <= time && time <= maxTime && 0 < beta && 0 < gamma && beta + gamma < 1) {
        interaction.location = v1 + beta * (v2 - v1) + gamma * (v3 - v1);
        interaction.time = time;
        interaction.setHitNormal(incidentRay, outwardNormal);
        interaction.material = &material;
        return true;
    }
    return false;
}

template
class Triangle<double>;

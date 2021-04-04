//
// Created by Oliver Zhang on 2021-01-16.
//

#include "sphere.h"

#include <cmath>

#include "quadratic_solver.h"

bool Sphere::hit(const Ray3d &incidentRay, double tMin, double tMax, LightInteraction &interaction) const {
    // Try to intersect the ray with the surface of the sphere.
    // Implicit equation of sphere:
    // (X - center)^2 - radius = 0, where X is a 3d vector of some point on the surface of the sphere.

    // So we need to solve for t in:
    // (ray.origin + t * ray.direction - center) ^ 2 - radius = 0.
    // Which expands to:
    // ray.direction^2 * t^2 + 2*ray.direction * (ray.origin - center) * t + (ray.origin - center)^2 - radius^2 = 0.

    double hitTime = QuadraticSolver::solveEarliestSolution(
            incidentRay.direction.lengthSquared(),
            2.0 * incidentRay.direction.dot(incidentRay.origin - center),
            (incidentRay.origin - center).lengthSquared() - radius * radius,
            Bound1d(tMin, tMax));

    if (std::isnan(hitTime)) {
        return false;
    }
    interaction.time = hitTime;
    interaction.location = incidentRay.at(interaction.time);
    Vector3d outwardNormal = (interaction.location - center) / radius;
    interaction.setHitNormal(incidentRay, outwardNormal);
    interaction.material = &material;
    return true;
}

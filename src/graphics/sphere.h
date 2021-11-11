//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_RENDERER_SPHERE_H
#define PATHTRACED_RENDERER_SPHERE_H


#include <utility>

#include "util.h"
#include "render_primitive.h"
#include "geometry.h"

class Sphere : public RenderPrimitive {
public:
    Point3d center;
    double radius;
    const Material &material;

public:
    Sphere(Point3d center, double radius, const Material &material) : center(center), radius(radius), material(material) {};

    bool hit(const Ray3d &incidentRay, double tMin, double tMax, LightInteraction &interaction) const override;
};

#endif //PATHTRACED_RENDERER_SPHERE_H

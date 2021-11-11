//
// Created by Oliver Zhang on 2021-01-31.
//

#ifndef PATHTRACED_RENDERER_LIGHT_INTERACTION_H
#define PATHTRACED_RENDERER_LIGHT_INTERACTION_H

#include "geometry.h"
#include "ray.h"
#include "util.h"

class Material;

struct LightInteraction {
    Point3d location;
    Vector3d normal; // Must be normalized.
    double time;
    bool isHitOnFrontFace;
    const Material *material;

    void setHitNormal(const Ray3d &incidentRay, const Vector3d &outwardNormal);
};

#endif //PATHTRACED_RENDERER_LIGHT_INTERACTION_H

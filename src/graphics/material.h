//
// Created by Oliver Zhang on 2021-01-25.
//

#ifndef PATHTRACED_FLIGHT_SIM_MATERIAL_H
#define PATHTRACED_FLIGHT_SIM_MATERIAL_H

#include "util.h"
#include "geometry.h"
#include "ray.h"

struct LightInteraction;

class Material {
public:
    // TODO: Need to use proper radiometric quantities than just "attenuation"
    virtual bool scatter(const Ray3d& incidentRay, const LightInteraction& interaction, Color& attenuation, Ray3d& scatteredRay) const = 0;
};


#endif //PATHTRACED_FLIGHT_SIM_MATERIAL_H

//
// Created by Oliver Zhang on 2021-01-25.
//

#ifndef PATHTRACED_FLIGHT_SIM_METAL_H
#define PATHTRACED_FLIGHT_SIM_METAL_H

#include "material.h"
#include "geometry.h"
#include "ray.h"
#include "render_primitive.h"
#include "util.h"

class Metal : public Material {
private:
    Color albedo;

public:
    explicit Metal(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray3d & incidentRay, const LightInteraction& rec, Color& attenuation, Ray3d& scatteredRay) const override;
};

#endif //PATHTRACED_FLIGHT_SIM_METAL_H
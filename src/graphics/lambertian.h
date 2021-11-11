//
// Created by Oliver Zhang on 2021-01-25.
//

#ifndef PATHTRACED_RENDERER_LAMBERTIAN_H
#define PATHTRACED_RENDERER_LAMBERTIAN_H

#include "material.h"
#include "geometry.h"
#include "ray.h"
#include "render_primitive.h"
#include "util.h"

class Lambertian : public Material {
private:
    Color albedo;

public:
    explicit Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray3d & incidentRay, const LightInteraction& interaction, Color& attenuation, Ray3d& scatteredRay) const override;
};


#endif //PATHTRACED_RENDERER_LAMBERTIAN_H

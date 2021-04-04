//
// Created by Oliver Zhang on 2021-01-25.
//

#include "lambertian.h"

bool Lambertian::scatter(const Ray3d & incidentRay, const LightInteraction& interaction, Color& attenuation, Ray3d& scatteredRay) const {
    auto scatterDirection = interaction.normal + Vector3d::randomUnitVector();
    scatteredRay = Ray3d(interaction.location, scatterDirection);
    attenuation = albedo;
    return true;
}

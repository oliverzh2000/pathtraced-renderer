//
// Created by Oliver Zhang on 2021-01-25.
//

#include "lambertian_emitter.h"

bool LambertianEmitter::scatter(const Ray3d &incidentRay, const LightInteraction &interaction, Color &attenuation,
                                Ray3d &scatteredRay,
                                Color &emission) const {
    auto scatterDirection = interaction.normal + Vector3d::randomUnitVector();
    scatteredRay = Ray3d(interaction.location, scatterDirection);
    attenuation = Color(0, 0, 0);
    emission = ke;
    return true;
}

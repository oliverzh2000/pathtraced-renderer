//
// Created by Oliver Zhang on 2021-01-25.
//

#ifndef PATHTRACED_RENDERER_LAMBERTIAN_EMITTER_H
#define PATHTRACED_RENDERER_LAMBERTIAN_EMITTER_H

#include "material.h"
#include "geometry.h"
#include "ray.h"
#include "render_primitive.h"
#include "util.h"

class LambertianEmitter : public Material {
private:
    Color ke;

public:
    explicit LambertianEmitter(const Color& ke) : ke(ke) {}

    bool scatter(const Ray3d &incidentRay, const LightInteraction &interaction, Color &attenuation, Ray3d &scatteredRay,
                 Color &emission) const override;
};


#endif //PATHTRACED_RENDERER_LAMBERTIAN_H

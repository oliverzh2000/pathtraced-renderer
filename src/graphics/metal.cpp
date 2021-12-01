//
// Created by Oliver Zhang on 2021-01-25.
//

#include "metal.h"

bool
Metal::scatter(const Ray3d &incidentRay, const LightInteraction &rec, Color &attenuation, Ray3d &scatteredRay,
               Color &emission) const {
    Vector3d reflected = incidentRay.direction.normalized().reflectOff(rec.normal);
    scatteredRay = Ray3d(rec.location, reflected);
    attenuation = albedo;
    emission = Color(0, 0, 0);
    return (scatteredRay.direction.dot(rec.normal) > 0);
}

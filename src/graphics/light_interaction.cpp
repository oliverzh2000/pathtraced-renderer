//
// Created by Oliver Zhang on 2021-01-31.
//

#include "light_interaction.h"


void LightInteraction::setHitNormal(const Ray3d &incidentRay, const Vector3d &outwardNormal) {
    isHitOnFrontFace = incidentRay.direction.dot(outwardNormal) < 0;
    normal = isHitOnFrontFace ? outwardNormal : -outwardNormal;
}

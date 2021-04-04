//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_RENDER_PRIMITIVE_H
#define PATHTRACED_FLIGHT_SIM_RENDER_PRIMITIVE_H

#include <utility>
#include "geometry.h"
#include "ray.h"
#include "light_interaction.h"
#include "util.h"

/**
 * A geometric primitive that meant to be hit by light rays.
 */
class RenderPrimitive {
public:
    /*
     * Returns true there is a hit between this primitive and an incident ray. False otherwise.
     * If there is a hit, then store information about the interaction between the incident ray
     * and this primitive's surface in the LightInteraction.
     */
    virtual bool hit(const Ray3d& incidentRay, double minTime, double maxTime, LightInteraction& interaction) const = 0;
};


#endif //PATHTRACED_FLIGHT_SIM_RENDER_PRIMITIVE_H

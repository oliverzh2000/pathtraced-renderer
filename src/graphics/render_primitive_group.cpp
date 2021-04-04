//
// Created by Oliver Zhang on 2021-01-16.
//

#include "render_primitive_group.h"

bool RenderPrimitiveGroup::hit(const Ray3d &r, double minTime, double maxTime, LightInteraction &interaction) const {
    LightInteraction earliestInteraction;
    bool hasHitOccurred = false;
    auto earliestTime = maxTime;
    for (const auto &primitive : primitives) {
        if (primitive->hit(r, minTime, earliestTime, earliestInteraction)) {
            hasHitOccurred = true;
            earliestTime = earliestInteraction.time;
            interaction = earliestInteraction;
        }
    }
    return hasHitOccurred;
}
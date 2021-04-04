//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_RENDER_PRIMITIVE_GROUP_H
#define PATHTRACED_FLIGHT_SIM_RENDER_PRIMITIVE_GROUP_H


#include "render_primitive.h"

#include <memory>
#include <vector>


class RenderPrimitiveGroup : public RenderPrimitive {
private:
    std::vector<std::unique_ptr<RenderPrimitive>> primitives;

public:
    RenderPrimitiveGroup() = default;

    void add(std::unique_ptr<RenderPrimitive> object) { primitives.push_back(std::move(object)); }

    bool hit(const Ray3d &r, double minTime, double maxTime, LightInteraction &interaction) const override;
};


#endif //PATHTRACED_FLIGHT_SIM_RENDER_PRIMITIVE_GROUP_H

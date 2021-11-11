//
// Created by Oliver Zhang on 2021-03-15.
//

#ifndef PATHTRACED_RENDERER_TRIANGLE_H
#define PATHTRACED_RENDERER_TRIANGLE_H

#include "geometry.h"
#include "ray.h"
#include "render_primitive.h"
#include "util.h"

/*
 * 3D triangle class using barycentric coordinates.
 */
template <typename T>
class Triangle : public RenderPrimitive {
public:
    // v1, v2, v3 are the three vertices that define this triangle.
    // Normal is in the direction of (v2 - v1) x (v3 - v1).
    const Point3<T> v1;
    const Point3<T> v2;
    const Point3<T> v3;

    const Point3<T> outwardNormal;

    const Material &material;

public:
    Triangle(Point3<T> v1, Point3<T> v2, Point3<T> v3, const Material &material);

    bool hit(const Ray3<T> &incidentRay, double minTime, double maxTime, LightInteraction &interaction) const override;
};



#endif //PATHTRACED_RENDERER_TRIANGLE_H

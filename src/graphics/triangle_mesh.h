//
// Created by Oliver Zhang on 2021-03-15.
//

#ifndef PATHTRACED_RENDERER_TRIANGLE_MESH_H
#define PATHTRACED_RENDERER_TRIANGLE_MESH_H

#include "bound.h"
#include "geometry.h"
#include "ray.h"
#include "render_primitive.h"
#include "util.h"

/*
 * 3D triangle mesh class.
 */
template <typename T>
class TriangleMesh : public RenderPrimitive {
private:
    struct TriangleVertexIndices
    {
        int v1Index;
        int v2Index;
        int v3Index;

        TriangleVertexIndices(int pv1, int pv2, int pv3)
                : v1Index(pv1)
                , v2Index(pv2)
                , v3Index(pv3)
        {}
    };

    std::vector<Vector3<T>> vertices;
    std::vector<TriangleVertexIndices> faces;
    const Material &material;
    Bound3<T> bound;

public:
    TriangleMesh(const std::string& objFileName, const Material &material);

    bool hit(const Ray3<T> &incidentRay, double minTime, double maxTime, LightInteraction &interaction) const override;
};



#endif //PATHTRACED_RENDERER_TRIANGLE_H

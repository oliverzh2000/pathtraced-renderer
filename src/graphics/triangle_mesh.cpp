//
// Created by Oliver Zhang on 2021-03-15.
//

#include "triangle_mesh.h"
#include "triangle.h"

#include <iostream>
#include <fstream>

#include "matrix.h"


template<typename T>
TriangleMesh<T>::TriangleMesh(const std::string& objFileName, const Material &material)
        : material(material) {
    std::string code;
    T vx, vy, vz;
    int s1, s2, s3;

    std::ifstream ifs( objFileName.c_str() );
    if (!ifs.is_open()) {
        throw std::runtime_error("Image read failed: " + objFileName);
    }
    while( ifs >> code ) {
        if( code == "v" ) {
            ifs >> vx >> vy >> vz;
            vertices.push_back( Vector3<T>( vx, vy, vz ) );
            
            // Increase the size of the bounding box around this mesh due to adding another vertex.
            bound.min.x = std::min(bound.min.x, vx);
            bound.min.y = std::min(bound.min.y, vy);
            bound.min.z = std::min(bound.min.z, vz);

            bound.max.x = std::max(bound.max.x, vx);
            bound.max.y = std::max(bound.max.y, vy);
            bound.max.z = std::max(bound.max.z, vz);
        } else if( code == "f" ) {
            ifs >> s1 >> s2 >> s3;
            faces.push_back( TriangleVertexIndices( s1 - 1, s2 - 1, s3 - 1 ) );
        }
    }
    std::cout << "vertices" << ": ";
    for (auto &element: vertices) {
        std::cout << element << ", ";
    }
    std::cout << std::endl;
}

template<typename T>
bool TriangleMesh<T>::hit(const Ray3<T> &incidentRay, double minTime, double maxTime, LightInteraction &interaction) const {
    // Currently there is no Acceleration structure so just loop through all the triangle vertices
    // and intersect the ray with each of the triangles.
    bool hasHit = false;

    if (!bound.hitRay(incidentRay, minTime, maxTime)) {
        return false;
    }

    // Currently loop through all triangles, and perform the hits with each triangle.
    for (const TriangleVertexIndices &vertexIndices: faces) {
        Vector3<T> v1 = vertices[vertexIndices.v1Index];
        Vector3<T> v2 = vertices[vertexIndices.v2Index];
        Vector3<T> v3 = vertices[vertexIndices.v3Index];
//        std::cout << v1 << " " << v2 << " " << v3 << std::endl;
//        std::cout << vertexIndices.v1Index << " " << vertexIndices.v2Index << " " << vertexIndices.v3Index << std::endl;
        if (Triangle<T>(v1, v2, v3, material).hit(incidentRay, minTime, maxTime, interaction)) {
            maxTime = interaction.time;
            hasHit = true;
        }
    }
    return hasHit;
}

template
class TriangleMesh<double>;

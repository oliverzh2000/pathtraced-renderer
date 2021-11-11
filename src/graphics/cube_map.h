//
// Created by Oliver Zhang on 2021-03-13.
//

#ifndef PATHTRACED_RENDERER_CUBE_MAP_H
#define PATHTRACED_RENDERER_CUBE_MAP_H

#include <vector>
#include <string>

#include "texture.h"

class CubeMap {
private:
    std::vector<Texture2D> sides;
    // right   +x: 0
    // left    -x: 1
    // top:    +y  2
    // bottom: -y  3
    // back:   +z  4
    // front:  -z  5
    FilteringMode filteringMode;

public:
    /*
     * Construct this CubeMap from the files in the directory given.
     * Expects there to exist exactly 6 files: right, left, front, back, up, down (they can have an extension, too).
     */
    explicit CubeMap(const std::string &imagesPath);

    /*
     * Sample this CubeMap given the direction of a ray starting from the origin.
     */
    Color sample(Vector3d dir);
};


#endif //PATHTRACED_RENDERER_CUBE_MAP_H

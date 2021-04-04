//
// Created by Oliver Zhang on 2021-03-13.
//

#include "cube_map.h"

//#include <filesystem>

CubeMap::CubeMap(const std::string &imagesPath) {
    // right   +x: 0
    // left    -x: 1
    // top:    +y  2
    // bottom: -y  3
    // back:   +z  4
    // front:  -z  5
    sides.emplace_back(Texture2D("assets/skybox4/right.png", FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER,
                                 false));
    sides.emplace_back(Texture2D("assets/skybox4/left.png", FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER,
                                 false));
    sides.emplace_back(Texture2D("assets/skybox4/top.png", FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER, false));
    sides.emplace_back(Texture2D("assets/skybox4/bottom.png", FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER,
                                 false));
    sides.emplace_back(Texture2D("assets/skybox4/back.png", FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER,
                                 false));
    sides.emplace_back(Texture2D("assets/skybox4/front.png", FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER,
                                 false));
}

// TODO: replcae with 2d vector class.
// Texture coordinate function, for the x component.
// Texture space is [0, 1]^2.
// z is the axis perpendicular to the side of the cube intersected by the ray.
double TCFx(double x, double y, double z) {
    return x / (2 * std::fabs(z)) + 0.5;
}

double TCFy(double x, double y, double z) {
    return y / (2 * std::fabs(z)) + 0.5;
}

Color CubeMap::sample(Vector3d dir) {
    // Determine which of the 6 sides this direction corresponds to.
    int side;
    if (dir.x >= std::fabs(dir.y) && dir.x >= std::fabs(dir.z)) {
        side = 0; // +x
        return sides[side].sample(TCFx(dir.z, dir.y, dir.x), TCFy(dir.z, dir.y, dir.x));
    }
    if (-dir.x > std::fabs(dir.y) && -dir.x > std::fabs(dir.z)) {
        side = 1; // -x
        return sides[side].sample(TCFx(-dir.z, dir.y, dir.x), TCFy(-dir.z, dir.y, dir.x));
    }

    if (dir.y >= std::fabs(dir.z) && dir.y >= std::fabs(dir.x)) {
        side = 2; // +y
        return sides[side].sample(TCFx(dir.x, dir.z, dir.y), TCFy(dir.x, dir.z, dir.y));
    }
    if (-dir.y > std::fabs(dir.z) && -dir.y > std::fabs(dir.x)) {
        side = 3; // -y
        return sides[side].sample(TCFx(dir.x, -dir.z, dir.y), TCFy(dir.x, -dir.z, dir.y));
    }

    if (dir.z >= std::fabs(dir.x) && dir.z >= std::fabs(dir.y)) {
        side = 4; // +z
        return sides[side].sample(TCFx(-dir.x, dir.y, dir.z), TCFy(-dir.x, dir.y, dir.z));
    }
    if (-dir.z > std::fabs(dir.x) && -dir.z > std::fabs(dir.y)) {
        side = 5; // -z
        return sides[side].sample(TCFx(dir.x, dir.y, dir.z), TCFy(dir.x, dir.y, dir.z));
    }
}

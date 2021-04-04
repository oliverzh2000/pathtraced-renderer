//
// Created by Oliver Zhang on 2021-03-14.
//

#include "equirectangular_map.h"

#include "util.h"

EquirectangularMap::EquirectangularMap(const std::string &imagePath)
: texture(Texture2D(imagePath, FilteringMode::NEAREST_NEIGHBOR, WrappingMode::BORDER, true)) {
    if (texture.getWidth() != texture.getHeight() * 2) {
        throw std::runtime_error("Equirectangular map needs image with aspect ratio exactly 2:1.");
    }
}

Color EquirectangularMap::sample(Vector3d dir) {
    // Convert the direction into lat/long, then use that to sample the underlying texture.
    double zenithAngle = std::acos(dir.y / dir.length());
    double azimuthAngle = std::atan2(dir.z, dir.x);

    // Assuming the underlying texture is 2D with a 2:1 aspect ratio,
    // map the zenith and azimuth angle from [0, pi], [-pi, pi] to [0, 1], [0, 1] to sample the texture.
    return texture.sample(azimuthAngle / (2 * pi) + 0.5, 1 - zenithAngle / pi);
}




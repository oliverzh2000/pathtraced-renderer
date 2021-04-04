//
// Created by Oliver Zhang on 2021-03-13.
//

#ifndef PATHTRACED_FLIGHT_SIM_TEXTURE_H
#define PATHTRACED_FLIGHT_SIM_TEXTURE_H

#include <string>

#include "geometry.h"

/**
 * Rectangular 2D texture. Allows loading from image and sampling at location in the texture.
 *
 * Texture space is [0, 1] in each direction. (0, 0) is bottom left and (1, 1) is top right.
 */

enum class FilteringMode {
    NEAREST_NEIGHBOR
};

enum class WrappingMode {
    BORDER
};

class Texture2D {
private:
    int width, height;
    std::vector<float> data;
    const int bytesPerChannel = sizeof(float); // 32 bit float.
    const int numChannels = 3; // rgb
    FilteringMode filteringMode;
    WrappingMode wrappingMode;

public:
    Texture2D(const std::string &imagePath, FilteringMode filteringMode, WrappingMode wrappingMode,
              bool isHDR);
    ~Texture2D();

    // TODO: Separate sampling from the texture itself. Eventually this class should
    // be lightweight and just handle the storage of the texture data, and sampling should be
    // offloaded to a dedicated "sampler" class.
    // TODO: replace with 2d vector class.
    Color sample(double u, double v);

    int getWidth() const;
    int getHeight() const;
};


#endif //PATHTRACED_FLIGHT_SIM_TEXTURE_H

//
// Created by Oliver Zhang on 2021-03-13.
//

#include "texture.h"

#include <stdexcept>
#include <algorithm>
#include "stb_image.h"

Texture2D::Texture2D(const std::string &imagePath, FilteringMode filteringMode, WrappingMode wrappingMode,
                     bool isHDR)
        : filteringMode(filteringMode),
          wrappingMode(wrappingMode) {
    int loadedImageNumChannels;
    int hdr = stbi_is_hdr(imagePath.c_str());
    stbi_hdr_to_ldr_gamma(1.0f);
    stbi_ldr_to_hdr_gamma(1.0f);
    if (isHDR) {
        float *dataChars = stbi_loadf(imagePath.c_str(), &width, &height, &loadedImageNumChannels, numChannels);
        if (dataChars == nullptr) {
            throw std::runtime_error("Image read failed: " + std::string(stbi_failure_reason()));
        }
        for (int i = 0; i < width * height * numChannels; ++i) {
            data.emplace_back(std::pow(dataChars[i], 1.0/2.2)); // TODO: see how to get stbi to do gamma conversion.
        }
        stbi_image_free(dataChars);
    } else {
        unsigned char *dataChars = stbi_load(imagePath.c_str(), &width, &height, &loadedImageNumChannels, numChannels);
        if (dataChars == nullptr) {
            throw std::runtime_error("Image read failed: " + std::string(stbi_failure_reason()));
        }
        for (int i = 0; i < width * height * numChannels; ++i) {
            data.emplace_back(dataChars[i] / 255.0f);
        }
        stbi_image_free(dataChars);
    }
}

Texture2D::~Texture2D() {
}

Color Texture2D::sample(double u, double v) {
    int xIndex = std::clamp(u * width, double(0), double(width - 1));
    int yIndex = std::clamp((1 - v) * height, double(0), double(height - 1));
    int startIndex = (xIndex + yIndex * width) * numChannels;
    return Color(data[startIndex], data[startIndex + 1], data[startIndex + 2]);
}

int Texture2D::getWidth() const {
    return width;
}

int Texture2D::getHeight() const {
    return height;
}

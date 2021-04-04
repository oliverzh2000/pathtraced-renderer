//
// Created by Oliver Zhang on 2021-03-14.
//

#ifndef PATHTRACED_FLIGHT_SIM_EQUIRECTANGULAR_MAP_H
#define PATHTRACED_FLIGHT_SIM_EQUIRECTANGULAR_MAP_H

#include <vector>
#include <string>

#include "texture.h"

class EquirectangularMap {
private:
    Texture2D texture;

public:
    explicit EquirectangularMap(const std::string &imagePath);

    Color sample(Vector3d dir);
};


#endif //PATHTRACED_FLIGHT_SIM_EQUIRECTANGULAR_MAP_H

//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_CAMERA_H
#define PATHTRACED_FLIGHT_SIM_CAMERA_H


#include "util.h"
#include "geometry.h"
#include "ray.h"

class Camera {
public:
    Camera(int width, int height);

    void setAspectRatio(int width, int height);

    [[nodiscard]] Ray3d getRay(double u, double v) const {
        return Ray3d(origin, lower_left_corner + horizontal * u + vertical * v - origin);
    }

private:
    Point3d origin;
    Point3d lower_left_corner;
    Vector3d horizontal;
    Vector3d vertical;
};

#endif //PATHTRACED_FLIGHT_SIM_CAMERA_H

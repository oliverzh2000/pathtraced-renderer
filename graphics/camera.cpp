//
// Created by Oliver Zhang on 2021-01-16.
//

#include "camera.h"

Camera::Camera(int width, int height) {
    setAspectRatio(width, height);
}

void Camera::setAspectRatio(int width, int height) {
    auto aspect_ratio = double(width) / double(height);
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    origin = Point3d(0, 0, 0);
    horizontal = Vector3d(viewport_width, 0.0, 0.0);
    vertical = Vector3d(0.0, viewport_height, 0.0);
    lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3d(0, 0, focal_length);
}

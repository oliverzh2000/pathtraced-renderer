//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_RENDERER_CAMERA_H
#define PATHTRACED_RENDERER_CAMERA_H


#include "util.h"
#include "geometry.h"
#include "ray.h"


enum MovementDirection {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    FRONT,
    BACK,
};

// Basics of how the camera works:
// Rays originate from lookFrom.
// lookDirection is computed from yaw and pitch (roll is zero, for now).
class Camera {

private:
    const Vector3d worldUp = Vector3d(0, 1, 0);

    // Primary camera state.
    Vector3d lookFrom;
    double verticalFov = 90;
    double aspectRatio;
    double yaw = 90;
    double pitch = 0;
    double apertureRadius = 0;
    double focusDistance = 1;

    // Compute these in updateCameraVectors, to save getRay from doing it each time it's called.
    Vector3d lookDirection;
    Vector3d right;
    Vector3d up;

    // Camera movement options
    const double maxPitch = 89.9;
    double movementSpeed = 2.5;
    double mouseSensitivity = 3.0;
    double fovSensitivity = 300.0;
    double minVerticalFOV = 25;
    double maxVerticalFOV = 140;

public:
    Camera(Vector3d lookFrom, double yaw, double pitch, int width, int height)
    : lookFrom(lookFrom), yaw(yaw), pitch(pitch), aspectRatio(double(width) / double(height)) {
        updateCameraVectors();
    }

    void movePosition(MovementDirection direction, double deltaTime) {
        double velocity = movementSpeed * deltaTime;
        Vector3d horizontalLookDirection = worldUp.cross(right).normalized();
        if (direction == RIGHT) {
            lookFrom += right * velocity;
        }
        if (direction == LEFT) {
            lookFrom -= right * velocity;
        }
        if (direction == UP) {
            lookFrom += worldUp * velocity;
        }
        if (direction == DOWN) {
            lookFrom -= worldUp * velocity;
        }
        if (direction == FRONT) {
            lookFrom += horizontalLookDirection * velocity;
        }
        if (direction == BACK) {
            lookFrom -= horizontalLookDirection * velocity;
        }
    }

    void moveDirection(double xoffset, double yoffset, double deltaTime) {
        yaw += xoffset * mouseSensitivity * deltaTime;
        pitch += yoffset * mouseSensitivity * deltaTime;

        if (pitch > maxPitch) {
            pitch = maxPitch;
        }
        if (pitch < -maxPitch) {
            pitch = -maxPitch;
        }
        updateCameraVectors();
    }

    void changeVerticalFOV(double deltaFOV, double deltaTime) {
        verticalFov += fovSensitivity * deltaFOV * deltaTime;

        if (verticalFov > maxVerticalFOV) {
            verticalFov = maxVerticalFOV;
        }
        if (verticalFov < minVerticalFOV) {
            verticalFov = minVerticalFOV;
        }
        updateCameraVectors();
    }

    void setAspectRatio(int width, int height) {
        aspectRatio = double(width) / double(height);
        updateCameraVectors();
    }

    void setApertureRadius(double apertureSize) {
        this->apertureRadius = apertureSize;
    }

    void setFocalDistance(double focusDistance) {
        this->focusDistance = focusDistance;
    }

    /*
     * Generate the ray corresponding to the x, y coordinates (NDC) of the image.
     */
    Ray3d generateRay(double x, double y) const {
        Vector3d lensPosition(0, 0, 0);
        if (apertureRadius != 0) {
            Vector3d lensOffset = Vector3d::randomInUnitSphere() * apertureRadius;
            lensPosition = lensOffset.x * right + lensOffset.y * up;
        }
        return Ray3d(lookFrom + lensPosition, focusDistance * (lookDirection + (x - 0.5) * right + (y - 0.5) * up));
    }

private:
    // Calculations performed here so that getRay doesn't have to do them each time its called.
    void updateCameraVectors() {
        lookDirection = Vector3d(cos(degToRad(yaw)) * cos(degToRad(pitch)),
                                 sin(degToRad(pitch)),
                                 sin(degToRad(yaw)) * cos(degToRad(pitch))
        ).normalized();
        double height = std::tan(degToRad(verticalFov / 2)) * 2;
        double width = height * aspectRatio;
        right = lookDirection.cross(worldUp).normalized() * width;
        up = right.cross(lookDirection).normalized() * height;
    }
};

#endif //PATHTRACED_RENDERER_CAMERA_H

#include <iostream>

#include "Light.hpp"

Light::Light()
  : colour(0.0, 0.0, 0.0),
    position(0.0, 0.0, 0.0)
{
}

Color Light::irradiance(const Vector3d &surfacePosition, const Vector3d &normal) const {
    Vector3d direction = (position - surfacePosition);

    double fluxScale = 1000;
    double distanceScale = 0.01;

    double r = direction.length() * distanceScale;
    Color unclamped = (colour * fluxScale * direction.normalized().dot(normal)) / (4.0 * pi * r * r);
    unclamped.x = std::max(0.0f, unclamped.x);
    unclamped.y = std::max(0.0f, unclamped.y);
    unclamped.z = std::max(0.0f, unclamped.z);
    return unclamped;
}

std::ostream& operator<<(std::ostream& out, const Light& l)
{
  out << "L[" << l.colour
  	  << ", " << l.position << ", ";
  out << "]";
  return out;
}

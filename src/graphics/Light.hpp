#pragma once

#include <iosfwd>

#include "geometry.h"

// Represents a simple point light.
struct Light {
  Light();
  
  Color colour;
  Vector3d position;

  Color irradiance(const Vector3d &surfacePosition, const Vector3d &normal) const;
};

std::ostream& operator<<(std::ostream& out, const Light& l);

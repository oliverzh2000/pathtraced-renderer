//
// Created by Oliver Zhang on 2021-01-10.
//

#ifndef PATHTRACED_FLIGHT_SIM_GEOMETRY_H
#define PATHTRACED_FLIGHT_SIM_GEOMETRY_H

#include <iostream>

#include "util.h"


template <typename T>
class Vector3 {
public:
    T x, y, z;

    Vector3();
    Vector3(T x, T y, T z);

    Vector3<T> operator+(const Vector3<T> &other) const;
    Vector3<T> operator-(const Vector3<T> &other) const;
    Vector3<T> operator*(T k) const;
    Vector3<T> operator/(T k) const;
    Vector3<T> operator-() const;

    Vector3<T> &operator+=(const Vector3<T> &other);
    Vector3<T> &operator-=(const Vector3<T> &other);
    Vector3<T> &operator*=(T k);
    Vector3<T> &operator/=(T k);

    bool operator==(const Vector3<T> &other) const;
    bool operator!=(const Vector3<T> &other) const;

    T lengthSquared() const;
    T length() const;

    T dot(const Vector3<T> &other) const;
    Vector3<T> cross(const Vector3<T> &other) const;

    Vector3<T> unitVector() const;

    static Vector3<T> random();
    static Vector3<T> random(double min, double max);
    static Vector3<T> randomInUnitSphere();
};

template <typename T>
std::ostream &operator<<(std::ostream &ostream, const Vector3<T> &v) {
    ostream << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return ostream;
}

typedef Vector3<double> Vector3d;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

template<typename T>
using Point3 = Vector3<T>;

typedef Vector3<double> Point3d;
typedef Vector3<float> Point3f;
typedef Vector3<int> Point3i;

typedef Vector3<float> Color;

#endif //PATHTRACED_FLIGHT_SIM_GEOMETRY_H

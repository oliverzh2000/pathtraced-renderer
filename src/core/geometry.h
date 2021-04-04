//
// Created by Oliver Zhang on 2021-01-10.
//

#ifndef PATHTRACED_FLIGHT_SIM_GEOMETRY_H
#define PATHTRACED_FLIGHT_SIM_GEOMETRY_H

#include <iostream>

#include "util.h"

// TODO: Refator the point and color typedefs into their own classes.
template <typename T>
class Vector3 {
public:
    T x, y, z;

    Vector3();
    Vector3(T x, T y, T z);

    Vector3<T> operator+(const Vector3<T> &other) const;
    Vector3<T> operator-(const Vector3<T> &other) const;
    Vector3<T> operator*(const Vector3<T> &other) const; // TODO: specific to color, factor out later.
    Vector3<T> operator*(T k) const;
    Vector3<T> operator/(T k) const;
    Vector3<T> operator-() const;

    Vector3<T> &operator+=(const Vector3<T> &other);
    Vector3<T> &operator-=(const Vector3<T> &other);
    Vector3<T> &operator*=(const Vector3<T> &other); // specific to color
    Vector3<T> &operator*=(T k);
    Vector3<T> &operator/=(T k);

    bool operator==(const Vector3<T> &other) const;
    bool operator!=(const Vector3<T> &other) const;

    T lengthSquared() const;
    T length() const;

    T dot(const Vector3<T> &other) const;
    Vector3<T> cross(const Vector3<T> &other) const;

    Vector3<T> normalized() const;
    Vector3<T> reflectOff(const Vector3<T>& normal) {
        return *this - 2 * this->dot(normal) * normal;
    }

    static Vector3<T> random(double min, double max); // TODO: refactor into separate random utility class.
    static Vector3<T> randomInUnitSphere();
    static Vector3<T> randomUnitVector() {
        return randomInUnitSphere().normalized();
    }
    static Vector3<T> randomInUnitDisk() {
        while (true) {
            auto p = Vector3<T>(randomDouble(-1, 1), randomDouble(-1, 1), 0);
            if (p.lengthSquared() >= 1) continue;
            return p;
        }
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &ostream, const Vector3<T> &v) {
    ostream << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return ostream;
}

template <typename T>
Vector3<T> operator*(T k, const Vector3<T> vec) {
    return Vector3<T>(vec.x * k, vec.y * k, vec.z * k);
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

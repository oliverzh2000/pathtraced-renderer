//
// Created by Oliver Zhang on 2021-01-10.
//

#include "geometry.h"

#include <cmath>

template<typename T>
Vector3<T>::Vector3() : x(0), y(0), z(0) {
}

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T> &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T> &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);;
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T> &other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);;
}

template<typename T>
Vector3<T> Vector3<T>::operator*(T k) const {
    return Vector3<T>(x * k, y * k, z * k);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(T k) const {
    T kReciprocal = 1 / k;
    return Vector3<T>(x * kReciprocal, y * kReciprocal, z * kReciprocal);
}

template<typename T>
Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

template<typename T>
Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator*=(T k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

template<typename T>
Vector3<T> &Vector3<T>::operator/=(T k) {
    T kReciprocal = 1 / k;
    x *= kReciprocal;
    y *= kReciprocal;
    z *= kReciprocal;
    return *this;
}

template<typename T>
bool Vector3<T>::operator==(const Vector3<T> &other) const {
    return x == other.x && y == other.y && z == other.z;
}

template<typename T>
bool Vector3<T>::operator!=(const Vector3<T> &other) const {
    return x != other.x || y != other.y || z != other.z;
}

template<typename T>
T Vector3<T>::lengthSquared() const {
    return x * x + y * y + z * z;
}

template<typename T>
T Vector3<T>::length() const {
    return std::sqrt(lengthSquared());
}

template<typename T>
T Vector3<T>::dot(const Vector3<T> &other) const {
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T> &other) const {
    return Vector3<T>(y * other.z - z * other.y,
                      z * other.x - x * other.z,
                      x * other.y - y * other.x);
}

template<typename T>
Vector3<T> Vector3<T>::normalized() const {
    return *this / length();
}

template<typename T>
Vector3<T> Vector3<T>::random(double min, double max) {
    return Vector3<T> (randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

template<typename T>
Vector3<T> Vector3<T>::randomInUnitSphere() {
    while (true) {
        auto p = Vector3<T>::random(-1,1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

template
class Vector3<double>;

template
class Vector3<float>;

template
class Vector3<int>;

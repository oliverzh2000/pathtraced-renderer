//
// Created by Oliver Zhang on 2021-01-10.
//

#include "ray.h"

template<typename T>

Ray3<T>::Ray3(const Point3<T> &origin, const Vector3<T> &direction) : origin(origin), direction(direction) {
}

template<typename T>
Point3<T> Ray3<T>::at(T t) const {
    return origin + direction * t;
}

template class Ray3<double>;
template class Ray3<float>;

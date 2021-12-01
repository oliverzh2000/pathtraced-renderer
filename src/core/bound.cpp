//
// Created by Oliver Zhang on 2021-04-02.
//

#include "bound.h"

#include <algorithm>

template<typename T>
Bound1<T>::Bound1(T min, T max) : min(min), max(max) {
}

//template<typename T>
//bool Bound1<T>::contains(T x) {
//    return min < x && x < max;
//}

template<typename T>
Bound3<T>::Bound3(Point3<T> min, Point3<T> max)
    : min(min), max(max) {
}

//template<typename T>
//bool Bound3<T>::contains(Point3<T> x) {
//    return false;
//}
//
//template<typename T>
//Bound3<T> Bound3<T>::unionBound(const Bound3<T> other) {
//    return Bound3<T>(Vector3(), Vector3());
//}

template<typename T>
bool Bound3<T>::hitRay(const Ray3<T> &ray, double minTime, double maxTime) const {
    // For each spatial dimension, compute the time interval that the ray hits
    // the planes for the Bound in that dimension.
    // Perform intersection of these intervals and the (minTime, maxTime) interval,
    // Returning failure if the final interval is empty.

    // Note: the min plane in this Bound is not necessarily the first side the ray hits.
    T timeX1 = (min.x - ray.origin.x) / ray.direction.x;
    T timeX2 = (max.x - ray.origin.x) / ray.direction.x;

    T timeY1 = (min.y - ray.origin.y) / ray.direction.y;
    T timeY2 = (max.y - ray.origin.y) / ray.direction.y;
    
    T timeZ1 = (min.z - ray.origin.z) / ray.direction.z;
    T timeZ2 = (max.z - ray.origin.z) / ray.direction.z;

    T minBoundTime = std::max({std::min(timeX1, timeX2), std::min(timeY1, timeY2), std::min(timeZ1, timeZ2)});
    T maxBoundTime = std::min({std::max(timeX1, timeX2), std::max(timeY1, timeY2), std::max(timeZ1, timeZ2)});

    return minBoundTime <= maxBoundTime && (minTime < minBoundTime || maxBoundTime < maxTime);
}

template<typename T>
Bound3<T>::Bound3()
    : min(Point3<T>(infinity, infinity, infinity)), max(Point3<T>(-infinity, -infinity, -infinity)) {
}

template
class Bound1<double>;

template
class Bound3<double>;

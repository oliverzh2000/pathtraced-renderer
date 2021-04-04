//
// Created by Oliver Zhang on 2021-04-02.
//

#include "bound.h"

template<typename T>
Bound1<T>::Bound1(T min, T max) : min(min), max(max) {
}

//template<typename T>
//bool Bound1<T>::contains(T x) {
//    return min < x && x < max;
//}

template
class Bound1<double>;

//
// Created by Oliver Zhang on 2021-03-15.
//

#ifndef PATHTRACED_FLIGHT_SIM_MATRIX_H
#define PATHTRACED_FLIGHT_SIM_MATRIX_H

#include "geometry.h"

template <typename T>
class Matrix3x3 {
public:
    T a, d, g;
    T b, e, h;
    T c, f, i;

    Matrix3x3(T e11, T e12, T e13, T e21, T e22, T e23, T e31, T e32, T e33);
    Matrix3x3(Vector3<T> col1, Vector3<T> col2, Vector3<T> col3);

    /*
     * Return the x in Mx = y, where M is this matrix. (Uses cramer's rule).
     */
    Vector3<T> solve(Vector3<T> y) const;

    Vector3<T> operator*(const Vector3<T> &x) const;

    Matrix3x3<T> operator*(const Matrix3x3<T> &other) const;
};



#endif //PATHTRACED_FLIGHT_SIM_MATRIX_H

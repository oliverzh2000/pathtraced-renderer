//
// Created by Oliver Zhang on 2021-03-15.
//

#include "matrix.h"

template<typename T>
Matrix3x3<T>::Matrix3x3(T e11, T e12, T e13, T e21, T e22, T e23, T e31, T e32, T e33)
: a(e11), d(e12), g(e13),
  b(e21), e(e22), h(e23),
  c(e31), f(e32), i(e33) {
}

template<typename T>
Matrix3x3<T>::Matrix3x3(Vector3<T> col1, Vector3<T> col2, Vector3<T> col3)
: a(col1.x), d(col2.x), g(col3.x),
  b(col1.y), e(col2.y), h(col3.y),
  c(col1.z), f(col2.z), i(col3.z) {
}


template<typename T>
Vector3<T> Matrix3x3<T>::solve(Vector3<T> y) const {
    double j = y.x;
    double k = y.y;
    double l = y.z;

    double ei_m_hf = e * i - h * f;
    double gf_m_di = g * f - d * i;
    double dh_m_eg = d * h - e * g;

    double ak_m_jb = a * k - j * b;
    double jc_m_al = j * c - a * l;
    double bl_m_kc = b * l - k * c;

    double det_M = a * ei_m_hf + b * gf_m_di + c * dh_m_eg;
    if (det_M == 0) {
//        throw std::runtime_error("Matrix is not invertible.");
        return Vector3<T>(NAN, NAN, NAN);
    }

    return Vector3<T>(
            j * ei_m_hf + k * gf_m_di + l * dh_m_eg,
            i * ak_m_jb + h * jc_m_al + g * bl_m_kc,
            -(f * ak_m_jb + e * jc_m_al + d * bl_m_kc)
    ) / det_M;
}

template<typename T>
Vector3<T> Matrix3x3<T>::operator*(const Vector3<T> &x) const {
    return Vector3<T>(x.dot(Vector3<T>(a, d, g)), x.dot(Vector3<T>(b, e, h)), x.dot(Vector3<T>(c, f, i)));
}

template<typename T>
Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T> &other) const {
    return Matrix3x3<T>(T(), T(), T(), T(), T(), T(), T(), T(), T());
}

template
class Matrix3x3<double>;
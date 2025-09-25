// =============================
// include/Math.h
// =============================
#pragma once
#include <array>
#include <vector>
#include <string>
#include "EulerAngle.h"
#include "Quaternion.h"

namespace Math {
// small helpers
template<size_t R,size_t C>
using Mat = std::array<std::array<float,C>,R>;

template<size_t R,size_t C, size_t K>
Mat<R,C> mul(const Mat<R,K>& A, const Mat<K,C>& B);

std::array<float,16> quatToMatrix(const Quaternion& q);

// Blend Q(t) = T * M * G (Catmull/B-spline)
std::array<float,7> blend(const Mat<1,4>& T, const Mat<4,4>& M, const Mat<4,7>& G);

// Interpolation in Euler space (6-dim) and Quaternion space (7-dim)
EulerAngle eInterpolation(const std::string& type, float t, int pointIndex);
Quaternion qInterpolation(const std::string& type, float t, int pointIndex);
}

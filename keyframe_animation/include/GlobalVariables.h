// =============================
// include/GlobalVariables.h
// =============================
#pragma once
#include <array>
#include <vector>

namespace Global {
inline constexpr int WIDTH = 400;
inline constexpr int HEIGHT = 400;
inline constexpr int pointNum = 7;

// Catmull-Rom matrix (a=0.5)
inline constexpr float a = 0.5f;
inline const float CRSplineM[4][4] = {
{ -a, 2.0f - a, a - 2.0f, a },
{ 2.0f*a, a - 3.0f, 3.0f - 2.0f*a, -a },
{ -a, 0.0f, a, 0.0f },
{ 0.0f, 1.0f, 0.0f, 0.0f }
};

// Uniform cubic B-spline basis
inline const float BSplineM[4][4] = {
{ -1.0f/6, 3.0f/6, -3.0f/6, 1.0f/6 },
{ 3.0f/6, -6.0f/6, 3.0f/6, 0.0f },
{ -3.0f/6, 0.0f, 3.0f/6, 0.0f },
{ 1.0f/6, 4.0f/6, 1.0f/6, 0.0f }
};

// 7 points: [ax, ay, az, px, py, pz] (angles in degrees)
inline const float points[pointNum][6] = {
{ 90, 0, 45, -5, 0, -5 },
{ 70, 20, 65, -3, 3, -10 },
{ 50, 40, 85, -1, 1, -15 },
{ 30, 60, 105, 0, -5, -20 },
{ 50, 40, 85, 1, 1, -15 },
{ 70, 20, 65, 3, 3, -10 },
{ 90, 0, 45, 5, 0, -5 }
};
}

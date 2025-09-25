// =============================
// include/EulerAngle.h
// =============================
#pragma once
#include <array>
#include "Quaternion.h"

struct EulerAngle {
float ax, ay, az; // degrees
float px, py, pz; // position

EulerAngle(float a,float b,float c,float x,float y,float z);
explicit EulerAngle(const float p[6]);

std::array<float,3> anglesRad() const; // radians
std::array<float,16> toMatrix() const; // column-major 4x4
std::array<float,16> toOneDMatrix() const { return toMatrix(); }
Quaternion toQuaternion() const; // XYZ order
};

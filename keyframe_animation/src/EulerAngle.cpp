#include "EulerAngle.h"
#include <cmath>

static inline float rad(float deg){ return deg * 3.14159265358979323846f / 180.0f; }

EulerAngle::EulerAngle(float a,float b,float c,float x,float y,float z)
: ax(a), ay(b), az(c), px(x), py(y), pz(z) {}

EulerAngle::EulerAngle(const float p[6])
: ax(p[0]), ay(p[1]), az(p[2]), px(p[3]), py(p[4]), pz(p[5]) {}

std::array<float,3> EulerAngle::anglesRad() const {
return { rad(ax), rad(ay), rad(az) };
}

std::array<float,16> EulerAngle::toMatrix() const {
// XYZ rotation order
auto [a,b,c] = anglesRad();
const float ca = std::cos(a), sa = std::sin(a);
const float cb = std::cos(b), sb = std::sin(b);
const float cc = std::cos(c), sc = std::sin(c);

// R = Rx(a) * Ry(b) * Rz(c)
// column-major 4x4
std::array<float,16> M{};
M[0] = cb*cc; M[4] = -cb*sc; M[8] = sb; M[12] = px;
M[1] = sa*sb*cc+ca*sc; M[5] = -sa*sb*sc+ca*cc; M[9] = -sa*cb; M[13] = py;
M[2] = -ca*sb*cc+sa*sc; M[6] = ca*sb*sc+sa*cc; M[10] = ca*cb; M[14] = pz;
M[3] = 0; M[7] = 0; M[11] = 0; M[15] = 1;
return M;
}

Quaternion EulerAngle::toQuaternion() const {
auto [a,b,c] = anglesRad();
float cx = std::cos(a*0.5f), sx = std::sin(a*0.5f);
float cy = std::cos(b*0.5f), sy = std::sin(b*0.5f);
float cz = std::cos(c*0.5f), sz = std::sin(c*0.5f);

// XYZ intrinsic
float w = cx*cy*cz - sx*sy*sz;
float x = sx*cy*cz + cx*sy*sz;
float y = cx*sy*cz - sx*cy*sz;
float z = cx*cy*sz + sx*sy*cz;

return Quaternion(w,x,y,z,px,py,pz);
}

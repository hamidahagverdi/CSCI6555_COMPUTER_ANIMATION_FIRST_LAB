#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion(float W,float X,float Y,float Z,float PX,float PY,float PZ)
: w(W), x(X), y(Y), z(Z), px(PX), py(PY), pz(PZ) { normalize(); }

Quaternion::Quaternion(const std::array<float,7>& q7)
: w(q7[0]), x(q7[1]), y(q7[2]), z(q7[3]), px(q7[4]), py(q7[5]), pz(q7[6]) { normalize(); }

void Quaternion::normalize(){
    float n = std::sqrt(w*w + x*x + y*y + z*z);
    if(n>0){ w/=n; x/=n; y/=n; z/=n; }
}

std::array<float,7> Quaternion::getPoint() const {
    return {w,x,y,z,px,py,pz};
}

std::array<float,16> Quaternion::toMatrix() const {
    const float xx=x*x, yy=y*y, zz=z*z;
    const float xy=x*y, xz=x*z, yz=y*z;
    const float wx=w*x, wy=w*y, wz=w*z;
    std::array<float,16> M{};
    M[0]=1-2*(yy+zz); M[4]=2*(xy-wz); M[8]=2*(xz+wy); M[12]=px;
    M[1]=2*(xy+wz);   M[5]=1-2*(xx+zz); M[9]=2*(yz-wx); M[13]=py;
    M[2]=2*(xz-wy);   M[6]=2*(yz+wx);   M[10]=1-2*(xx+yy); M[14]=pz;
    M[3]=0; M[7]=0; M[11]=0; M[15]=1;
    return M;
}

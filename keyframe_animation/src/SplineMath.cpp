#include "SplineMath.h"
#include "GlobalVariables.h"
#include <algorithm>
#include <cmath>
#include <cstring>

using Math::Mat;

template<size_t R,size_t C, size_t K>
Mat<R,C> Math::mul(const Mat<R,K>& A, const Mat<K,C>& B){
Mat<R,C> P{};
for(size_t i=0;i<R;++i)
for(size_t j=0;j<C;++j){
float s=0; for(size_t k=0;k<K;++k) s+=A[i][k]*B[k][j];
P[i][j]=s;
}
return P;
}

std::array<float,16> Math::quatToMatrix(const Quaternion& q){
return q.toMatrix();
}

std::array<float,7> Math::blend(const Mat<1,4>& T, const Mat<4,4>& M, const Mat<4,7>& G){
auto TM = mul<1,4,4>(T,M); // 1x4
auto B = mul<1,7,4>(TM, (Mat<4,7>&)G); // 1x7
return { B[0][0],B[0][1],B[0][2],B[0][3],B[0][4],B[0][5],B[0][6] };
}

static Math::Mat<4,4> pickM(const std::string& type){
Math::Mat<4,4> M{};
const float (*src)[4] = (type=="B Spline") ? Global::BSplineM : Global::CRSplineM;
for(int i=0;i<4;++i) for(int j=0;j<4;++j) M[i][j]=src[i][j];
return M;
}

EulerAngle Math::eInterpolation(const std::string& type, float t, int pointIndex){
if(pointIndex+3 >= Global::pointNum) return EulerAngle(0,0,0,0,0,0);
Mat<1,4> T{{ {t*t*t, t*t, t, 1} }};
auto M = pickM(type);
// Build G (4x6): angles+pos
float Gf[4][6];
for(int i=0;i<4;++i)
for(int j=0;j<6;++j)
Gf[i][j] = Global::points[pointIndex+i][j];
// Interpolate each channel separately
float out[6]{};
for(int col=0; col<6; ++col){
Mat<4,1> Gcol{}; for(int r=0;r<4;++r) Gcol[r][0]=Gf[r][col];
auto TM = mul<1,4,4>(T,M); // 1x4
auto B = mul<1,1,4>(TM, Gcol); // 1x1
out[col] = B[0][0];
}
return EulerAngle(out);
}

Quaternion Math::qInterpolation(const std::string& type, float t, int pointIndex){
if(pointIndex+3 >= Global::pointNum) return Quaternion();
Mat<1,4> T{{ {t*t*t, t*t, t, 1} }};
auto M = pickM(type);

// Build G (4x7) from Euler->Quaternion at control points
Mat<4,7> G{};
for(int i=0;i<4;++i){
EulerAngle e(Global::points[pointIndex+i]);
auto q7 = e.toQuaternion().getPoint();
for(int j=0;j<7;++j) G[i][j] = q7[j];
}
auto blended = blend(T,M,G);
Quaternion q{blended};
return q;
}

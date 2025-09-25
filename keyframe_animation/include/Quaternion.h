cat > include/Function.h << 'EOF'
#ifndef FUNCTION_H
#define FUNCTION_H

#include "EulerAngle.h"
#include "Quaternion.h"
#include "GlobalVariables.h"
#include <string>
#include <vector>

class Function {
public:
    static void multiplyMatrix(const float a[4][4], const float b[4][4], float result[4][4]);
    static std::vector<float> convertMatrix(const float matrix[4][4]);
    static std::vector<float> vectorCross(const std::vector<float>& a, const std::vector<float>& b);
    static float vectorDot(const std::vector<float>& a, const std::vector<float>& b);
    static void displayProduct(const float product[4][4]);
    static std::vector<float> blend(const std::vector<float>& T, const float MS[4][4], const float G[4][6]);
    static std::vector<float> blend(const std::vector<float>& T, const float MS[4][4], const float G[4][7]);
    static EulerAngle eInterpolation(const std::string& splineType, float t, int pointIndex);
    static Quaternion qInterpolation(const std::string& splineType, float t, int pointIndex);
};

#endif
EOF

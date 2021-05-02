#include "GenMath.h"

namespace MathLib {
	const float YMath::posInf = std::numeric_limits<float>::max();
	const float YMath::negInf = std::numeric_limits<float>::min();
    const float YMath::Max(float a, float b) {
        return std::max(a, b);
    }
    const float YMath::Min(float a, float b) {
        return std::min(a, b);
    }
    const float YMath::Abs(float a) {
        return abs(a);
    }
    /*const bool YMath::IsZero(float a, float epsilon = yEpsilon) {
        return (abs(a) <= epsilon);
    }*/
    const bool YMath::IsNearlyZero(float a, float epsilon) {
        return IsZero(a, epsilon);
    }
    const float YMath::Clamp(float a, float min, float max) {
        if (a < min) a = min;
        if (a > max) a = max;
        return a;
    }
    const bool YMath::IsNaN(float a) {
        if (isnan(a)) {
            return true;
        }
        return false;
    }
    const float YMath::ACos(float a) {
        if (a <= -1.0f) return yPi;
        else if (a >= 1.0f) return 0;
        return acos(a);
    }
    const float YMath::ASin(float a) {
        if (a <= -1.0f) return -yPiBy2;
        else if (a >= 1.0f) return yPiBy2;
        return asin(a);
    }
    const float YMath::ATan(float a) {
        return atan(a);
    }
    const float YMath::Cos(float a) {
        return cos(a);
    }
    const float YMath::Sin(float a) {
        return sin(a);
    }
    const float YMath::Tan(float a) {
        return tan(a);
    }
    const float YMath::DegToRad(float deg) {
        return deg * (yPi / 180.0f);
    }
    const float YMath::RadToDeg(float rad) {
        return rad * (180.0f / yPi);
    }
    const float YMath::Round(float a) {
        return round(a);
    }
    const float YMath::Sqrt(float a) {
        return sqrt(a);
    }
    const float YMath::Log(float a) {
        return log(a);
    }
    const float YMath::Log2(float a) {
        return log2(a);
    }
    const float YMath::Log10(float a) {
        return log10(a);
    }
    const float YMath::Exp(float a) {
        return exp(a);
    }
    const float YMath::ATan2(float a, float b) {
        return atan2(a,b);
    }
}
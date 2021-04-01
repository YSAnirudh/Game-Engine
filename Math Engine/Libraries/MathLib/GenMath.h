#pragma once
#include <iostream>
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
//#include "MathLib.h"
//Varible Definitions
constexpr auto yEpsilon = 1.0e-6f;
const float yPi = 3.14159265f;
const float y2Pi = yPi * 2.0f;
const float yPiBy2 = yPi / 2.0f;
const float y1ByPi = 1.0f / yPi;
const float y1By2Pi = 1.0f / y2Pi;
namespace MathLib {
    //General Functions
    inline bool IsZero(float a, float epsilon = yEpsilon) {
        return (abs(a) <= epsilon);
    }
    inline bool AreEqual(float a, float b, float epsilon = yEpsilon) {
        return (abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f));
    }
    inline void SinCos(float* outSin, float* outCos, float theta) {
        *outSin = sin(theta);
        *outCos = cos(theta);
    }
    //wraps theta between -yPi and yPi
    inline float WrapPi(float theta) {
        //floor((theta + 180)/360) => if (between -180 - 180) will return 0
        theta += yPi;
        //gets value between 0 - 360
        theta -= floor(theta * y1By2Pi) * y2Pi;
        theta -= yPi;
        return theta;
    }
    //restricts a between -1 and 1 and applies acos
    inline float SafeACos(float a) {
        if (a <= -1.0f) return yPi;
        else if (a >= 1.0f) return 0;
        return acos(a);
    }
    inline float Sqrt(float a) {
        assert(a >= 0);
        return sqrt(a);
    }
    class YMath {
    public:
        static float Max(float a, float b) {
            return std::max(a, b);
        }
        static float Min(float a, float b) {
            return std::min(a, b);
        }
        static float Abs(float a) {
            return abs(a);
        }
        static bool IsZero(float a, float epsilon = yEpsilon) {
            return (abs(a) <= epsilon);
        }
        static bool IsNearlyZero(float a, float epsilon) {
            return IsZero(a, epsilon);
        }
        static float Clamp(float a, float min, float max) {
            if (a < min) a = min;
            if (a > max) a = max;
            return a;
        }
        static bool IsNaN(float a) {
            if (isnan(a)) {
                return true;
            }
            return false;
        }
        static float ACos(float a) {
            if (a <= -1.0f) return yPi;
            else if (a >= 1.0f) return 0;
            return acos(a);
        }
        static float ASin(float a) {
            if (a <= -1.0f) return -yPiBy2;
            else if (a >= 1.0f) return yPiBy2;
            return asin(a);
        }
        static float Cos(float a) {
            return cos(a);
        }
        static float Sin(float a) {
            return sin(a);
        }
        static float Tan(float a) {
            return sin(a);
        }
        static float DegToRad(float deg) {
            return deg * (yPi / 180.0f);
        }
        static float RadToDeg(float rad) {
            return rad * (180.0f / yPi);
        }
        static float Round(float a) {
            return round(a);
        }
        static float Sqrt(float a) {
            return sqrt(a);
        }
    };
}
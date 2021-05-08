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
    inline bool IsZero(float a) {
        return (abs(a) <= yEpsilon);
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
        theta -= floor(theta / y1By2Pi) * y2Pi;
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
        static const float posInf;
        static const float negInf;
        static const float Max(float a, float b);
        static const float Min(float a, float b);
        static const float Abs(float a);
        static const bool IsZero(float hel, float epsilon = yEpsilon) {
            return (abs(hel) <= epsilon);
        }
        static const bool AreEqual(float a, float b, float epsilon = yEpsilon) {
            return (abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f));
        }
        static const bool IsNearlyZero(float a, float epsilon);
        static const bool AreNearlyEqual(float a, float b, float epsilon);
        static const float Clamp(float a, float min, float max);
        static const bool IsNaN(float a);
        static const float ACos(float a);
        static const float ASin(float a);
        static const float ATan(float a);
        static const float ATan2(float a, float b);
        static const float Cos(float a);
        static const float Sin(float a);
        static const float Tan(float a);
        static const float DegToRad(float deg);
        static const float RadToDeg(float rad);
        static const float Round(float a);
        static const float Sqrt(float a);
        static const void SinCos(float* outSin, float* outCos, float theta) {
            *outSin = sin(theta);
            *outCos = cos(theta);
        }
        static const float WrapAngle(float theta, float lowLim, float upLim);
        static const float Log(float a);
        static const float Log2(float a);
        static const float Log10(float a);
        static const float Exp(float a);
        static const float Floor(float a);
        static const float GridSnapHelp(float a, float gridSize);
    };
}
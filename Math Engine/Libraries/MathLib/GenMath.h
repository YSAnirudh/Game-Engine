#pragma once
#include <iostream>
#include <math.h>
#include <assert.h>
#include "MathLib.h"
//Varible Definitions
constexpr auto yEpsilon = 1.0e-6f;
const float yPi = 3.14159265f;
const float y2Pi = yPi * 2.0f;
const float yPiBy2 = yPi / 2.0f;
const float y1ByPi = 1.0f / yPi;
const float y1By2Pi = 1.0f / y2Pi;
namespace MathLib {
    //General Functions
    inline bool isZero(float a, float epsilon = yEpsilon) {
        return (abs(a) <= epsilon);
    }
    inline bool areEqual(float a, float b, float epsilon = yEpsilon) {
        return (abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f));
    }
    inline void sinCos(float* outSin, float* outCos, float theta) {
        *outSin = sin(theta);
        *outCos = cos(theta);
    }
    //wraps theta between -yPi and yPi
    inline float wrapPi(float theta) {
        //floor((theta + 180)/360) => if (between -180 - 180) will return 0
        theta += yPi;
        //gets value between 0 - 360
        theta -= floor(theta * y1By2Pi) * y2Pi;
        theta -= yPi;
        return theta;
    }
    //restricts a between -1 and 1 and applies acos
    inline float safeACos(float a) {
        if (a <= -1.0f) return yPi;
        else if (a >= 1.0f) return 0;
        return acos(a);
    }
    inline float Sqrt(float a) {
        assert(a >= 0);
        return sqrt(a);
    }
}
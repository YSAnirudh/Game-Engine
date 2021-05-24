#pragma once
#include <iostream>
#include "EulerAngles.h"
#include "GenMath.h"
#include "Matrix3x3.h"
//#include "Matrix4x3.h"
#include "Matrix4x4.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Ray3D.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
//#include "Line3D.h"
using namespace std;
using namespace MathLib;
// /FORCE:MULTIPLE /IGNORE:4006 
void printVec2(YVec2 a) {
	std::cout << "X: " <<  a.x << ",Y: " << a.y << std::endl;
}
void printVec3(YVec2 a) {
	std::cout << "X: " << a.x << ",Y: " << a.y << std::endl;
}
int main() {
	YVec2 a = YVec2(YVec4(1,2,4,5));

	float length;
	YVec2 b(2,3);
	cout << YVec2::Magnitude(a) << endl;
	return 0;
}
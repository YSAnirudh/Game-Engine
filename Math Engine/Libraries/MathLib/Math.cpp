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
void printVec(YVec3 a) {
	std::cout << "X: " <<  a.x << ",Y: " << a.y << ",Z: " << a.z << std::endl;
}
int main() {
	YVec3 rotateThis = YVec3(1.0f, 1.0f, 2.0f);
	YQuat q = YQuat(1,1,1,1);
	rotateThis = q.RotateVector(rotateThis);
	printVec(rotateThis);
	return 0;
}
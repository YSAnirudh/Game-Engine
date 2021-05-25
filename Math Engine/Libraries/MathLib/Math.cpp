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
void printVec3(YVec3 a) {
	std::cout << "X: " << a.x << ",Y: " << a.y << ", Z:" <<  a.z << std::endl;
}
void printQuat(YQuat q) {
	std::cout << q.x << " " << q.y << " " << q.z << " " << q.w << " " << std::endl;
}
void printEuler(YQuat q) {
	std::cout << q.x << " " << q.y << " " << q.z << " " << q.w << " " << std::endl;
}

int main() {
	YVec3 a = YVec3(YVec3(1,1,0));
	YVec3 hello;
	float length;
	a.ToDirectionAndLength(hello, length);

	printVec3(hello);
	cout << length << endl;
	return 0;
}
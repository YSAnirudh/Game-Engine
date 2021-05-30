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
void printVec4(YVec4 a) {
	std::cout << "X: " << a.x << ",Y: " << a.y << ", Z:" << a.z << ", W:" << a.w << std::endl;
}
void printQuat(YQuat q) {
	std::cout << q.w << " " << q.x << " " << q.y << " " << q.z << " " << std::endl;
}
void printEuler(YEuler E) {
	std::cout << E.roll << " " << E.pitch << " " << E.yaw << std::endl;
}

void printMatrix4(YMat4x4 m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << m.m[i][j] << " " << std::flush;
		}
		std::cout << std::endl;
	}
}

void printMatrix3(YMat3x3 m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << m.m[i][j] << " " << std::flush;
		}
		std::cout << std::endl;
	}
}

int main() {
	YQuat quat1 = YQuat(0.9702957f, 0, 0, -0.2419219f);
	YMat4x4 mat1 = YMat4x4();
	mat1.SetupRotation(0, 0, -28);
	YQuat quat2 = YQuat(mat1);

	printQuat(quat1);
	printQuat(quat2);
	return 0;
}
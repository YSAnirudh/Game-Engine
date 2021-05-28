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
	std::cout << q.x << " " << q.y << " " << q.z << " " << q.w << " " << std::endl;
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
	YMat4x4 m4 = YMat4x4(YMat4x4(
		YVec4(YVec3(0.8823529, 0.4705882, 0).GetSafeNormal(), 4),
		YVec4(YVec3(-0.4705882, 0.8823529, 0).GetSafeNormal(), 8),
		YVec4(YVec3(0, 0, 1).GetSafeNormal(), 12),
		YVec4(YVec3(13, 14, 15).GetSafeNormal(), 16)
	));
	
	std::cout << YVec3(1, 2, 3).GetSafeNormal().Magnitude() << std::endl;
	YMat4x4 m1 = YMat4x4(YMat4x4(YVec4(1, 2, 3, 4), YVec4(4, 5, 6, 7), YVec4(8, 7, 9, 10), YVec4(13, 14, 15, 16)));;
	
	//m1 = m4;
	//printMatrix4(m4 = m1);
	//m4.Transpose();
	printMatrix4(m4);
	printVec3(m1.GetScaledVector());
	m1.RemoveScaling(yEpsilon);
	printVec3(m1.GetScaledVector());
	//printVec4(YVec4(1, 2, 3, 4) * m4);
	cout << m4.Determinant() << endl;
	return 0;
}
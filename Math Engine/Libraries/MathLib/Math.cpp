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
	std::cout << "Roll (Z):" << E.roll << " " << "Pitch (X):" << E.pitch << " " << "Yaw (Y):" << E.yaw << std::endl;
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
	YQuat quat1 = YQuat(0.8535534 ,-0.1464466, 0.3535534, 0.3535534); //yz45
	//YQuat quat1 = YQuat(0.8535534, -0.1464466, 0.3535534, 0.3535534); //xyz45
	//quat1.RotationY(60);
	YQuat quat2 = YQuat(YEuler(0,79.3,0));
	//YQuat quat2 = YQuat(YEuler(12, 0, 0));
	YMat4x4 mat1 = YMat4x4();
	YMat4x4 mat2 = YMat4x4();
	mat2.SetupRotation(quat1);
	mat1.SetupRotation(30, 54.7356, -35.2644);
	YVec3 rohan = YVec3(1, 1, 1);
	float angle = 64.7368256f;
	//printQuat(YQuat(mat2.Rotation()));
	printQuat(quat1);
	printEuler(quat2.Rotation());
	printQuat(quat2);
	printVec3(mat1.TransformVec3(rohan));
	printQuat(YQuat(mat1));

	//std::cout << Angle << std::endl;
	return 0;
}
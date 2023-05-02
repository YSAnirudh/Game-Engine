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

#include <time.h>

using namespace std;
using namespace YSAoo;

#define maxCount 10000000
// /FORCE:MULTIPLE /IGNORE:4006

int main() {
	YMat4x4 a = YMat4x4::Identity;
	
	YVec4 vec = YVec4(1.0f, 0.0f, 0.0f, 1.0f);
	long time1 = clock();
	for (int i = 0; i < maxCount; i++) {
		a = a.ApplyTranslation(YVec3(1.0f, 1.0f, 1.0f));

		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << a.m[i][j] << " " << std::flush;
			}
			std::cout << std::endl;
		}*/


		vec = a.TransformVec4(vec);
	}

	cout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << endl;

	long time2 = clock();
	cout << "Time Taken: " << time2 - time1 << endl;
	return 0;
}
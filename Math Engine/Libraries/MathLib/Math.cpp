#include <iostream>
#include "MathLib.h"
using namespace std;
using namespace MathLib;

void printVec(YVec3 a) {
	cout << "X: " <<  a.x << ",Y: " << a.y << ",Z: " << a.z << endl;
}
int main() {
	YVec3 a(1.0, 1.0, 0.0);
	YVec3 b(1, 2, 3);

	YVec3 c = 5.0f * a;
	YVec3& temp = c;
	float angle = 0;
	printVec(a);
	YMat4x4 mat;
	mat.getAxisAngle(a, angle);
	//temp.normalize();
	cout << angle << endl;
	return 0;
}
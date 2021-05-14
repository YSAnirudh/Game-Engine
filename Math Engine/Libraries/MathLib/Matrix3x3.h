#pragma once

namespace MathLib {
	class YEuler;
	class YMat4x3;
	class YQuat;
	class YVec3;
	class YMat4x4;
	class YMat3x3 {
	public:
		float m[3][3];
		//
		// CONSTRUCTOR OVERLOADS START
		//

		// 0mat constructor
		YMat3x3();
		// Constructor - 1 YMat4x4 (ROW WISE Assignment)
		// Initializes rows to corresponding rows in YMat4x4
		YMat3x3(const YMat3x3 &InMat3x3);
		// Constructor - 1 YMat3x3 (ROW WISE Assignment)
		// Initializes rows to corresponding rows in YMat3x3
		// Leaves out other columns to be zero and (4,4) to be 1
		YMat3x3(const YMat4x4 &InMat4x4);
		////value constructor
		//YMat3x3(const float& m11, const float& m12, const float& m13,
		//	const float& m21, const float& m22, const float& m23,
		//	const float& m31, const float& m32, const float& m33);
		// 3 vectors
		YMat3x3(const YVec3 &InX, const YVec3 &InY, const YVec3 &InZ);

		//
		// CONSTRUCTOR OVERLOADS END
		//

		//
		// OPERATORS START
		//
		void operator=(const YMat3x3 &Other);
		bool operator==(const YMat3x3 &Other);
		bool operator!=(const YMat3x3 &Other);
		//+, +=, *, *=, - , -=
		YMat3x3 operator+(const YMat3x3 &Other) const;
		YMat3x3 operator+=(const YMat3x3 &Other);
		YMat3x3 operator-() const;
		YMat3x3 operator-(const YMat3x3 &Other) const;
		YMat3x3 operator-=(const YMat3x3 &Other);
		YMat3x3 operator*(const YMat3x3 &Other) const;
		YMat3x3 operator*=(const YMat3x3 &Other);
		YMat3x3 operator*(const float Scalar) const;
		friend YMat3x3 operator*(float Scalar, const YMat3x3 &Other);
		YMat3x3 operator*=(float Scalar);
		// Operator - (row,column) Accessor
		float &operator()(unsigned int i, unsigned int j);
		// Operator - (row,column) Accessor
		float operator()(unsigned int i, unsigned int j) const;
		YVec3 operator*(const YVec3 &Vector) const;
		friend YVec3 operator*(const YVec3 &Vector, const YMat3x3 &Matrix);
		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//
		void Transpose();
		float Determinant() const;
		float GetCofactor(int IndexI, int IndexJ) const;
		YMat3x3 Adjoint() const;
		YMat3x3 Inverse() const;
		//Assumes det 1 check once
		YMat3x3 InverseFast() const;

		void ToIdentity();
		YEuler Rotation() const;
		void SetupRotation(const YMat3x3 &Matrix);
		void SetupRotation(const YQuat &Rotate);
		void SetupRotation(float xRotation, float yRotation, float zRotation);
		void SetupRotation(const YVec3 &Axis, float Angle);
		void SetupRotation(const YEuler &Euler);
		void SetupRotationX(float xAngle);
		void SetupRotationY(float yAngle);
		void SetupRotationZ(float zAngle);
		void SetupScale(float Scale);
		void SetupScale(const YVec3 &Scale);
		void SetupProject(const YVec3 &Normal);
		YMat3x3 ApplyRotation(const YMat3x3 &Matrix) const;
		YMat3x3 ApplyRotation(const YQuat &Rotate) const;
		YMat3x3 ApplyRotation(float xRotation, float yRotation, float zRotation) const;
		YMat3x3 ApplyRotation(const YVec3 &Axis, float Angle) const;
		YMat3x3 ApplyRotation(const YEuler &Euler) const;
		YMat3x3 ApplyRotationX(float xAngle) const;
		YMat3x3 ApplyRotationY(float yAngle) const;
		YMat3x3 ApplyRotationZ(float zAngle) const;
		YMat3x3 ApplyScale(float Scale) const;
		YMat3x3 ApplyScale(const YVec3 &Scale) const;
		YMat3x3 ApplyProject(const YVec3 &Normal) const;
		YVec3 GetColumn(int i) const;
		YVec3 GetRow(int i) const;
		void SetColumn(int i, YVec3 Value);
		void SetRow(int i, YVec3 Value);
		/*void fromInertialToObjectQuaternion(const YQuat& quat);
		void fromObjectToInertialQuaternion(const YQuat& quat);

		YVec3 fromInertialToObject(const YVec3& vec);
		YVec3 fromObjectToInertial(const YVec3& vec);*/
		// Static Functions

		//
		// FUNCTIONS END
		//

		//
		// STATIC VARIABLES START
		//

		static const YMat3x3 Identity;

		//
		// STATIC VARIABLES END
		//
	};
}
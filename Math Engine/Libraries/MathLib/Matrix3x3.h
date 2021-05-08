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
		inline YMat3x3(const YMat3x3 &InMat3x3);
		// Constructor - 1 YMat3x3 (ROW WISE Assignment)
		// Initializes rows to corresponding rows in YMat3x3
		// Leaves out other columns to be zero and (4,4) to be 1
		inline YMat3x3(const YMat4x4 &InMat4x4);
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
		inline void operator=(const YMat3x3 &Other);
		inline bool operator==(const YMat3x3 &Other);
		inline bool operator!=(const YMat3x3 &Other);
		//+, +=, *, *=, - , -=
		inline YMat3x3 operator+(const YMat3x3 &Other) const;
		inline YMat3x3 operator+=(const YMat3x3 &Other);
		inline YMat3x3 operator-() const;
		inline YMat3x3 operator-(const YMat3x3 &Other) const;
		inline YMat3x3 operator-=(const YMat3x3 &Other);
		inline YMat3x3 operator*(const YMat3x3 &Other) const;
		inline YMat3x3 operator*=(const YMat3x3 &Other);
		inline YMat3x3 operator*(const float Scalar) const;
		inline friend YMat3x3 operator*(float Scalar, const YMat3x3 &Other);
		inline YMat3x3 operator*=(float Scalar);
		// Operator - (row,column) Accessor
		inline float &operator()(unsigned int i, unsigned int j);
		// Operator - (row,column) Accessor
		inline float operator()(unsigned int i, unsigned int j) const;
		inline YVec3 operator*(const YVec3 &Vector) const;
		inline friend YVec3 operator*(const YVec3 &Vector, const YMat3x3 &Matrix);
		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//
		inline void Transpose();
		inline float Determinant() const;
		inline float GetCofactor(int IndexI, int IndexJ) const;
		inline YMat3x3 Adjoint() const;
		inline YMat3x3 Inverse() const;
		//Assumes det 1 check once
		inline YMat3x3 InverseFast() const;

		inline void ToIdentity();
		inline YEuler Rotation() const;
		inline void SetupRotation(const YQuat &Quaternion);
		inline void SetupRotation(const YMat3x3 &Matrix);
		inline void SetupRotation(const YQuat &Rotate);
		inline void SetupRotation(float xRotation, float yRotation, float zRotation);
		inline void SetupRotation(const YVec3 &Axis, float Angle);
		inline void SetupRotation(const YEuler &Euler);
		inline void SetupRotationX(float xAngle);
		inline void SetupRotationY(float yAngle);
		inline void SetupRotationZ(float zAngle);
		inline void SetupScale(float Scale);
		inline void SetupScale(const YVec3 &Scale);
		inline void SetupProject(const YVec3 &Normal);
		inline YMat3x3 ApplyRotation(const YMat3x3 &Matrix) const;
		inline YMat3x3 ApplyRotation(const YQuat &Rotate) const;
		inline YMat3x3 ApplyRotation(float xRotation, float yRotation, float zRotation) const;
		inline YMat3x3 ApplyRotation(const YVec3 &Axis, float Angle) const;
		inline YMat3x3 ApplyRotation(const YEuler &Euler) const;
		inline YMat3x3 ApplyRotationX(float xAngle) const;
		inline YMat3x3 ApplyRotationY(float yAngle) const;
		inline YMat3x3 ApplyRotationZ(float zAngle) const;
		inline YMat3x3 ApplyScale(float Scale) const;
		inline YMat3x3 ApplyScale(const YVec3 &Scale) const;
		inline YMat3x3 ApplyProject(const YVec3 &Normal) const;
		inline YVec3 GetColumn(int i) const;
		inline YVec3 GetRow(int i) const;
		inline void SetColumn(int i, YVec3 Value);
		inline void SetRow(int i, YVec3 Value);
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
#pragma once
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include "GenMath.h"
#include <immintrin.h>
#include <xmmintrin.h>
namespace MathLib{
	class YEuler;
	class YMat4x3;
	class YQuat;
	class YMat3x3 {
	public:
		float
			m11, m12, m13,
			m21, m22, m23,
			m31, m32, m33;
		//
		// Constructors START
		//
		
		// 0mat constructor
		YMat3x3();

		//value constructor
		YMat3x3(const float& m11, const float& m12, const float& m13,
			const float& m21, const float& m22, const float& m23,
			const float& m31, const float& m32, const float& m33);
		
		
		// take in matrix
		YMat3x3(const YMat3x3& a);

		// 3 vectors
		YMat3x3(const YVec3& a, const YVec3& b, const YVec3& c);
		// Constructors END

		//
		// Operators START
		//
		inline YMat3x3& operator=(const YMat3x3& a);
		//+, +=, *, *=, - , -=
		inline YMat3x3 operator+(const YMat3x3& a);
		inline YMat3x3 operator+=(const YMat3x3& a);
		inline YMat3x3 operator-(const YMat3x3& a);
		inline YMat3x3 operator-=(const YMat3x3& a);
		inline YMat3x3 operator*(const YMat3x3& b);
		inline YMat3x3 operator*=(const YMat3x3& b);
		inline YMat3x3 operator*(const float& mult);
		inline friend YMat3x3 operator*(const YMat3x3& a, const float& mult);
		inline friend YMat3x3 operator*(const float& mult, const YMat3x3& a);
		inline YMat3x3 operator/(const float& b);
		inline YMat3x3 operator/=(const float& b);
		YVec3 operator*(const YVec3& vector) const;
		friend YVec3 operator*(const YVec3& vector, const YMat3x3& matrix);
		//Operators END

		//
		// Functions START
		//
		void transpose();
		float determinant();
		void cofactor();
		void adjoint();
		void inverse();

		void setToIdentity();

		void setup(const YEuler& orien);

		void fromInertialToObjectQuaternion(const YQuat& quat);
		void fromObjectToInertialQuaternion(const YQuat& quat);

		YVec3 fromInertialToObject(const YVec3& vec);
		YVec3 fromObjectToInertial(const YVec3& vec);
		// Functions END
	};
	//
	// Non Member Functions START
	//

	// Non Member functions END
}
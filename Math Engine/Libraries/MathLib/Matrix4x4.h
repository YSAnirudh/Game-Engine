#pragma once
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector4D.h"
#include "GenMath.h"
namespace MathLib {
	class YMat3x3;
	class YQuat;
	class YMat4x4 {
	public:
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;
		YMat4x4();
		
		float& operator()(unsigned int i, unsigned int j);
		float operator()(unsigned int i, unsigned int j) const;
		bool operator==(const YMat4x4& other) const;
		bool operator!=(const YMat4x4& other) const;

		bool zero() const;
		bool isIdentity() const;

		YMat4x4& affineInverse();

		YMat4x4& transpose();
		friend YMat4x4 transpose(const YMat4x4& mat);

		YMat4x4& translation(const YVec3& xlate);
		YMat4x4& rotation(const YMat3x3& matrix);
		YMat4x4& rotation(const YQuat& rotate);
		YMat4x4& rotation(float zRotation, float yRotation, float xRotation);
		YMat4x4& rotation(const YVec3& axis, float angle);

		YMat4x4& scaling(const YVec3& scale);

		YMat4x4& rotationX(float angle);
		YMat4x4& rotationY(float angle);
		YMat4x4& rotationZ(float angle);

		void getFixedAngles(float& zRotation, float& yRotation, float& xRotation);
		void getAxisAngle(YVec3& axis, float& angle);
		YMat4x4& operator=(const YMat4x4& other);
		YMat4x4 operator+(const YMat4x4& other) const;
		YMat4x4& operator+=(const YMat4x4& other);
		YMat4x4 operator-(const YMat4x4& other) const;
		YMat4x4& operator-=(const YMat4x4& other);

		YMat4x4 operator-() const;

		// multiplication
		YMat4x4& operator*=(const YMat4x4& matrix);
		YMat4x4 operator*(const YMat4x4& matrix) const;

		// column vector multiplier
		YVec4 operator*(const YVec4& vector) const;
		// row vector multiplier
		friend YVec4 operator*(const YVec4& vector, const YMat4x4& matrix);

		YMat4x4& operator*=(float scalar);
		friend YMat4x4 operator*(float scalar, const YMat4x4& matrix);
		YMat4x4 operator*(float scalar) const;

		// vector3 ops
		YVec3 transform(const YVec3& point) const;

		// point ops
		YVec3 transformPoint(const YVec3& point) const;
	};
	YMat4x4 affineInverse(const YMat4x4& mat);
	YMat4x4 transpose(const YMat4x4& mat);
	inline float& YMat4x4::operator()(unsigned int i, unsigned int j)
	{
		if (i == 1) {
			if (j == 1) {
				return m11;
			}
			else if (j == 2) {
				return m12;
			}
			else if (j == 3) {
				return m13;
			}
			else if (j == 4) {
				return m14;
			}
		} else if (i == 2) {
			if (j == 1) {
				return m21;
			}
			else if (j == 2) {
				return m22;
			}
			else if (j == 3) {
				return m23;
			}
			else if (j == 4) {
				return m24;
			}
		} else if (i == 3) {
			if (j == 1) {
				return m31;
			}
			else if (j == 2) {
				return m32;
			}
			else if (j == 3) {
				return m33;
			}
			else if (j == 4) {
				return m34;
			}
		} else if (i == 4) {
			if (j == 1) {
				return m41;
			}
			else if (j == 2) {
				return m42;
			}
			else if (j == 3) {
				return m43;
			}
			else if (j == 4) {
				return m44;
			}
		}
	}
	
	inline float YMat4x4::operator()(unsigned int i, unsigned int j) const
	{
		if (i == 1) {
			if (j == 1) {
				return m11;
			}
			else if (j == 2) {
				return m12;
			}
			else if (j == 3) {
				return m13;
			}
			else if (j == 4) {
				return m14;
			}
		}
		else if (i == 2) {
			if (j == 1) {
				return m21;
			}
			else if (j == 2) {
				return m22;
			}
			else if (j == 3) {
				return m23;
			}
			else if (j == 4) {
				return m24;
			}
		}
		else if (i == 3) {
			if (j == 1) {
				return m31;
			}
			else if (j == 2) {
				return m32;
			}
			else if (j == 3) {
				return m33;
			}
			else if (j == 4) {
				return m34;
			}
		}
		else if (i == 4) {
			if (j == 1) {
				return m41;
			}
			else if (j == 2) {
				return m42;
			}
			else if (j == 3) {
				return m43;
			}
			else if (j == 4) {
				return m44;
			}
		}

	}
}
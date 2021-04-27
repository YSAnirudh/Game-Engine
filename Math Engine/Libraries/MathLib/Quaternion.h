#pragma once

namespace MathLib {
	class YEuler;
	class YMat4x3;
	class YMat3x3;
	class YMat4x4;
	class YVec3;
	class YQuat {
	public:
		float w, x, y, z;

		//
		// Constructor overloads
		//
		YQuat();
		YQuat(float InW, float InX, float InY, float InZ);
		YQuat(const YMat4x4& M);
		YQuat(const YMat3x3& M);
		YQuat(const YEuler& E);
		YQuat(const YVec3& Axis, float AngleDeg);


		//
		// Operators START
		//
		//Cross product
		inline bool operator==(const YQuat& Q) const;
		inline bool operator!=(const YQuat& Q) const;
		inline YQuat operator+(const YQuat& Q) const;
		inline YQuat operator+=(const YQuat& Q);
		inline YQuat operator-(const YQuat& Q) const;
		inline YQuat operator-=(const YQuat& Q);

		inline YVec3 operator*(const YVec3& V) const;
		inline YMat3x3 operator*(const YMat3x3& M) const;
		inline YMat4x4 operator*(const YMat4x4& M) const;
		inline YQuat operator*(const YQuat& Q) const;
		inline YQuat operator*=(const YQuat& Q);
		inline YQuat operator*(const float Scale) const;
		inline YQuat operator*=(const float Scale);

		inline YQuat operator/(const float Scale) const;
		inline YQuat operator/=(const float Scale);

		inline float operator|(const YQuat& Q) const;

		// Operators END

		//
		// Functions START
		//
		inline void conjugate();
		void setToIdentity();
		void normalize();
		float getRotationAngle() const;
		YVec3 getRotationAxis() const;
		void rotationX(float theta);
		void rotationY(float theta);
		void rotationZ(float theta);
		void axisAngle(const YVec3& axis, float theta);

		void setToRotateObjectToInertial(const YEuler& orientation);
		void setToRotateInertialToObject(const YEuler& orientation);

		bool isUnit() const;
		// Functions END
	};
	class YQuat;
	//
	// Non Member Functions START
	//
	// Quaternion dot product
	extern float dotProduct(const YQuat& p, const YQuat& q);
	// Quaternion cross product
	extern YQuat crossProduct(const YQuat& p, const YQuat& q);
	// Spherical Linear Interpolation
	extern YQuat slerp(const YQuat& p, const YQuat& q, float t);
	// Quaternion conjugation
	extern YQuat conjugate(const YQuat& q);
	// Quaternion exponentiation
	extern YQuat pow(const YQuat& q, float exponent);

	// Non Member Functions END
}
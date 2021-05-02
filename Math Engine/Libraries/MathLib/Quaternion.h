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
		YQuat(float InW, const YVec3& InXYZ);


		//
		// Operators START
		//
		//Cross product
		inline bool operator==(const YQuat& Q) const;
		inline bool operator!=(const YQuat& Q) const;
		inline YQuat operator+(const YQuat& Q) const;
		inline YQuat operator+=(const YQuat& Q);
		inline YQuat operator-() const;
		inline YQuat operator-(const YQuat& Q) const;
		inline YQuat operator-=(const YQuat& Q);

		inline YVec3 operator*(const YVec3& V) const;
		inline friend YVec3 operator*(const YVec3& V, const YQuat& Q);
		inline YMat3x3 operator*(const YMat3x3& M) const;
		inline YMat4x4 operator*(const YMat4x4& M) const;
		inline YQuat operator*(const YQuat& Q) const;
		inline YQuat operator*=(const YQuat& Q);
		inline YQuat operator*(const float Scale) const;
		inline friend YQuat operator*(const float Scale, const YQuat& Q);
		inline YQuat operator*=(const float Scale);

		inline YQuat operator/(const float Scale) const;
		inline YQuat operator/=(const float Scale);

		inline float operator|(const YQuat& Q) const;

		// Operators END

		//
		// Functions START
		//
		inline float GetRotationAngle() const;
		inline YVec3 GetRotationAxis() const;

		inline float GetAngle() const;
		inline YVec3 GetAxisX() const;
		inline YVec3 GetAxisY() const;
		inline YVec3 GetAxisZ() const;
		inline YVec3 GetForwardVector() const;
		inline YVec3 GetUpVector() const;
		inline YVec3 GetRightVector() const;
		inline YQuat GetNormalized(float Tolerance) const;
		inline float GetTwistAngle(const YVec3& TwistAxis) const;

		inline float AngularDistance(const YQuat& Q) const;
		inline bool ContainsNan() const;
		inline bool Equals(const YQuat& Q, float Tolerance) const;
		//inline YEuler Euler() const;
		inline bool IsIdentity(float Tolerance) const;
		inline bool IsNormalized() const;
		inline YQuat Log() const;
		inline YQuat Exp() const;
		inline YVec3 RotateVector(YVec3 V) const;
		inline YEuler Rotation() const;
		inline float Magnitude() const;
		inline float MagnitudeSquared() const;
		inline YVec3 UnrotateVector(YVec3 V) const;
		inline YVec3 Vector() const;
		inline YQuat Conjugate() const;

		inline void ToAxisAngle(YVec3& Axis, float& Angle);
		inline void EnforceShortestArcWith(const YQuat& Other);
		inline void Conjugate(); //Inverse
		inline void ToIdentity();
		inline void Normalize();
		inline void RotationX(float theta);
		inline void RotationY(float theta);
		inline void RotationZ(float theta);

		static YQuat FastBilerp(
			const YQuat& P00, 
			const YQuat& P10, 
			const YQuat& P01, 
			const YQuat& P11, 
			float FracX,
			float FracY
		);
		static YQuat FastLerp(const YQuat& A, const YQuat& B, const float Alpha);
		static YQuat FindBetween(const YVec3& Vector1, const YVec3& Vector2);
		static YQuat FindBetweenNormals(const YVec3& Normal1, const YVec3& Normal2);
		static YQuat FindBetweenVectors(const YVec3& Vector1, const YVec3& Vector2);
		static YQuat MakeFromEuler(const YEuler& Euler);
		static YQuat MakeFromAxisAngle(const YVec3& axis, float theta);
		static YQuat Slerp(const YQuat& Quat1, const YQuat& Quat2, float Slerp);
		static YQuat SlerpUnNormalized(const YQuat& Quat1, const YQuat& Quat2, float Slerp);
		static YQuat SlerpFullPath(const YQuat& Quat1, const YQuat& Quat2, float Alpha);
		static YQuat SlerpFullPathUnNormalized(const YQuat& Quat1, const YQuat& Quat2, float Alpha);
		
		void setToRotateObjectToInertial(const YEuler& orientation);
		void setToRotateInertialToObject(const YEuler& orientation);

		bool isUnit() const;
		// Functions END
	};
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
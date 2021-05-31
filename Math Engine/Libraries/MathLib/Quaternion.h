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
		// CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes this to 0
		YQuat();
		// Contructor - 4 float Values
		// Initializes this with corresponding w,x,y,z
		YQuat(float InW, float InX, float InY, float InZ);

		// Constructor - YMat4x4
		// Initializes this with quaternion obtained from YMat4x4 M
		YQuat(const YMat4x4& M);
		
		// Constructor - YMat3x3
		// Initializes this with quaternion obtained from YMat3x3 M
		YQuat(const YMat3x3& M);

		// Constructor - Euler
		// Initializes this with quaternion obtained from Euler E
		YQuat(const YEuler& E);
		
		// Constructor - YVec3, float
		// Initializes this with quaternion obtained from Axis and AngleDeg
		YQuat(const YVec3& Axis, float AngleDeg);
		YQuat(float InW, const YVec3& InXYZ);

		//
		// CONSTRUCTOR OVERLOADS END
		//
		
		//
		// OPERATORS START
		//

		// ASSIGNMENT OPERATORS

		// Operator - Assignment
		YQuat operator=(const YQuat& Q);

		// RELATIONAL OPERATORS

		// Operator -> Equality 
		bool operator==(const YQuat& Q) const;
		// Operator -> Inequality
		bool operator!=(const YQuat& Q) const;

		// ARITHMETIC OPERATORS

		// Addition

		// Operator -> this + YQuat Q
		YQuat operator+(const YQuat& Q) const;
		// Operator -> this += YQuat Q
		YQuat operator+=(const YQuat& Q);
		
		// Subtraction
		
		// Operator -> Negation
		YQuat operator-() const;
		// Operator -> this - YQuat Q
		YQuat operator-(const YQuat& Q) const;
		// Operator -> this -= YQuat Q
		YQuat operator-=(const YQuat& Q);

		// Multiplication

		// Operator -> this * YVec3 V
		YVec3 operator*(const YVec3& V) const;
		// friend for this * YVec3 (YVec3 * this)
		friend YVec3 operator*(const YVec3& V, const YQuat& Q);
		// Operator -> this * YMat3x3 M
		YMat3x3 operator*(const YMat3x3& M) const;
		// Operator -> this * YMat4x4 M
		YMat4x4 operator*(const YMat4x4& M) const;
		// Operator -> this * YQuat Q
		YQuat operator*(const YQuat& Q) const;
		// Operator -> this *= YQuat Q
		YQuat operator*=(const YQuat& Q);
		// Operator -> this * Scale
		YQuat operator*(const float Scale) const;
		// friend for this * Scale (Scale * this)
		friend YQuat operator*(const float Scale, const YQuat& Q);
		// Operator -> this *= Scale
		YQuat operator*=(const float Scale);

		// Division

		// Operator -> this / Scale
		YQuat operator/(const float Scale) const;
		// Operator -> this /= Scale
		YQuat operator/=(const float Scale);

		// SPECIAL OPERATORS

		// Operator - Dot Product
		float operator|(const YQuat& Q) const;

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Const GET Functions
		float GetRotationAngle() const;
		YVec3 GetRotationAxis() const;

		float GetAngle() const;
		YVec3 GetAxisX() const;
		YVec3 GetAxisY() const;
		YVec3 GetAxisZ() const;
		YVec3 GetForwardVector() const;
		YVec3 GetUpVector() const;
		YVec3 GetRightVector() const;
		YQuat GetNormalized(float Tolerance) const;
		YQuat GetConjugate() const;
		YQuat GetInverse() const;
		float GetTwistAngle(const YVec3& TwistAxis) const;

		// Const Functions
		float AngularDistance(const YQuat& Q) const;
		bool ContainsNan() const;
		bool Equals(const YQuat& Q, float Tolerance) const;
		//YEuler Euler() const;
		bool IsIdentity(float Tolerance) const;
		bool IsNormalized() const;
		YQuat Log() const;
		YQuat Exp() const;
		YVec3 RotateVector(YVec3 V) const;
		YEuler Rotation() const;
		YMat4x4 RotationMatrix4() const;
		YMat3x3 RotationMatrix3() const;
		float Magnitude() const;
		float MagnitudeSquared() const;
		YVec3 UnrotateVector(YVec3 V) const;
		YVec3 Vector() const;

		// Non Const Functions
		void ToAxisAngle(YVec3& Axis, float& Angle);
		void EnforceShortestArcWith(const YQuat& Other);
		void Conjugate();
		void ToIdentity();
		void Normalize();
		void RotationX(float theta);
		void RotationY(float theta);
		void RotationZ(float theta);

		// Static Functions
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
		
		//
		// FUNCTIONS END
		//

		//
		// STATIC VARIABLES START
		//

		static const YQuat Identity;

		//
		// STATIC VARIABLES END
		//
	};
}
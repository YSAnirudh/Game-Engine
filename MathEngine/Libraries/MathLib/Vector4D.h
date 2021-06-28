#pragma once
#include "GenMath.h"

namespace YSAoo {
	// Foward Declarations
	// Vector 2D
	class YVec2;
	// Vector 3D
	class YVec3;
	// Quaternion
	class YQuat;
	// Euler Angles
	class YEuler;
	class YVec4 {
	public:
		float x, y, z, w;
		//
		//CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes x,y,z to 0.0f
		YVec4();

		// Constructor - 1 float value
		// Initializes x and y to InFloat
		YVec4(float InF);

		// Constructor - 4 float values
		// Initializes x, y, z to InX, InY, InZ
		YVec4(float InX, float InY, float InZ, float InW);

		// Constructor - 1 YVec4 reference
		// Initializes x, y, z, w to InVec4.x, InVec4.y, InVec4.z, InVec4.w
		YVec4(const YVec4& InVec4);

		// Constructor - 1 YVec3 reference, 1 float
		// Initializes x, y, z to InVec3.x, InVec3.y, InVec3.z, w to InW
		YVec4(const YVec3& InVec3, float InW);
		//One For Color

		// Constructor - 1 YVec2 reference, 2 floats
		// Initializes x, y to InVec2.x, InVec2.y, z, w to InZ, InW
		YVec4(const YVec2& InXY, const YVec2& InZW);

		//
		// CONSTRUCTOR OVERLOADS END
		//

		//
		// OPERATORS START
		//

		// ASSIGNMENT OPERATOR

		YVec4 operator=(const YVec4& Other);

		// COMPARISION OPERATORS

		// Operator -> Equality
		bool operator==(const YVec4& Other) const;
		// Operator -> Inequality
		bool operator!=(const YVec4& Other) const;
		// Operator -> Less than
		bool operator<(const YVec4& Other) const;
		// Operator -> Less than or Equal to 
		bool operator<=(const YVec4& Other) const;
		// Operator -> Greater than
		bool operator>(const YVec4& Other) const;
		// Operator -> Greater than or Equal to 
		bool operator>=(const YVec4& Other) const;

		// ARITHMETIC OPERATORS

		// Addition

		// Operator -> this + YVec4 V
		YVec4 operator+(const YVec4& V) const;
		// Operator -> this + float A
		YVec4 operator+(float A) const;
		// Operator -> this += YVec4 V
		YVec4 operator+=(const YVec4& V);
		// Operator -> this += float A
		YVec4 operator+=(float A);

		// Subtraction

		// Operator -> Negation
		YVec4 operator-() const;
		// Operator -> this - YVec4 V
		YVec4 operator-(const YVec4& V) const;
		// Operator -> this - float A
		YVec4 operator-(float A) const;
		// Operator -> this -= YVec4 V
		YVec4 operator-=(const YVec4& V);
		// Operator -> this -= float A
		YVec4 operator-=(float A);

		// Multiplication

		// Operator -> this * YVec4 V
		YVec4 operator*(const YVec4& V) const;
		// Operator -> this * A
		YVec4 operator*(float A) const;
		// Operator -> V * A (friend)
		//inline friend YVec4 operator*(const YVec4& a, const float& mult);
		// Operator -> A * V (friend)
		friend YVec4 operator*(float A, const YVec4& V);
		// Operator -> this *= YVec4 V
		YVec4 operator*=(const YVec4& V);
		// Operator -> this *= float A
		YVec4 operator*=(float A);

		// Division

		// Operator -> this / YVec4 V
		YVec4 operator/(const YVec4& V) const;
		// Operator -> this / float A
		YVec4 operator/(float A) const;
		// Operator -> this /= YVec4 V
		YVec4 operator/=(const YVec4& V);
		// Operator -> this /= A
		YVec4 operator/=(float A);

		// ACCESSING OPERATORS

		// Operator - [] Accessor
		float& operator[](unsigned int i) { return (&x)[i]; }
		// Operator - [] Accessor
		float operator[](unsigned int i) const { return (&x)[i]; }

		// SPECIAL OPERATORS

		// Operator - Dot Product
		float operator|(const YVec4& V) const;
		// Operator - Cross product
		YVec4 operator^(const YVec4& V) const;

		// IO OPERATORS
		friend std::ostream& operator<<(std::ostream& out, const YVec4& vec);
		friend std::istream& operator>>(std::istream& in, YVec4& vec);

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Const Functions
		bool ContainsNaN() const;
		bool Equals(const YVec4& V, float Tolerance = yEpsilon) const;
		void FindBestAxisVectors3(YVec3 &Axis1, YVec3& Axis2) const;
		bool IsNearlyZero3(float Tolerance = yEpsilon) const;
		bool IsUnit3(float LengthSquaredTolerance = yEpsilon) const;
		YVec4 Reflect3(const YVec4& Normal) const;
		YEuler Rotation() const;
		float Magnitude() const;
		float Magnitude3() const;
		float MagnitudeSquared() const;
		float MagnitudeSquared3() const;
		YQuat ToOrientationQuat() const;
		YEuler ToOrientationEuler() const;

		// Const GET Functions
		YVec4 GetSafeNormal(float Tolerance = yEpsilon) const;
		YVec4 GetUnsafeNormal3() const;

		// Non Const Functions
		void Set(float InX, float InY, float InZ, float InW);
		//
		// FUNCTIONS END
		//
	};

}
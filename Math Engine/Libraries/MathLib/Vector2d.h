#pragma once
#include "GenMath.h"
namespace MathLib {
	// Forward Declarations
	// Vector 3D
	class YVec3;
	// Vector 4D
	class YVec4;
	class YVec2 {
	public:
		float x, y;
		//
		// CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes x and y to 0.0f
		YVec2();

		// Constructor - 1 float value
		// Initializes x and y to InFloat
		YVec2(float InFloat);

		// Constructor - 2 float values
		// Initializes x to InX and y to InY
		YVec2(float InX, float InY);

		// Constructor - 1 YVec2 reference
		// Initializes x, y to InVec2.x, InVec2.y
		YVec2(const YVec2& InVec2);

		// Constructor - 1 YVec3 reference
		// Initializes x, y to InVec3.x, InVec3.y
		YVec2(const YVec3& InVec3);

		// Constructor - 1 YVec4 reference
		// Initializes x, y to InVec4.x, InVec4.y
		YVec2(const YVec4& InVec4);

		//
		// CONSTRUCTOR OVERLOADS END
		//
		
		//
		// OPERATORS START
		//
		
		// Operator - Assignment
		YVec2& operator=(const YVec2& V);

		// COMPARISION OPERATORS
		
		// Operator -> Equality 
		bool operator==(const YVec2& Other) const;	
		// Operator -> Inequality
		bool operator!=(const YVec2& Other) const;
		// Operator -> Less than
		bool operator<(const YVec2& Other) const;
		// Operator -> Less than or Equal to 
		bool operator<=(const YVec2& Other) const;
		// Operator -> Greater than
		bool operator>(const YVec2& Other) const;
		// Operator -> Greater than or Equal to 
		bool operator>=(const YVec2& Other) const;
		
		// ARITHMETIC OPERATORS
		
		// Addition

		// Operator -> this + YVec2 V
		YVec2 operator+(const YVec2& V) const;
		// Operator -> this + float A
		YVec2 operator+(float A) const;
		// Operator -> this += YVec2 V
		YVec2 operator+=(const YVec2& a);
		// Operator -> this += float A
		YVec2 operator+=(float A);
		
		// Subtraction

		// Operator -> Negation
		YVec2 operator-() const;
		// Operator -> this - YVec2 V
		YVec2 operator-(const YVec2& V) const;
		// Operator -> this - float A
		YVec2 operator-(float A) const;
		// Operator -> this -= YVec2 V
		YVec2 operator-=(const YVec2& V);
		// Operator -> this -= float A
		YVec2 operator-=(float A);

		// Multiplication

		// Operator -> this * YVec2 V
		YVec2 operator*(const YVec2& V) const;
		// Operator -> this * Scale
		YVec2 operator*(float Scale) const;
		// Operator -> V * Scale (friend)
		friend YVec2 operator*(YVec2& V, float Scale);
		// Operator -> Scale * V (friend)
		friend YVec2 operator*(float Scale, YVec2& V);
		// Operator -> this *= YVec2 V
		YVec2 operator*=(const YVec2& V);
		// Operator -> this *= float Scale
		YVec2 operator*=(float Scale);

		// Division

		// Operator -> this / YVec2 V
		YVec2 operator/(const YVec2& V) const;
		// Operator -> this / float Scale
		YVec2 operator/(float Scale) const;
		// Operator -> this /= YVec2 V
		YVec2 operator/=(const YVec2& V);
		// Operator -> this /= Scale
		YVec2 operator/=(float Scale);

		// ACCESSING OPERATORS

		// Operator - [] Accessor
		float& operator[](unsigned int i) { return (&x)[i]; }
		// Operator - [] Accessor
		float operator[](unsigned int i) const { return (&x)[i]; }

		// SPECIAL OPERATORS
		
		// Operator - Dot Product
		float operator|(const YVec2& V) const;
		// Operator - Cross product
		float operator^(const YVec2& V) const;

		// IO OPERATORS
		friend std::ostream& operator<<(std::ostream& out, const YVec2& vec);
		friend std::istream& operator>>(std::istream& in, YVec2& vec);

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Const Functions
		bool IsNearlyZero(float Tolerance = yEpsilon) const;
		bool IsZero() const;
		bool Equals(const YVec2& V, float Tolerance = yEpsilon) const;
		YVec2 ClampAxes(float MinAxisVal, float MaxAxisVal) const;
		bool ContainsNaN() const;
		YVec2 RoundToVector() const;
		float Magnitude() const;
		float MagnitudeSquared() const;
		void ToDirectionAndLength(YVec2& OutDir, float& OutLength) const;
		YVec3 SprericalToCartesian() const;

		// Const GET Functions
		YVec2 GetRotated(float AngleDeg) const;
		YVec2 GetSignVector() const;
		YVec2 GetSafeNormal(float Tolerance = yEpsilon) const;
		YVec2 GetAbs() const;
		float GetAbsMax() const;
		float GetMax() const;
		float GetMin() const;

		// Not Const Functions
		void Set(float InX, float InY);
		void Normalize(float Tolerance = yEpsilon);

		// Static Functions
		static YVec2 Max(const YVec2& A, const YVec2& B);
		static YVec2 Min(const YVec2& A, const YVec2& B);
		static float DotProduct(const YVec2& A, const YVec2& B);
		static float CrossProduct(const YVec2& A, const YVec2& B);
		static float Distance(const YVec2& V1, const YVec2& V2);
		static float DistanceSquared(const YVec2& V1, const YVec2& V2);
		static float Magnitude(const YVec2& V);

		//
		// FUNCTIONS END
		//

		//
		// STATIC VARIABLES START
		//

		static const YVec2 UnitVec2;
		static const YVec2 ZeroVec2;
		static const YVec2 Deg45Vec2;

		//
		// STATIC VARIABLES END
		//
	};

}

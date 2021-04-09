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
		inline YVec2();

		// Constructor - 1 float value
		// Initializes x and y to InFloat
		inline YVec2(float InFloat);

		// Constructor - 2 float values
		// Initializes x to InX and y to InY
		inline YVec2(float InX, float InY);

		// Constructor - 1 YVec2 reference
		// Initializes x, y to InVec2.x, InVec2.y
		inline YVec2(const YVec2& InVec2);

		// Constructor - 1 YVec3 reference
		// Initializes x, y to InVec3.x, InVec3.y
		inline YVec2(const YVec3& InVec3);

		// Constructor - 1 YVec4 reference
		// Initializes x, y to InVec4.x, InVec4.y
		inline YVec2(const YVec4& InVec4);

		//
		// CONSTRUCTOR OVERLOADS END
		//
		
		//
		// OPERATORS START
		//
		

		// Operator - Assignment
		inline YVec2 operator=(const YVec2& V);	

		// COMPARISION OPERATORS
		
		// Operator -> Equality 
		inline bool operator==(const YVec2& Other) const;	
		// Operator -> Inequality
		inline bool operator!=(const YVec2& Other) const;
		// Operator -> Less than
		inline bool operator<(const YVec2& Other) const;
		// Operator -> Less than or Equal to 
		inline bool operator<=(const YVec2& Other) const;
		// Operator -> Greater than
		inline bool operator>(const YVec2& Other) const;
		// Operator -> Greater than or Equal to 
		inline bool operator>=(const YVec2& Other) const;
		
		// ARITHMETIC OPERATORS
		
		// Addition

		// Operator -> this + YVec2 V
		inline YVec2 operator+(const YVec2& V) const;
		// Operator -> this + float A
		inline YVec2 operator+(float A) const;
		// Operator -> this += YVec2 V
		inline YVec2 operator+=(const YVec2& a);
		// Operator -> this += float A
		inline YVec2 operator+=(float A);
		
		// Subtraction

		// Operator -> Negation
		inline YVec2 operator-() const;
		// Operator -> this - YVec2 V
		inline YVec2 operator-(const YVec2& V) const;
		// Operator -> this - float A
		inline YVec2 operator-(float A) const;
		// Operator -> this -= YVec2 V
		inline YVec2 operator-=(const YVec2& V);
		// Operator -> this -= float A
		inline YVec2 operator-=(float A);

		// Multiplication

		// Operator -> this * YVec2 V
		inline YVec2 operator*(const YVec2& V) const;
		// Operator -> this * Scale
		inline YVec2 operator*(float Scale) const;
		// Operator -> V * Scale (friend)
		friend inline YVec2 operator*(YVec2& V, float Scale);
		// Operator -> Scale * V (friend)
		friend inline YVec2 operator*(float Scale, YVec2& V);
		// Operator -> this *= YVec2 V
		inline YVec2 operator*=(const YVec2& V);
		// Operator -> this *= float Scale
		inline YVec2 operator*=(float Scale);

		// Division

		// Operator -> this / YVec2 V
		inline YVec2 operator/(const YVec2& V) const;
		// Operator -> this / float Scale
		inline YVec2 operator/(float Scale) const;
		// Operator -> this /= YVec2 V
		inline YVec2 operator/=(const YVec2& V);
		// Operator -> this /= Scale
		inline YVec2 operator/=(float Scale);

		// ACCESSING OPERATORS

		// Operator - [] Accessor
		inline float& operator[](unsigned int i) { return (&x)[i]; }
		// Operator - [] Accessor
		inline float operator[](unsigned int i) const { return (&x)[i]; }

		// SPECIAL OPERATORS
		
		// Operator - Dot Product
		inline float operator|(const YVec2& V) const;
		// Operator - Cross product
		inline float operator^(const YVec2& V) const;

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Const Functions
		inline bool IsNearlyZero(float Tolerance) const;
		inline bool IsZero() const;
		inline bool Equals(const YVec2& V, float Tolerance) const;
		inline YVec2 ClampAxes(float MinAxisVal, float MaxAxisVal) const;
		inline bool ContainsNaN() const;
		inline YVec2 RoundToVector() const;
		inline float Magnitude() const;
		inline float MagnitudeSquared() const;
		inline void ToDirectionAndLength(YVec2& OutDir, float& OutLength) const;
		inline YVec3 SprericalToCartesian() const;

		// Const GET Functions
		inline YVec2 GetRotated(float AngleDeg) const;
		inline YVec2 GetSignVector() const;
		inline YVec2 GetSafeNormal(float Tolerance) const;
		inline YVec2 GetAbs() const;
		inline float GetAbsMax() const;
		inline float GetMax() const;
		inline float GetMin() const;

		// Not Const Functions
		inline void Set(float InX, float InY);
		inline void Normalize(float Tolerance);

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

		


		//Makes a vector2s 0
		inline void makeZero();
		//normalizes a vector2d
		inline void normalize();


		//DOT PRODUCT between two vector2ds
		inline float dot(const YVec2& a) const;
	};
	//
	// Non Member Functions
	//

	//calculates the magnitude of a vector2d
	extern inline float magnitude(const YVec2& a);
	//calculates the distance between two vector2ds
	extern inline float distance(const YVec2& a, const YVec2& b);
	//calculates the dot product between two vector2ds
	extern inline float dotProduct(const YVec2& a, const YVec2& b);
	//Non Member Functions END
}

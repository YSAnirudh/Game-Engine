#pragma once
#include "GenMath.h"
namespace MathLib {
	class YVec3;
	class YVec4;
	class YVec2 {
	public:
		float x, y;

		//
		// Constructor Overloads
		//
		inline YVec2();
		inline YVec2(float InFloat);
		inline YVec2(float InX, float InY);
		inline YVec2(const YVec2& InVec2);
		inline YVec2(const YVec3& InVec3);
		inline YVec2(const YVec4& InVec4);

		//
		// Operators START
		//
		//Relational
		inline YVec2 operator=(const YVec2& V);
		inline bool operator==(const YVec2& Other) const;
		inline bool operator!=(const YVec2& Other) const;

		inline bool operator<(const YVec2& Other) const;
		inline bool operator<=(const YVec2& Other) const;
		inline bool operator>(const YVec2& Other) const;
		inline bool operator>=(const YVec2& Other) const;

		inline YVec2 operator+(const YVec2& V) const;
		inline YVec2 operator+(float A) const;
		inline YVec2 operator+=(float A);
		inline YVec2 operator+=(const YVec2& a);

		inline YVec2 operator-() const;
		inline YVec2 operator-(float A) const;
		inline YVec2 operator-(const YVec2& V) const;
		inline YVec2 operator-=(float A);
		inline YVec2 operator-=(const YVec2& V);


		inline YVec2 operator*(float Scale) const;
		friend inline YVec2 operator*(YVec2& V, float Scale);
		friend inline YVec2 operator*(float Scale, YVec2& V);
		inline YVec2 operator*(const YVec2& V) const;
		inline YVec2 operator*=(float a);
		inline YVec2 operator*=(const YVec2& V);

		inline YVec2 operator/(float Scale) const;
		inline YVec2 operator/(const YVec2& V) const;
		inline YVec2 operator/=(float Scale);
		inline YVec2 operator/=(const YVec2& V);

		inline float& operator[](unsigned int i) { return (&x)[i]; }
		inline float operator[](unsigned int i) const { return (&x)[i]; }
		
		inline float operator|(const YVec2& V) const;
		inline float operator^(const YVec2& V) const;
		//Operators END

		//
		// Functions START
		//
		inline bool IsNearlyZero(float Tolerance) const;
		inline bool IsZero() const;
		inline bool Equals(const YVec2& V, float Tolerance) const;
		inline YVec2 ClampAxes(float MinAxisVal, float MaxAxisVal) const;
		inline bool ContainsNaN() const;
		inline YVec2 RoundToVector() const;
		inline float Magnitude() const;
		inline float MagnitudeSquared() const;

		inline YVec2 GetRotated(float AngleDeg) const;
		inline YVec2 GetSignVector() const;
		inline YVec2 GetSafeNormal(float Tolerance) const;
		inline YVec2 GetAbs() const;
		inline float GetAbsMax() const;
		inline float GetMax() const;
		inline float GetMin() const;

		inline void Set(float InX, float InY);
		inline void Normalize(float Tolerance);

		//Makes a vector2s 0
		inline void makeZero();
		//normalizes a vector2d
		inline void normalize();

		//Functions END

		//DOT PRODUCT between two vector2ds
		inline float dot(const YVec2& a) const;


		//Statics
		static YVec2 Max(const YVec2& A, const YVec2& B);
		static YVec2 Min(const YVec2& A, const YVec2& B);
		static float DotProduct(const YVec2& A, const YVec2& B);
		static float CrossProduct(const YVec2& A, const YVec2& B);
		static float Distance(const YVec2& V1, const YVec2& V2);
		static float DistanceSquared(const YVec2& V1, const YVec2& V2);

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

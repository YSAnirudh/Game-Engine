#pragma once
#include <iostream>
namespace MathLib {
	class YVec2 {
	public:
		float x, y;

		//
		// Constructor Overloads
		//
		inline YVec2();
		inline YVec2(float x, float y);
		inline YVec2(const YVec2& vec2);

		//
		// Operators START
		//
		//Relational
		inline YVec2 operator=(const YVec2& a);
		inline bool operator==(const YVec2& a) const;

		//Arithmetic
		// Negate a vector2d
		inline YVec2 operator-() const;
		//Multiply a vector2d with a scalar
		inline YVec2 operator*(const float& mult) const;
		//Scalar Multiplication 5 * vector2d
		friend inline YVec2 operator*(YVec2& a, const float& mult);
		friend inline YVec2 operator*(const float& mult, YVec2& a);
		//Divide a vector2d with a scalar
		inline YVec2 operator/(const float& div) const;
		//Adding two YVec2s
		inline YVec2 operator+(const YVec2& a) const;
		//Subtracting two vector2ds
		inline YVec2 operator-(const YVec2& a) const;

		//Operators for easy use and flexibility
		inline YVec2& operator+=(const YVec2& a);
		inline YVec2& operator-=(const YVec2& a);
		inline YVec2& operator*=(const float& a);
		inline YVec2& operator/=(const float& a);

		inline float& operator[](unsigned int i) { return (&x)[i]; }
		inline float operator[](unsigned int i) const { return (&x)[i]; }
		//Operators END

		//
		// Functions START
		//
		//Makes a vector2s 0
		inline void makeZero();
		//normalizes a vector2d
		inline void normalize();

		//Functions END

		//DOT PRODUCT between two vector2ds
		inline float operator*(const YVec2& a) const;
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

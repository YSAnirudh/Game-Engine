#pragma once
#include <iostream>
#include "Vector3D.h"

namespace MathLib {
	class YVec4 {
	public:
		float x, y, z, w;
		//
		//Constructor Overloads
		//
		inline YVec4()
			:x(0), y(0), z(0), w(0)
		{}
		inline YVec4(const YVec4& a)
			: x(a.x), y(a.y), z(a.z), w(a.w)
		{}
		inline YVec4(const YVec3& a)
			: x(a.x), y(a.y), z(a.z), w(0)
		{}
		/*inline YVec4(const YVec2& a)
			: x(a.x), y(a.y), z(0), w(0)
		{}*/
		inline YVec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{}

		//
		// Operators START
		//
		//Relational

		//Assignment operator to a vector.
		inline YVec4 operator =(const YVec4& a);
		//Equality operator to check for Equality of 2 YVec4s
		inline bool operator ==(const YVec4& a) const;

		//Arithmetic

		//Negation operator to negate a vector4d
		inline YVec4 operator-() const;
		//Multiplication of a vector4d with a scalar
		inline YVec4 operator*(const float& mult) const;
		//Scalar Multiplication 5 * vector4d
		inline friend YVec4 operator*(YVec4& a, const float& mult);
		inline friend YVec4 operator*(const float& mult, YVec4& a);
		//Division of a vector4d with a scalar
		inline YVec4 operator/(const float& div) const;
		//Addition of two vector4ds
		inline YVec4 operator+(const YVec4& a) const;
		//Subtraction of two vector4ds
		inline YVec4 operator-(const YVec4& a) const;
		//Extra Operators for flexibility
		inline YVec4& operator +=(const YVec4& a);
		inline YVec4& operator -=(const YVec4& a);
		inline YVec4& operator *=(const float& a);
		inline YVec4& operator /=(const float& a);
		inline float& operator[](unsigned int i) { return (&x)[i]; }
		inline float operator[](unsigned int i) const { return (&x)[i]; }
		//Operators END

		//
		//Functions START
		//
		//Makes a vector3d 0
		void makeZero();
		// normalizes a vector3d
		void normalize();
		//Functions END

		//DOT PRODUCT between two vector3ds
		float operator *(const YVec4& a) const;
		inline float dot(const YVec4& a) const;
	};
	//
	//Non Member Functions START
	//
	//DOT PRODUCT between two vector3ds
	extern inline float dotProduct(const YVec4& a, const YVec4& b);
	//Magnitude of a vector3d specified
	extern float magnitude(const YVec4& a);
	//Distance between two vector3ds
	extern float distance(const YVec4& a, const YVec4& b);
	//non member functions END
}
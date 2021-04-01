#pragma once
#include <iostream>
#include "Vector2D.h"

namespace MathLib {
	//class YVec2;
	class YVec3 {
	public:
		float x, y, z;

		//
		//Constructor Overloads
		//

		inline YVec3();
		inline YVec3(const YVec3& a);
		inline YVec3(float x, float y, float z);
		inline YVec3(const YVec2& a);

		//
		//Operators START
		//

		//Relational

		////Assignment operator to a vector.
		//inline YVec3 operator =(const YVec3& a);
		//Equality operator to check for Equality of 2 Vectors
		inline bool operator ==(const YVec3& a) const;

		//Arithmetic

		//Negation operator to negate a vector3d
		inline YVec3 operator-() const;
		//Multiplication of a vector3d with a scalar
		inline YVec3 operator*(const float& mult) const;
		//Scalar Multiplication 5 * vector3d

		//inline friend YVec3 operator*(const YVec3& a, const float& mult);
		inline friend YVec3 operator*(const float& mult,const YVec3& a);
		//Division of a vector3d with a scalar
		inline YVec3 operator/(const float& div) const;
		//Addition of two vector3ds
		inline YVec3 operator+(const YVec3& a) const;
		//Subtraction of two vector3ds
		inline YVec3 operator-(const YVec3& a) const;
		//Extra Operators for flexibility
		inline YVec3& operator +=(const YVec3& a);
		inline YVec3& operator -=(const YVec3& a);
		inline YVec3& operator *=(const float& a);
		inline YVec3& operator /=(const float& a);

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
		float operator *(const YVec3& a) const;
		inline float dot(const YVec3& a) const;

		inline void set(float X, float Y, float Z) {
			X = x;
			Y = y;
			Z = z;
		}
	};
	//
	// Non Member Functions
	//

	//DOT PRODUCT between two vector3ds
	extern inline float dotProduct(const YVec3& a, const YVec3& b);
	//CROSS PRODUCT between two vector3ds
	extern inline YVec3 crossProduct(const YVec3& a, const YVec3& b);
	//Magnitude of a vector3d specified
	extern inline float magnitude(const YVec3& a);
	//Distance between two vector3ds
	extern inline float distance(const YVec3& a, const YVec3& b);
	// Non Member Functions END
}
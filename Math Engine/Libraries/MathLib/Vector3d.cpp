#pragma once
#include "Vector3D.h"
namespace MathLib {
	//
	// Constructors
	//
	YVec3::YVec3() : x(0), y(0), z(0) {}
	YVec3::YVec3(const YVec3& a) : x(a.x), y(a.y), z(a.z) {}
	YVec3::YVec3(float x, float y, float z) : x(x), y(y), z(z) {}
	YVec3::YVec3(const YVec2& a) : x(a.x), y(a.y), z(0) {}

	//
	// Relational Operators
	//
	//Assignment
	/*inline YVec3 YVec3::operator =(const YVec3& a) {
		this->x = a.x;
		this->y = a.y;
		this->z = a.z;
		return *this;
	}*/
	//Equality
	inline bool YVec3::operator ==(const YVec3& a) const {
		if (a.x == this->x && a.y == this->y && a.z == this->z) {
			return true;
		}
		return false;
	}
	//
	// Basic Operators
	//
	//Negation
	inline YVec3 YVec3::operator-() const {
		return YVec3(-this->x, -this->y, -this->z);
	}
	//Scalar multiplication
	inline YVec3 YVec3::operator*(const float& mult) const {
		return YVec3(this->x * mult, this->y * mult, this->z * mult);
	}
	/*inline YVec3 operator*(const YVec3& a, const float& mult) {
		return YVec3(a.x * mult, a.y * mult, a.z * mult);
	}*/
	inline YVec3 operator*(const float& mult, const YVec3& a) {
		return a * mult;
	}
	//Scalar Division
	inline YVec3 YVec3::operator/(const float& div) const {
		return YVec3(this->x / div, this->y / div, this->z / div);
	}
	//Addition
	inline YVec3 YVec3::operator+(const YVec3& a) const {
		return YVec3(this->x + a.x, this->y + a.y, this->z + a.z);
	}
	//Subtraction
	inline YVec3 YVec3::operator-(const YVec3& a) const {
		return YVec3(this->x - a.x, this->y - a.y, this->z - a.z);
	}

	//Extra Operators
	inline YVec3& YVec3::operator +=(const YVec3& a) {
		this->x += a.x; this->y += a.y; this->z += a.z;
		return *this;
	}
	inline YVec3& YVec3::operator -=(const YVec3& a) {
		this->x = this->x - a.x;
		this->y = this->y - a.y;
		this->z = this->z - a.z;
		return *this;
	}
	inline YVec3& YVec3::operator *=(const float& a) {
		this->x *= a; this->y *= a; this->z *= a;
		return *this;
	}
	inline YVec3& YVec3::operator /=(const float& a) {
		float byA = 1.0f / a;
		this->x *= byA; this->y *= byA; this->z *= byA;
		return *this;
	}


	//
	// Member Functions
	//
	//Make Vector Zero
	inline void YVec3::makeZero() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	//Normalize
	inline void YVec3::normalize() {
		float mag = magnitude(*this);
		if (mag > 0) {
			this->x /= mag;
			this->y /= mag;
			this->z /= mag;
		}
	}

	//DOT PRODUCT
	inline float YVec3::operator*(const YVec3& a) const {
		return this->x * a.x + this->y * a.y + this->z * a.z;
	}
	inline float YVec3::dot(const YVec3& a) const {
		return this->x * a.x + this->y * a.y + this->z * a.z;
	}

	//
	// Non Member Functions
	//
	//DOT PRODUCT
	inline float dotProduct(const YVec3& a, const YVec3& b) {
		return b.x * a.x + b.y * a.y + b.z * a.z;
	}
	//CROSS PRODUCT
	inline YVec3 crossProduct(const YVec3& a, const YVec3& b) {
		return YVec3(
			a.y * b.z - b.y * a.z,
			-(a.x * b.z - b.x * a.z),
			a.x * b.y - b.x * a.y
		);
	}
	//Magnitude
	inline float magnitude(const YVec3& a) {
		float magSq = a.x * a.x + a.y * a.y + a.z * a.z;
		return sqrt(magSq);
	}
	//Distance
	inline float distance(const YVec3& a, const YVec3& b) {
		float X, Y, Z;
		X = a.x - b.x;
		Y = a.y - b.y;
		Z = a.z - b.z;
		return sqrt(X * X + Y * Y + Z * Z);
	}
}
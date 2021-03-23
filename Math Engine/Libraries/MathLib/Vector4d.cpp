#include "Vector4D.h"

namespace MathLib {
	//
	// Constructors
	//
	

	//
	// Relational Operators
	//
	//Assignment
	inline YVec4 YVec4::operator =(const YVec4& a) {
		this->x = a.x;
		this->y = a.y;
		this->z = a.z;
		return *this;
	}
	//Equality
	inline bool YVec4::operator ==(const YVec4& a) const {
		if (a.x == this->x && a.y == this->y && a.z == this->z) {
			return true;
		}
		return false;
	}
	//
	// Basic Operators
	//
	//Negation
	inline YVec4 YVec4::operator-() const {
		return YVec4(-this->x, -this->y, -this->z, -this->w);
	}
	//Scalar multiplication
	inline YVec4 YVec4::operator*(const float& mult) const {
		return YVec4(this->x * mult, this->y * mult, this->z * mult, this->w * mult);
	}
	inline YVec4 operator*(YVec4& a, const float& mult) {
		return YVec4(a.x * mult, a.y * mult, a.z * mult, a.w * mult);
	}
	inline YVec4 operator*(const float& mult, YVec4& a) {
		return a * mult;
	}
	//Scalar Division
	inline YVec4 YVec4::operator/(const float& div) const {
		return YVec4(this->x / div, this->y / div, this->z / div, this->w / div);
	}
	//Addition
	inline YVec4 YVec4::operator+(const YVec4& a) const {
		return YVec4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
	}
	//Subtraction
	inline YVec4 YVec4::operator-(const YVec4& a) const {
		return YVec4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
	}

	//Extra Operators
	inline YVec4& YVec4::operator +=(const YVec4& a) {
		this->x += a.x; this->y += a.y; this->z += a.z; this->w += a.w;
		return *this;
	}
	inline YVec4& YVec4::operator -=(const YVec4& a) {
		this->x = this->x - a.x;
		this->y = this->y - a.y;
		this->z = this->z - a.z;
		this->w = this->w - a.w;
		return *this;
	}
	inline YVec4& YVec4::operator *=(const float& a) {
		this->x *= a; this->y *= a; this->z *= a; this->w *= a;
		return *this;
	}
	inline YVec4& YVec4::operator /=(const float& a) {
		float byA = 1.0f / a;
		this->x *= byA; this->y *= byA; this->z *= byA; this->w *= byA;
		return *this;
	}

	//
	// Member Functions
	//
	//Make Vector Zero
	inline void YVec4::makeZero() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}
	//Normalize
	void YVec4::normalize() {
		float mag = magnitude(*this);
		if (mag > 0) {
			this->x /= mag;
			this->y /= mag;
			this->z /= mag;
			this->w /= mag;
		}
	}
	//DOT PRODUCT
	inline float YVec4::operator*(const YVec4& a) const {
		return this->x * a.x + this->y * a.y + this->z * a.z + this->w * a.w;
	}
	inline float YVec4::dot(const YVec4& a) const {
		return this->x * a.x + this->y * a.y + this->z * a.z + this->w * a.w;
	}

	//
	// Non Member Functions
	//
	//DOT PRODUCT
	inline float dotProduct(const YVec4& a, const YVec4& b) {
		return a * b;
	}
	//Magnitude
	float magnitude(const YVec4& a) {
		float magSq = a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
		return sqrt(magSq);
	}
	//Distance
	float distance(const YVec4& a, const YVec4& b) {
		float X, Y, Z, W;
		X = a.x - b.x;
		Y = a.y - b.y;
		Z = a.z - b.z;
		W = a.w - b.w;
		return sqrt(X * X + Y * Y + Z * Z + W * W);
	}
}
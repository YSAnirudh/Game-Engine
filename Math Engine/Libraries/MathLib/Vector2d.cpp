#include "Vector2D.h"
namespace MathLib {
	//
	// Constructors
	//
	inline YVec2::YVec2() :x(0), y(0) {}
	inline YVec2::YVec2(float x, float y) : x(x), y(y) {}
	inline YVec2::YVec2(const YVec2& a) : x(a.x), y(a.y) {}

	//
	// Basic Operators
	//
	//Assignment
	inline YVec2 YVec2::operator =(const YVec2& a) {
		this->x = a.x;
		this->y = a.y;
		return *this;
	}
	//Equality
	inline bool YVec2::operator ==(const YVec2& a) const {
		if (a.x == this->x && a.y == this->y) {
			return true;
		}
		return false;
	}
	//Negation
	inline YVec2 YVec2::operator-() const {
		return YVec2(-this->x, -this->y);
	}
	//Scalar multiplication
	inline YVec2 YVec2::operator*(const float& mult) const {
		return YVec2(this->x * mult, this->y * mult);
	}
	inline YVec2 operator*(YVec2& a, const float& mult) {
		return YVec2(a.x * mult, a.y * mult);
	}
	inline YVec2 operator*(const float& mult, YVec2& a) {
		return a * mult;
	}
	//Scalar Division
	inline YVec2 YVec2::operator/(const float& div) const {
		return YVec2(this->x / div, this->y / div);
	}
	//Addition
	inline YVec2 YVec2::operator+(const YVec2& a) const {
		return YVec2(this->x + a.x, this->y + a.y);
	}
	//Subtraction
	inline YVec2 YVec2::operator-(const YVec2& a) const {
		return YVec2(this->x - a.x, this->y - a.y);
	}

	//Extra Operators
	inline YVec2& YVec2::operator +=(const YVec2& a) {
		this->x += a.x; this->y += a.y;
		return *this;
	}
	inline YVec2& YVec2::operator -=(const YVec2& a) {
		this->x = this->x - a.x;
		this->y = this->y - a.y;
		return *this;
	}
	inline YVec2& YVec2::operator *=(const float& a) {
		this->x *= a; this->y *= a;
		return *this;
	}
	inline YVec2& YVec2::operator /=(const float& a) {
		float byA = 1.0f / a;
		this->x *= byA; this->y *= byA;
		return *this;
	}
	//
	// Member Functions
	//
	//Make Vector Zero
	inline void YVec2::makeZero() {
		this->x = 0;
		this->y = 0;
	}
	//Normalize
	inline void YVec2::normalize() {
		float mag = magnitude(*this);
		if (mag > 0) {
			this->x /= mag;
			this->y /= mag;
		}
	}

	//DOT PRODUCT
	inline float YVec2::operator*(const YVec2& a) const {
		return this->x * a.x + this->y * a.y;
	}
	inline float YVec2::dot(const YVec2& a) const {
		return this->x * a.x + this->y * a.y;
	}
	//
	// Non Member Functions
	//
	//Magnitude
	inline float magnitude(const YVec2& a) {
		float magSq = a.x * a.x + a.y * a.y;
		return sqrt(magSq);
	}
	//Distance
	inline float distance(const YVec2& a, const YVec2& b) {
		float X, Y;
		X = a.x - b.x;
		Y = a.y - b.y;
		return sqrt(X * X + Y * Y);
	}
	//Dot Product
	inline float dotProduct(const YVec2& a, const YVec2& b) {
		return a.x * b.x + a.y + b.y;
	}
}
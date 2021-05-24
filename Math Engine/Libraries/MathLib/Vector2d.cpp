// HEADER INCLUDES
#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include <iostream>
namespace MathLib {
	//
	// STATIC VARIABLE DECLARATIONS
	//
	const YVec2 YVec2::UnitVec2 = YVec2(1.0f, 1.0f);
	const YVec2 YVec2::ZeroVec2 = YVec2(0.0f, 0.0f);
	const YVec2 YVec2::Deg45Vec2 = YVec2(YMath::Sqrt(0.5f), YMath::Sqrt(0.5f));

	//
	// CONSTRUCTORS START
	//
	YVec2::YVec2() :x(0), y(0) {}
	YVec2::YVec2(float InFloat): x(InFloat), y(InFloat){}
	YVec2::YVec2(float InX, float InY) : x(InX), y(InY) {}
	YVec2::YVec2(const YVec2& InVec2) : x(InVec2.x), y(InVec2.y) {}
	YVec2::YVec2(const YVec3& InVec3) : x(InVec3.x), y(InVec3.y) {}
	YVec2::YVec2(const YVec4& InVec4) : x(InVec4.x), y(InVec4.y) {}
	//
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//

	// Assignment -> Assigns the values x and y of V to this
	void YVec2::operator =(const YVec2& V) {
		this->x = V.x;
		this->y = V.y;
	}

	//Equality -> Returns true if this and Other are equal
	bool YVec2::operator ==(const YVec2& Other) const {
		if (YMath::IsZero(Other.x - this->x) && YMath::IsZero(Other.y - this->y)) {
			return true;
		}
		return false;
	}

	// Inequality -> Returns true if this and Other are not equal
	bool YVec2::operator!=(const YVec2& Other) const {
		if (YMath::IsZero(Other.x - this->x) && YMath::IsZero(Other.y - this->y)) {
			return false;
		}
		return true;
	}

	// Less Than -> Returns true if Magnitude of this is less than Magnitude of Other
	bool YVec2::operator<(const YVec2& Other) const {
		if (this->MagnitudeSquared() < Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// Less than or Equal to -> Returns true if Magnitude of this is
	// less than or equal to Magnitude of Other
	bool YVec2::operator<=(const YVec2& Other) const {
		if (this->MagnitudeSquared() <= Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// Greater than - Returns true if Magnitude of this is greater than Magnitude of Other
	bool YVec2::operator>(const YVec2& Other) const {
		if (this->MagnitudeSquared() > Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// Greater than or Equal to -> Returns true if Magnitude of this 
	// greater than or equal to Magnituce of Other
	bool YVec2::operator>=(const YVec2& Other) const	{
		if (this->MagnitudeSquared() >= Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// this + YVec2 -> Adds the values V.x and V.y to this.x and this.y respectively
	YVec2 YVec2::operator+(const YVec2& V) const {
		return YVec2(this->x + V.x, this->y + V.y);
	}
	// this + float -> Adds the value A to both this.x and this.y
	YVec2 YVec2::operator+(float A) const {
		return YVec2(this->x + A, this->y + A);
	}
	// this += YVec2 -> Adds the values V.x and V.y to this.x and this.y respectively and stores in this
	YVec2 YVec2::operator+=(const YVec2& V) {
		return (*this) + V;
	}
	// this += float -> Adds the value A to both this.x and this.y and stores in this
	YVec2 YVec2::operator+=(float A) {
		return (*this) + A;
	}

	// Negation -> Makes the values x and y of this opposite sign (+ -> - , - -> +)
	YVec2 YVec2::operator-() const {
		return YVec2(-this->x, -this->y);
	}
	// this - YVec2 -> Subtracts V.x and V.y from this.x and this.y respectively 
	YVec2 YVec2::operator-(const YVec2& V) const {
		return YVec2(this->x - V.x, this->y - V.y);
	}
	// this - float -> Subtracts A from values of this.x and this.y
	YVec2 YVec2::operator-(float A) const {
		return YVec2(this->x - A, this->y - A);
	}
	// this -= YVec2 -> Subtracts V.x and V.y from this.x and this.y respectively and stores in this
	YVec2 YVec2::operator-=(const YVec2& V) {
		return (*this) - V;
	}
	// this -= float -> Subtracts A from values of this.x and this.y and stores in this
	YVec2 YVec2::operator-=(float A) {
		return (*this) - A;
	}

	// this * YVec2 -> Multiplies this.x and this.y with V.x and V.y respectively
	YVec2 YVec2::operator*(const YVec2& V) const {
		return YVec2(this->x * V.x, this->y * V.y);
	}
	// Scalar Multiplication -> Multiplies this.x and this.y with Scale
	YVec2 YVec2::operator*(float Scale) const {
		return YVec2(this->x * Scale, this->y * Scale);
	}
	YVec2 operator*(YVec2& V,float Scale) {
		return YVec2(V.x * Scale, V.y * Scale);
	}
	YVec2 operator*(float Scale, YVec2& V) {
		return V * Scale;
	}
	// this *= YVec2 -> Multiplies this.x and this.y with V.x and V.y respectively and stores in this
	YVec2 YVec2::operator*=(const YVec2& V) {
		return (*this) * V;
	}
	// this *= Scale -> Multiplies this.x and this.y with Scale and stores in this
	YVec2 YVec2::operator *=(float Scale){
		return (*this) * Scale;
	}

	// this / YVec2 -> Divides this.x and this.y with V.x and V.y respectively
	YVec2 YVec2::operator/(const YVec2& V) const {
		return YVec2(this->x / V.x, this->y / V.y);
	}
	// Scalar Division -> Divides this.x and this.y with Scale
	YVec2 YVec2::operator/(float Scale) const {
		return YVec2(this->x / Scale, this->y / Scale);
	}
	// this /= YVec2 -> Divides this.x and this.y with V.x and V.y respectively and stores in this
	YVec2 YVec2::operator/=(const YVec2& V) {
		return (*this) / V;
	}
	// this /= Scale -> Divides this.x and this.y with Scale and stores in this
	YVec2 YVec2::operator /=(float Scale) {
		return (*this) / Scale;
	}

	// Dot Product -> Calculates the Dot Product between this and V
	float YVec2::operator|(const YVec2& V) const {
		return this->x * V.x + this->y * V.y;
	}
	// Cross Product Product -> Calculates the Cross Product between this and V
	float YVec2::operator^(const YVec2& V) const {
		return this->x * V.y - this->y * V.x;
	}

	// 
	// OPERATORS END
	//

	//
	// FUNCTIONS START
	//

	// Returns true if this is within Tolerance Range of ZeroVec(0.0f, 0.0f)
	bool YVec2::IsNearlyZero(float Tolerance = yEpsilon) const {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return true;
		}
		return false;
	}

	// Returns true if this is equal to ZeroVec(0.0f, 0.0f)
	bool YVec2::IsZero() const {
		if (YMath::IsZero(this->MagnitudeSquared())) {
			return true;
		}
		return false;
	}

	// Returns true if this.x and this.y are with the Tolerance range of V.x and V.y respectively
	bool YVec2::Equals(const YVec2& V, float Tolerance = yEpsilon) const {
		if (YMath::IsNearlyZero(this->x - V.x, Tolerance) && YMath::IsNearlyZero(this->y - V.y, Tolerance)) {
			return true;
		}
		return false;
	}

	// Returns YVec2 with this.x and this.y clamped between MinAxisValue and MaxAxisValue
	YVec2 YVec2::ClampAxes(float MinAxisVal, float MaxAxisVal) const {
		return YVec2(
			YMath::Clamp(this->x, MinAxisVal, MaxAxisVal),
			YMath::Clamp(this->y, MinAxisVal, MaxAxisVal)
			);
	}

	// Returns true if either of this.x or this.y are NaN(Not a Number)
	bool YVec2::ContainsNaN() const {
		if (YMath::IsNaN(this->x) || YMath::IsNaN(this->y)) {
			return true;
		}
		return false;
	}

	// Returns the YVec2 with the rounded values of this.x and this.y
	YVec2 YVec2::RoundToVector() const {
		return YVec2(YMath::Round(this->x), YMath::Round(this->y));
	}

	// Gets the YVec2 when it is rotated AngleDeg degrees "Anti-Clockwise"
	YVec2 YVec2::GetRotated(float AngleDeg) const {
		float AngleRad = YMath::DegToRad(AngleDeg);
		float Mag = this->Magnitude();
		float CurrAngleRad = YMath::ACos(this->x / Mag);

		return YVec2(Mag * YMath::Cos(AngleRad + CurrAngleRad), Mag * YMath::Sin(AngleRad + CurrAngleRad));
	}

	// Gets the signs of this.x and this.y as a YVec2(sign(x), sign(y))
	YVec2 YVec2::GetSignVector() const {
		return YVec2(this->x >= 0 ? 1.0f : -1.0f, this->y >= 0 ? 1.0f : -1.0f);
	}

	// Gets the Normalized this vector 2d if Magnitude(YVec2 this) != 0.0f
	// Gets YVec2(0.0f, 0.0f) otherwise with a Tolerance
	YVec2 YVec2::GetSafeNormal(float Tolerance = yEpsilon) const {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return YVec2(0.0f, 0.0f);
		}
		return YVec2(this->x / this->Magnitude(),this->y / this->Magnitude());
	}

	// Gets the YVec2 of this with absolute values of x and y
	YVec2 YVec2::GetAbs() const {
		return YVec2(YMath::Abs(this->x), YMath::Abs(this->y));
	}

	// Gets the maximum values of absolute values of this.x and this.y
	float YVec2::GetAbsMax() const {
		return YMath::Max(YMath::Abs(this->x), YMath::Abs(this->y));
	}

	// Gets the maximum of this.x and this.y
	float YVec2::GetMax() const {
		return YMath::Max(this->x, this->y);
	}

	// Gets the maximum of this.x and this.y
	float YVec2::GetMin() const {
		return YMath::Min(this->x, this->y);
	}

	// Sets the values of this.x and this.y to InX and InY respectively
	void YVec2::Set(float InX, float InY) {
		this->x = InX;
		this->y = InY;
	}

	// Sets this to the Normalized version of this vector for Magnitude outside Tolerance range of 0.0f
	// Sets this to YVec2(0.0f, 0.0f) for Magnitude within Tolerance range of 0.0f
	void YVec2::Normalize(float Tolerance = yEpsilon) {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			this->x = 0;
			this->y = 0;
		}
		this->x /= this->Magnitude();
		this->y /= this->Magnitude();
	}

	// Returns the Magnitude of this vector
	float YVec2::Magnitude() const {
		return YMath::Sqrt(this->x * this->x + this->y * this->y);
	}

	// Returns the Square of the Magnitude of this vector
	float YVec2::MagnitudeSquared() const {
		return this->x * this->x + this->y * this->y;
	}

	//Assigns unit vector of this vector to OutDir and length of this vector to OutLength
	void YVec2::ToDirectionAndLength(YVec2& OutDir, float& OutLength) const {
		OutDir = this->GetSafeNormal();
		OutLength = this->Magnitude();
	}

	YVec3 YVec2::SprericalToCartesian() const {
		return YVec3(
			YMath::Sin(this->y) * YMath::Cos(this->x),
			YMath::Sin(this->y) * YMath::Sin(this->x),
			YMath::Cos(this->y)
		);
	}

	// STATIC FUNCTIONS
	
	// Returns YVec2 with the maximum values of x and y of A and B
	YVec2 YVec2::Max(const YVec2& A, const YVec2& B) {
		return YVec2(YMath::Max(A.x, B.x), YMath::Max(A.y, B.y));
	}

	// Returns YVec2 with the minimum values of x and y of A and B
	YVec2 YVec2::Min(const YVec2& A, const YVec2& B) {
		return YVec2(YMath::Min(A.x, B.x), YMath::Min(A.y, B.y));
	}

	// Returns the computed Dot Product between A and B
	float YVec2::DotProduct(const YVec2& A, const YVec2& B) {
		return A.x * B.x + A.y * B.y;
	}
	
	// Returns the computed Cross Product between A and B
	float YVec2::CrossProduct(const YVec2& A, const YVec2& B) {
		return A.x * B.y - A.y * B.x;
	}

	// Returns the distance between V1 and V2
	float YVec2::Distance(const YVec2& V1, const YVec2& V2) {
		return YMath::Sqrt(((V1.x - V2.x) * (V1.x - V2.x)) + ((V1.y - V2.y)*(V1.y - V2.y)));
	}

	// Returns the square of distance between V1 and V2
	float YVec2::DistanceSquared(const YVec2& V1, const YVec2& V2) {
		return ((V1.x - V2.x) * (V1.x - V2.x)) + ((V1.y - V2.y) * (V1.y - V2.y));
	}

	// Returns the magnitude of V
	float YVec2::Magnitude(const YVec2& V) {
		return YMath::Sqrt(V.x * V.x + V.y * V.y);
	}
	
	//
	// FUNCTIONS END
	//
	
	



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
	inline float YVec2::dot(const YVec2& a) const {
		return this->x * a.x + this->y * a.y;
	}

	
	//
	// Non Member Functions
	//
	//Magnitude
	inline float magnitude(const YVec2& a) {
		float magSq = a.x * a.x + a.y * a.y;
		return YMath::Sqrt(magSq);
	}
	//Distance
	inline float distance(const YVec2& a, const YVec2& b) {
		float X, Y;
		X = a.x - b.x;
		Y = a.y - b.y;
		return YMath::Sqrt(X * X + Y * Y);
	}
	//Dot Product
	inline float dotProduct(const YVec2& a, const YVec2& b) {
		return a.x * b.x + a.y + b.y;
	}
}
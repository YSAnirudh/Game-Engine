// HEADER INCLUDES

#include <iostream>
#include "Vector4D.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Quaternion.h"
#include "EulerAngles.h"
namespace MathLib {
	//
	// CONSTRUCTORS START
	//
	inline YVec4::YVec4() : x(0), y(0), z(0), w(0) {}
	inline YVec4::YVec4(float InF) : x(InF), y(InF), z(InF), w(InF) {}
	inline YVec4::YVec4(const YVec4& V) : x(V.x), y(V.y), z(V.z), w(V.w) {}
	inline YVec4::YVec4(const YVec3& a, float InW) : x(a.x), y(a.y), z(a.z), w(InW) {}
	inline YVec4::YVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	inline YVec4::YVec4(const YVec2& InXY, const YVec2& InZW) : x(InXY.x), y(InXY.y), z(InZW.x), w(InZW.y){}
	//
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//
	//Assignment -> Assigns the values x, y, z of V to this
	/*inline YVec4 YVec4::operator =(const YVec4& a) {
		this->x = a.x;
		this->y = a.y;
		this->z = a.z;
		this->w = a.w
		return *this;
	}*/

	//Equality -> Returns true if this and Other are equal
	inline bool YVec4::operator ==(const YVec4& Other) const {
		if (YMath::IsZero(Other.x - this->x) && YMath::IsZero(Other.y - this->y) && YMath::IsZero(Other.z - this->z) && YMath::IsZero(Other.w - this->w)) {
			return true;
		}
		return false;
	}

	// Inequality -> Returns true if this and Other are not equal
	inline bool YVec4::operator!=(const YVec4& Other) const {
		if (!YMath::IsZero(Other.x - this->x) && !YMath::IsZero(Other.y - this->y) && !YMath::IsZero(Other.z - this->z) && !YMath::IsZero(Other.w - this->w)) {
			return true;
		}
		return false;
	}

	// Less Than -> Returns true if this.x, this.y, this.z, this.w are less than Other.x, Other.y, Other.z, Other.w
	inline bool YVec4::operator<(const YVec4& Other) const {
		if (this->x < Other.x && this->y < Other.y && this->z < Other.z && this->w < Other.w) {
			return true;
		}
		return false;
	}

	// Less Than or Equal to -> Returns true if this.x, this.y, this.z, this.w are 
	// less than or equal to Other.x, Other.y, Other.z, Other.w
	inline bool YVec4::operator<=(const YVec4& Other) const {
		if (this->x <= Other.x && this->y <= Other.y && this->z <= Other.z && this->w <= Other.w) {
			return true;
		}
		return false;
	}

	// Greater Than -> Returns true if this.x, this.y, this.z, this.w are greater than Other.x, Other.y, Other.z, Other.w
	inline bool YVec4::operator>(const YVec4& Other) const {
		if (this->x > Other.x && this->y > Other.y && this->z > Other.z && this->w > Other.w) {
			return true;
		}
		return false;
	}

	// Greater Than or Equal to -> Returns true if this.x, this.y, this.z, this.w are 
	// greater than or equal to Other.x, Other.y, Other.z, Other.w
	inline bool YVec4::operator>=(const YVec4& Other) const {
		if (this->x >= Other.x && this->y >= Other.y && this->z >= Other.z && this->w >= Other.w) {
			return true;
		}
		return false;
	}

	// this + YVec4 -> Adds the values V.x, V.y, V.z, V.w to this.x, this.y, this.z, this.w
	inline YVec4 YVec4::operator+(const YVec4& V) const {
		return YVec4(this->x + V.x, this->y + V.y, this->z + V.z, this->w + V.w);
	}

	// this + float -> Adds the value A to this.x, this.y, this.z, this.w
	inline YVec4 YVec4::operator+(float A) const {
		return YVec4(this->x + A, this->y + A, this->z + A, this->w + A);
	}

	// this += YVec4 -> Adds the values V.x, V.y, V.z, V.w to this.x, this.y, this.z, this.w
	inline YVec4 YVec4::operator+=(const YVec4& V) {
		return (*this) + V;
	}

	// this += float -> Adds the value A to this.x, this.y, this.z, this.w and stores in this
	inline YVec4 YVec4::operator+=(float A) {
		return (*this) + A;
	}

	// Negation -> Makes the values x, y, z, w of this opposite sign (+ -> - , - -> +)
	inline YVec4 YVec4::operator-() const {
		return YVec4(-this->x, -this->y, -this->z, -this->w);
	}

	// this - YVec4 -> Subtracts the values V.x, V.y, V.z, V.w from this.x, this.y, this.z, this.w
	inline YVec4 YVec4::operator-(const YVec4& V) const {
		return YVec4(this->x - V.x, this->y - V.y, this->z - V.z, this->w - V.w);
	}

	// this - float -> Subtracts the value A from this.x, this.y, this.z, this.w
	inline YVec4 YVec4::operator-(float A) const {
		return YVec4(this->x - A, this->y - A, this->z - A, this->w - A);
	}

	// this -= YVec4 -> Subtracts the values V.x, V.y, V.z, V.w from this.x, this.y, this.z, this.w and stores in this
	inline YVec4 YVec4::operator-=(const YVec4& V) {
		return (*this) - V;
	}

	// this -= float -> Subtracts the value A from this.x, this.y, this.z, this.w and stores in this
	inline YVec4 YVec4::operator-=(float A) {
		return (*this) - A;
	}

	// this * YVec4 -> Multiplies the values this.x, this.y, this.z, this.w to V.x, V.y, V.z, V.w
	inline YVec4 YVec4::operator*(const YVec4& V) const {
		return YVec4(this->x * V.x, this->y * V.y, this->z * V.z, this->w * V.w);
	}

	// Scalar Multiplication -> Multiplies this.x, this.y, this.z, this.w with A
	inline YVec4 YVec4::operator*(float A) const {
		return YVec4(this->x * A, this->y * A, this->z * A, this->w * A);
	}
	inline YVec4 operator*(float A, const YVec4& V) {
		return V * A;
	}

	// this *= YVec4 -> Multiplies the values this.x, this.y, this.z, this.w to V.x, V.y, V.z, V.w and stores in this
	inline YVec4 YVec4::operator*=(const YVec4& V) {
		return (*this) * V;
	}

	// this *= A -> Multiplies the value this.x, this.y, this.z, this.w with A and stores in this
	inline YVec4 YVec4::operator*=(float A) {
		return (*this) * A;
	}

	// this / YVec4 -> Divides the values this.x, this.y, this.z, this.w by V.x, V.y, V.z, V.w
	inline YVec4 YVec4::operator/(const YVec4& V) const {
		return YVec4(this->x / V.x, this->y / V.y, this->z / V.z, this->w / V.w);
	}

	// Scalar Division -> Divides this.x, this.y, this.z, this.w by A
	inline YVec4 YVec4::operator/(float A) const {
		return YVec4(this->x / A, this->y / A, this->z / A, this->w / A);
	}

	// this /= YVec4 -> Divides the values this.x, this.y, this.z, this.w by V.x, V.y, V.z, V.w and stores in this
	inline YVec4 YVec4::operator/=(const YVec4& V) {
		return (*this) / V;
	}

	// this /= A -> Divides the value this.x, this.y, this.z, this.w by A and stores in this
	inline YVec4 YVec4::operator/=(float A) {
		return (*this) / A;
	}

	// Dot Product -> Calculates the Dot Product between this and V
	inline float YVec4::operator|(const YVec4& V) const {
		return this->x * V.x + this->y * V.y + this->z * V.z, this->w * V.w;
	}

	// Cross Product Product -> Calculates the Cross Product between this (x,y,z) and V (x,y,z)
	inline YVec4 YVec4::operator^(const YVec4& V) const {
		return YVec4(
			this->y * V.z - V.y * this->z,
			-(this->x * V.z - V.x * this->z),
			this->x * V.y - V.x * this->y,
			0.0f
		);
	}

	// 
	// OPERATORS END
	//

	//
	// FUNCTIONS START
	//

	// Returns true if any of x,y,z,w are NaN
	inline bool YVec4::ContainsNaN() const {
		if (YMath::IsNaN(this->x) || YMath::IsNaN(this->y) || YMath::IsNaN(this->z) || YMath::IsNaN(this->w)) {
			return true;
		}
		return false;
	}

	// Returns true if this is equal to V within a specified Tolerance
	inline bool YVec4::Equals(const YVec4& V, float Tolerance = yEpsilon) const {
		if (YMath::IsNearlyZero(this->x - V.x, Tolerance) && YMath::IsNearlyZero(this->y - V.y, Tolerance) 
			&& YMath::IsNearlyZero(this->z - V.z, Tolerance) && YMath::IsNearlyZero(this->w - V.w, Tolerance)) {
			return true;
		}
		return false;
	}

	// Finds the best axis vectors for the YVec3 in this YVec4 and assigns them to Axis1 and Axis2
	inline void YVec4::FindBestAxisVectors3(YVec3& Axis1, YVec3& Axis2) const {
	}

	// Returns true if x,y,z are nearly zero with the specified Tolerance
	inline bool YVec4::IsNearlyZero3(float Tolerance = yEpsilon) const {
		if (YMath::IsNearlyZero(this->x, Tolerance) && YMath::IsNearlyZero(this->y, Tolerance)
			&& YMath::IsNearlyZero(this->z, Tolerance)) {
			return true;
		}
		return false;
	}

	// Returns true if the YVec3 in this YVec4 has Magnitude 1.0f
	inline bool YVec4::IsUnit3(float LengthSquaredTolerance) const {
		if (YMath::IsNearlyZero(YVec3(*this).MagnitudeSquared()-1.0f, LengthSquaredTolerance)) {
			return true;
		}
		return false;
	}

	// Reflects the YVec3 in this YVec4 about YVec3 of Normal YVec4
	inline YVec4 YVec4::Reflect3(const YVec4& Normal) const {
		YVec3 Reflect = YVec3(*this);
		Reflect.MirrorByVector(YVec3(Normal));
		return YVec4(Reflect, this->z);
	}

	// Gets the Euler Rotation of the YVec4
	inline YEuler YVec4::Rotation() const {
		return YEuler(0.0f, 0.0f, 0.0f);
	}

	// Returns the magnitude of this
	inline float YVec4::Magnitude() const {
		return YMath::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
	}

	// Returns the magnitude of the YVec3 in this YVec4
	inline float YVec4::Magnitude3() const {
		return YMath::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	// Returns the magnitude Squared of this
	inline float YVec4::MagnitudeSquared() const {
		return this->x*this->x + this->y * this->y + this->z * this->z + this->w * this->w;
	}

	// Returns the magnitude Squared of the YVec3 in this YVec4
	inline float YVec4::MagnitudeSquared3() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	// Returns the Orientation Quaternion for this
	inline YQuat YVec4::ToOrientationQuat() const {
		return YQuat();
	}

	// Returns the Orientation Euler for this
	inline YEuler YVec4::ToOrientationEuler() const {
		return YEuler();
	}

	// Gets the Normalized Vector if the magnitude is not 0.0f otherwise returns zero YVec4
	inline YVec4 YVec4::GetSafeNormal(float Tolerance) const {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return YVec4();
		}
		return (*this)/this->Magnitude();
	}

	// Gets the Normalizeed Vector regardless of the magnitude (Not Safe)
	inline YVec4 YVec4::GetUnsafeNormal3() const {
		float Mag = this->Magnitude();
		return YVec4(YVec3(*this) / Mag, this->z);
	}

	// Sets the values of x,y,z,w to InX, InY, InZ, InW
	inline void YVec4::Set(float InX, float InY, float InZ, float InW) {
		this->x = InX;
		this->y = InY;
		this->z = InZ;
		this->w = InW;
	}

	//
	// FUNCTIONS END
	//









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
	
	inline float YVec4::dot(const YVec4& a) const {
		return this->x * a.x + this->y * a.y + this->z * a.z + this->w * a.w;
	}

	//
	// Non Member Functions
	//
	//DOT PRODUCT
	inline float dotProduct(const YVec4& a, const YVec4& b) {
		return 0.0f;
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
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include <iostream>
namespace MathLib {
	static const YVec2 UnitVec2 = YVec2(1.0f, 1.0f);
	static const YVec2 ZeroVec2 = YVec2(0.0f, 0.0f);
	static const YVec2 Deg45Vec2 = YVec2(YMath::Sqrt(0.5f), YMath::Sqrt(0.5f));
	//
	// Constructors
	//
	inline YVec2::YVec2() :x(0), y(0) {}
	inline YVec2::YVec2(float InFloat): x(InFloat), y(InFloat){}
	inline YVec2::YVec2(float InX, float InY) : x(InX), y(InY) {}
	inline YVec2::YVec2(const YVec2& InVec2) : x(InVec2.x), y(InVec2.y) {}
	inline YVec2::YVec2(const YVec3& InVec3) : x(InVec3.x), y(InVec3.y) {}
	inline YVec2::YVec2(const YVec4& InVec4) : x(InVec4.x), y(InVec4.y) {}

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
	inline bool YVec2::operator ==(const YVec2& Other) const {
		if (Other.x == this->x && Other.y == this->y) {
			return true;
		}
		return false;
	}
	inline bool YVec2::operator!=(const YVec2& Other) const {
		if (Other.x != this->x || Other.y != this->y) {
			return true;
		}
		return false;
	}

	inline bool YVec2::operator<(const YVec2& Other) const {
		if (this->x < Other.x && this->y < Other.y) {
			return true;
		}
		return false;
	}

	inline bool YVec2::operator<=(const YVec2& Other) const {
		if (this->x <= Other.x && this->y <= Other.y) {
			return true;
		}
		return false;
	}

	inline bool YVec2::operator>(const YVec2& Other) const {
		if (this->x > Other.x && this->y > Other.y) {
			return true;
		}
		return false;
	}

	inline bool YVec2::operator>=(const YVec2& Other) const	{
		if (this->x >= Other.x && this->y >= Other.y) {
			return true;
		}
		return false;
	}

	inline YVec2 YVec2::operator+(const YVec2& V) const {
		return YVec2(this->x + V.x, this->y + V.y);
	}
	inline YVec2 YVec2::operator+(float A) const
	{
		return YVec2(this->x + A, this->y + A);
	}
	inline YVec2 YVec2::operator+=(float A) {
		return (*this) + A;
	}
	inline YVec2 YVec2::operator+=(const YVec2& V) {
		return (*this) + V;
	}

	//Negation
	inline YVec2 YVec2::operator-() const {
		return YVec2(-this->x, -this->y);
	}
	inline YVec2 YVec2::operator-(float A) const
	{
		return YVec2(this->x - A, this->y - A);
	}
	inline YVec2 YVec2::operator-(const YVec2& V) const {
		return YVec2(this->x - V.x, this->y - V.y);
	}

	inline YVec2 YVec2::operator-=(float A) {
		return (*this) - A;
	}
	inline YVec2 YVec2::operator-=(const YVec2& V) {
		return (*this) - V;
	}



	//Scalar multiplication
	inline YVec2 YVec2::operator*(float Scale) const {
		return YVec2(this->x * Scale, this->y * Scale);
	}
	inline YVec2 operator*(YVec2& V,float Scale) {
		return YVec2(V.x * Scale, V.y * Scale);
	}
	inline YVec2 operator*(float Scale, YVec2& V) {
		return V * Scale;
	}
	inline YVec2 YVec2::operator*(const YVec2& V) const {
		return YVec2(this->x * V.x, this->y * V.y);
	}
	inline YVec2 YVec2::operator *=(float Scale){
		return (*this) * Scale;
	}
	inline YVec2 YVec2::operator*=(const YVec2& V)
	{
		return (*this) * V;
	}





	//Scalar Division
	inline YVec2 YVec2::operator/(float Scale) const {
		return YVec2(this->x / Scale, this->y / Scale);
	}

	inline YVec2 YVec2::operator/(const YVec2& V) const {
		return YVec2(this->x / V.x, this->y / V.y);
	}
	inline YVec2 YVec2::operator /=(float Scale) {
		return (*this) / Scale;
	}
	inline YVec2 YVec2::operator/=(const YVec2& V) {
		return (*this) / V;
	}

	inline float YVec2::operator|(const YVec2& V) const {
		return this->x * V.x + this->y * V.y;
	}

	inline float YVec2::operator^(const YVec2& V) const {
		return this->x * V.y - this->y * V.x;
	}



	inline bool YVec2::IsNearlyZero(float Tolerance = yEpsilon) const
	{
		if (YMath::IsNearlyZero(this->x, Tolerance) && YMath::IsNearlyZero(this->y, Tolerance)) {
			return true;
		}
		return false;
	}

	inline bool YVec2::IsZero() const
	{
		if (YMath::IsZero(this->x) && YMath::IsZero(this->y)) {
			return true;
		}
		return false;
	}

	inline bool YVec2::Equals(const YVec2& V, float Tolerance = yEpsilon) const
	{
		if (YMath::IsNearlyZero(this->x - V.x, Tolerance) && YMath::IsNearlyZero(this->y - V.y, Tolerance)) {
			return true;
		}
		return false;
	}

	inline YVec2 YVec2::ClampAxes(float MinAxisVal, float MaxAxisVal) const
	{
		return YVec2(
			YMath::Clamp(this->x, MinAxisVal, MaxAxisVal),
			YMath::Clamp(this->y, MinAxisVal, MaxAxisVal)
			);
	}

	inline bool YVec2::ContainsNaN() const
	{
		if (YMath::IsNaN(this->x) || YMath::IsNaN(this->y)) {
			return true;
		}
		return false;
	}

	inline YVec2 YVec2::RoundToVector() const
	{
		return YVec2(YMath::Round(this->x), YMath::Round(this->y));
	}

	inline YVec2 YVec2::GetRotated(float AngleDeg) const
	{
		float AngleRad = YMath::DegToRad(AngleDeg);
		float Mag = this->Magnitude();
		float CurrAngleRad = YMath::ACos(this->x / Mag);

		return YVec2(Mag * YMath::Cos(AngleRad + CurrAngleRad), Mag * YMath::Sin(AngleRad + CurrAngleRad));
	}

	inline YVec2 YVec2::GetSignVector() const
	{
		return YVec2(this->x >= 0 ? 1.0f : -1.0f, this->y >= 0 ? 1.0f : -1.0f);
	}

	inline YVec2 YVec2::GetSafeNormal(float Tolerance = yEpsilon) const
	{
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return YVec2(0.0f, 0.0f);
		}
		return YVec2(this->x / this->Magnitude(),this->y / this->Magnitude());
	}

	inline YVec2 YVec2::GetAbs() const
	{
		return YVec2(YMath::Abs(this->x), YMath::Abs(this->y));
	}

	inline float YVec2::GetAbsMax() const
	{
		return YMath::Max(YMath::Abs(this->x), YMath::Abs(this->y));
	}

	inline float YVec2::GetMax() const
	{
		return YMath::Max(this->x, this->y);
	}

	inline float YVec2::GetMin() const
	{
		return YMath::Min(this->x, this->y);
	}

	inline void YVec2::Set(float InX, float InY)
	{
		this->x = InX;
		this->y = InY;
	}

	inline void YVec2::Normalize(float Tolerance = yEpsilon)
	{
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			this->x = 0;
			this->y = 0;
		}
		this->x /= this->Magnitude();
		this->y /= this->Magnitude();
	}

	//Addition
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

	inline float YVec2::Magnitude() const {
		return YMath::Sqrt(this->x * this->x + this->y * this->y);
	}

	inline float YVec2::MagnitudeSquared() const {
		return this->x * this->x + this->y * this->y;
	}

	//DOT PRODUCT
	inline float YVec2::dot(const YVec2& a) const {
		return this->x * a.x + this->y * a.y;
	}









	YVec2 YVec2::Max(const YVec2& A, const YVec2& B) {
		return YVec2(YMath::Max(A.x, B.x), YMath::Max(A.y, B.y));
	}

	YVec2 YVec2::Min(const YVec2& A, const YVec2& B) {
		return YVec2(YMath::Min(A.x, B.x), YMath::Min(A.y, B.y));
	}

	float YVec2::DotProduct(const YVec2& A, const YVec2& B)
	{
		return A.x * B.x + A.y * B.y;
	}

	float YVec2::CrossProduct(const YVec2& A, const YVec2& B) {
		return A.x * B.y - A.y * B.x;
	}

	float YVec2::Distance(const YVec2& V1, const YVec2& V2)
	{
		return YMath::Sqrt(((V1.x - V2.x) * (V1.x - V2.x)) + ((V1.y - V2.y)*(V1.y - V2.y)));
	}

	float YVec2::DistanceSquared(const YVec2& V1, const YVec2& V2)
	{
		return ((V1.x - V2.x) * (V1.x - V2.x)) + ((V1.y - V2.y) * (V1.y - V2.y));
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
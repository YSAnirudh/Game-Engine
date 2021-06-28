//HEADER INCLUDES
#pragma once
#include "Vector3D.h"
#include "Vector2D.h"
#include "Vector4D.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "EulerAngles.h"
#include <iostream>
namespace YSAoo {
	//
	// STATIC VARIABLE DECLARATIONS
	//
	const YVec3 YVec3::BackVector = YVec3(0.0f, 0.0f, -1.0f);
	const YVec3 YVec3::FrontVector = YVec3(0.0f, 0.0f, 1.0f);
	const YVec3 YVec3::LeftVector = YVec3(-1.0f, 0.0f, 0.0f);
	const YVec3 YVec3::RightVector = YVec3(1.0f, 0.0f, 0.0f);
	const YVec3 YVec3::DownVector = YVec3(0.0f, -1.0f, 0.0f);
	const YVec3 YVec3::UpVector = YVec3(0.0f, 1.0f, 0.0f);
	const YVec3 YVec3::XAxis = YVec3(1.0f, 0.0f, 0.0f);
	const YVec3 YVec3::YAxis = YVec3(0.0f, 1.0f, 0.0f);
	const YVec3 YVec3::ZAxis = YVec3(0.0f, 0.0f, 1.0f);
	const YVec3 YVec3::OneVector = YVec3(1.0f, 1.0f, 1.0f);
	const YVec3 YVec3::ZeroVector = YVec3(0.0f, 0.0f, 0.0f);

	//
	// CONSTRUCTORS START
	//
	YVec3::YVec3() : x(0), y(0), z(0) {}
	YVec3::YVec3(float InF) : x(InF), y(InF), z(InF) {}
	YVec3::YVec3(const YVec4& V) : x(V.x), y(V.y), z(V.z) {}
	YVec3::YVec3(const YVec3& a) : x(a.x), y(a.y), z(a.z) {}
	YVec3::YVec3(float x, float y, float z) : x(x), y(y), z(z) {}
	YVec3::YVec3(const YVec2& V, float InZ) : x(V.x), y(V.y), z(InZ) {}
	//
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//
	//Assignment -> Assigns the values x, y, z of V to this
	YVec3& YVec3::operator =(const YVec3& a) {
		this->x = a.x;
		this->y = a.y;
		this->z = a.z;
		return *this;
	}

	//Equality -> Returns true if this and Other are equal
	bool YVec3::operator ==(const YVec3& Other) const {
		if (YMath::IsZero(Other.x - this->x) && YMath::IsZero(Other.y - this->y) && YMath::IsZero(Other.z - this->z)) {
			return true;
		}
		return false;
	}

	// Inequality -> Returns true if this and Other are not equal
	bool YVec3::operator!=(const YVec3& Other) const {
		if (YMath::IsZero(Other.x - this->x) && YMath::IsZero(Other.y - this->y) && YMath::IsZero(Other.z - this->z)) {
			return false;
		}
		return true;
	}

	// Less Than -> Returns true if Magnitude of this is less than Magnitude of Other
	bool YVec3::operator<(const YVec3& Other) const {
		if (this->MagnitudeSquared() < Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// Less Than or Equal to -> Returns true if Magnitude of this is
	// less than or equal to Magnitude of Other 
	bool YVec3::operator<=(const YVec3& Other) const {
		if (this->MagnitudeSquared() <= Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// Greater Than -> Returns true if Magnitude of this is greater than Magnitude of Other
	bool YVec3::operator>(const YVec3& Other) const {
		if (this->MagnitudeSquared() > Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}

	// Greater Than or Equal to -> Returns true if Magnitude of this is
	// greater than or equal to Magnitude of Other 
	bool YVec3::operator>=(const YVec3& Other) const {
		if (this->MagnitudeSquared() >= Other.MagnitudeSquared()) {
			return true;
		}
		return false;
	}
	
	// this + YVec3 -> Adds the values V.x, V.y, V.z to this.x, this.y, this.z
	YVec3 YVec3::operator+(const YVec3& V) const {
		return YVec3(this->x + V.x, this->y + V.y, this->z + V.z);
	}

	// this + float -> Adds the value A to this.x, this.y, this.z
	YVec3 YVec3::operator+(float A) const {
		return YVec3(this->x + A, this->y + A, this->z + A);
	}

	// this += YVec3 -> Adds the values V.x, V.y, V.z to this.x, this.y, this.z
	YVec3 YVec3::operator+=(const YVec3& V) {
		return (*this) = (*this) + V;
	}

	// this += float -> Adds the value A to this.x, this.y, this.z and stores in this
	YVec3 YVec3::operator+=(float A) {
		return (*this) = (*this) + A;
	}

	// Negation -> Makes the values x, y, z of this opposite sign (+ -> - , - -> +)
	YVec3 YVec3::operator-() const {
		return YVec3(-this->x, -this->y, -this->z);
	}

	// this - YVec3 -> Subtracts the values V.x, V.y, V.z from this.x, this.y, this.z
	YVec3 YVec3::operator-(const YVec3& V) const {
		return YVec3(this->x - V.x, this->y - V.y, this->z - V.z);
	}

	// this - float -> Subtracts the value A from this.x, this.y, this.z
	YVec3 YVec3::operator-(float A) const {
		return YVec3(this->x - A, this->y - A, this->z - A);
	}

	// this -= YVec3 -> Subtracts the values V.x, V.y, V.z from this.x, this.y, this.z and stores in this
	YVec3 YVec3::operator-=(const YVec3& V) {
		return (*this) = (*this) - V;
	}

	// this -= float -> Subtracts the value A from this.x, this.y, this.z and stores in this
	YVec3 YVec3::operator-=(float A) {
		return (*this) = (*this) - A;
	}

	// this * YVec3 -> Multiplies the values this.x, this.y, this.z to V.x, V.y, V.z
	YVec3 YVec3::operator*(const YVec3& V) const {
		return YVec3(this->x * V.x, this->y * V.y, this->z * V.z);
	}

	// Scalar Multiplication -> Multiplies this.x, this.y, this.z with A
	YVec3 YVec3::operator*(float A) const {
		return YVec3(this->x * A, this->y * A, this->z * A);
	}
	YVec3 operator*(float A, const YVec3& V) {
		return V * A;
	}

	// this *= YVec3 -> Multiplies the values this.x, this.y, this.z to V.x, V.y, V.z and stores in this
	YVec3 YVec3::operator*=(const YVec3& V) {
		return (*this) = (*this) = (*this) * V;
	}

	// this *= A -> Multiplies the value this.x, this.y, this.z with A and stores in this
	YVec3 YVec3::operator*=(float A) {
		return (*this) = (*this) * A;
	}

	// this / YVec3 -> Divides the values this.x, this.y, this.z by V.x, V.y, V.z
	YVec3 YVec3::operator/(const YVec3& V) const {
		return YVec3(this->x / V.x, this->y / V.y, this->z / V.z);
	}

	// Scalar Division -> Divides this.x, this.y, this.z by A
	YVec3 YVec3::operator/(float A) const {
		return YVec3(this->x / A, this->y / A, this->z / A);
	}

	// this /= YVec3 -> Divides the values this.x, this.y, this.z by V.x, V.y, V.z and stores in this
	YVec3 YVec3::operator/=(const YVec3& V) {
		return (*this) = (*this) / V;
	}

	// this /= A -> Divides the value this.x, this.y, this.z by A and stores in this
	YVec3 YVec3::operator/=(float A) {
		return (*this) = (*this) / A;
	}

	// Dot Product -> Calculates the Dot Product between this and V
	float YVec3::operator|(const YVec3& V) const {
		return this->x * V.x + this->y * V.y + this->z * V.z;
	}

	// Cross Product Product -> Calculates the Cross Product between this and V
	YVec3 YVec3::operator^(const YVec3& V) const {
		return YVec3(
			this->y * V.z - V.y * this->z,
			-(this->x * V.z - V.x * this->z),
			this->x * V.y - V.x * this->y
		);
	}

	// OSTREAM OPERATOR
	std::ostream& operator<<(std::ostream& out, const YVec3& vec) {
		out << "X:" << vec.x << " " << "Y:" << vec.y << " " << "Z:" << vec.z << std::endl;
		return out;
	}

	// ISTREAM OPERATOR
	std::istream& operator>>(std::istream& in, YVec3& vec) {
		std::cout << "X:";
		in >> vec.x;
		std::cout << "Y:";
		in >> vec.y;
		std::cout << "Z:";
		in >> vec.z;
		return in;
	}

	// 
	// OPERATORS END
	//

	//
	// FUNCTIONS START
	//

	// Returns true if all the Components of this are equal
	bool YVec3::AllComponentsEqual(float Tolerance) const {
		if (YMath::AreEqual(this->x, this->y, Tolerance)) {
			if (YMath::AreEqual(this->y, this->z, Tolerance)) {
				return true;
			}
		}
		return false;
	}

	// Returns a copy vector of this bounded to values of vector Max and vector Min
	YVec3 YVec3::BoundToBox(const YVec3& Min, const YVec3& Max) const {
		if (Min.x > Max.x || Min.y > Max.y || Min.z > Max.z) {
			return *this;
		}

		return YVec3(
			YMath::Clamp(this->x, Min.x, Max.x),
			YMath::Clamp(this->y, Min.y, Max.y),
			YMath::Clamp(this->z, Min.z, Max.z)
		);
	}

	// Returns a copy vector of this bounded to a cube with Radius
	// Radius -> Half the length of the Cube
	YVec3 YVec3::BoundToCube(float Radius) const {
		return YVec3(
			YMath::Clamp(this->x, -Radius, Radius),
			YMath::Clamp(this->y, -Radius, Radius),
			YMath::Clamp(this->z, -Radius, Radius)
		);
	}

	// Returns a copy vector with component-wise maximum of this and Other
	YVec3 YVec3::ComponentMax(const YVec3& Other) const {
		return YVec3(
			YMath::Max(this->x, Other.x),
			YMath::Max(this->y, Other.y),
			YMath::Max(this->z, Other.z)
		);
	}

	// Returns a copy vector with component-wise minimum of this and Other
	YVec3 YVec3::ComponentMin(const YVec3& Other) const {
		return YVec3(
			YMath::Min(this->x, Other.x),
			YMath::Min(this->y, Other.y),
			YMath::Min(this->z, Other.z)
		);
	}

	// Returns true if either of this.x or this.y or this.z are NaN(Not a Number) 
	bool YVec3::ContainsNaN() const {
		if (YMath::IsNaN(this->x) || YMath::IsNaN(this->y) || YMath::IsNaN(this->z)) {
			return true;
		}
		return false;
	}

	// Returns the cosine of angle between 2D parts of this and B
	float YVec3::CosineAngle2D(YVec3 B) const {
		YVec3 thisOntoXY = YVec3(this->x, this->y, 0.0f);
		YVec3 BOntoXY = YVec3(B.x, B.y, 0.0f);
		return (thisOntoXY | BOntoXY) / (thisOntoXY.Magnitude() * BOntoXY.Magnitude());
	}

	// Returns true if this is equal to V with a Specified Tolerance
	bool YVec3::Equals(const YVec3& V, float Tolerance) const {
		if (YMath::IsNearlyZero(this->x - V.x, Tolerance)) {
			if (YMath::IsNearlyZero(this->y - V.y, Tolerance)) {
				if (YMath::IsNearlyZero(this->z - V.z, Tolerance)) {
					return true;
				}
			}
		}
		return false;
	}

	// Returns the copy of this vector snapped to the grid with grid size GridSize
	YVec3 YVec3::GridSnap(const float& GridSize) const {
		return YVec3(
			YMath::GridSnapHelp(x, GridSize),
			YMath::GridSnapHelp(y, GridSize),
			YMath::GridSnapHelp(z, GridSize)
		);
	}

	// Gets the heading/yaw angle of this vector
	// The angle about Y axis. angle 0 points towards +ve Z axis
	float YVec3::HeadingAngle() const {
		YVec3 refVector = YVec3(this->x, 0.0f, this->z);
		if (YMath::IsZero(refVector.Magnitude())) {
			return 0.0f;
		}
		float headingAngle = YMath::Abs(YMath::ACos(refVector.z / (refVector.Magnitude())));
		if (this->x < 0) {
			headingAngle = -headingAngle;
		}
		while (headingAngle > yPi) {
			headingAngle -= 2 * yPi;
		}

		while (headingAngle < -yPi) {
			headingAngle += 2 * yPi;
		}
		return headingAngle;
	}

	// Returns true if this vector is nearly zero with Tolerance
	bool YVec3::IsNearlyZero(float Tolerance) const {
		if (YMath::IsNearlyZero(this->x, Tolerance)) {
			if (YMath::IsNearlyZero(this->y, Tolerance)) {
				if (YMath::IsNearlyZero(this->z, Tolerance)) {
					return true;
				}
			}
		}
		return false;
	}

	// Returns true if this vector is Zero
	bool YVec3::IsZero() const {
		if (YMath::IsZero(this->x)) {
			if (YMath::IsZero(this->y)) {
				if (YMath::IsZero(this->z)) {
					return true;
				}
			}
		}
		return false;
	}

	// Returns true if this vector is normalized
	bool YVec3::IsNormalized() const {
		if (YMath::IsZero(this->MagnitudeSquared() - 1.0f)) {
			return true;
		}
		return false;
	}

	// Returns true if the vector is uniform => all values are same (x, y, z) with a Tolerance
	bool YVec3::IsUniform(float Tolerance) const {
		if (YMath::IsNearlyZero(this->x - this->y, Tolerance)) {
			if (YMath::IsNearlyZero(this->y - this->z, Tolerance)) {
				return true;
			}
		}
		return false;
	}

	// Returns true if the Length of this vector is Unit with a Tolerance
	bool YVec3::IsUnit(float LengthSquaredTolerance) const {
		if (YMath::IsNearlyZero(this->MagnitudeSquared() - 1.0f, LengthSquaredTolerance)) {
			return true;
		}
		return false;
	}

	// MARK FOR REVIEW
	// Returns the mirrored vector of this vector along Mirror Normal Vector
	YVec3 YVec3::MirrorByVector(const YVec3& MirrorNormal) const {
		return 2 * ((*this) | MirrorNormal) * MirrorNormal - (*this);
	}

	// Returns the vector projected onto the XY Plane
	YVec3 YVec3::Projection() const {
		return YVec3(this->x, this->y, 0.0f);
	}

	// Returns the copy of this vector projected onto A vector
	YVec3 YVec3::ProjectOnTo(const YVec3& A) const {
		return ((*this) | A) * A / A.MagnitudeSquared();
	}

	// Returns the copy of this vector projected onto Normal
	// Assumes Normal to be of Unit Length
	YVec3 YVec3::ProjectOnToNormal(const YVec3& Normal) const {
		return ((*this) | Normal) * Normal / Normal.Magnitude();
	}

	// Returns the reciprocal vector of this
	// Assigns a large value if a component is Zero
	YVec3 YVec3::Reciprocal() const {
		return YVec3(
			YMath::IsZero(this->x) ? YMath::posInf : 1 / this->x,
			YMath::IsZero(this->y) ? YMath::posInf : 1 / this->y,
			YMath::IsZero(this->z) ? YMath::posInf : 1 / this->z
		);
	}

	// Returns the copy of this vector rotated about Axis vector by AngleDeg degrees
	YVec3 YVec3::RotateAngleAxis(const float AngleDeg, const YVec3& Axis) const {
		YVec3 a = Axis.GetSafeNormal();
		float AngleRad = YMath::DegToRad(AngleDeg);
		return YMath::Cos(AngleRad) * ((*this) - ((*this)| a)* a) +
			YMath::Sin(AngleRad) * ((*this)^ a) + ((*this)| a)* a;
	}

	// Returns the Magnitude(Length) of this
	float YVec3::Magnitude() const {
		return YMath::Sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	// Returns the Magnitude(Length) of 2D components of this
	float YVec3::Magnitude2D() const {
		return YMath::Sqrt(this->x * this->x + this->y * this->y);
	}

	// MARK FOR REVIEW
	// Returns the Magnitude(Length) Squared of this
	float YVec3::MagnitudeSquared() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	// Returns the Magnitude(Length) Squared of 2D components of this
	float YVec3::MagnitudeSquared2D() const {
		return this->x * this->x + this->y * this->y;
	}

	// Assigns direction and length of this vector to the OUT Parameters
	void YVec3::ToDirectionAndLength(YVec3& OUT OutDir, float& OUT OutLength) const {
		OutDir = this->GetSafeNormal(yEpsilon);
		OutLength = this->Magnitude();
	}

	// MARK FOR REVIEW
	// Converts this vector to an orientation Quaternion
	YQuat YVec3::ToOrientationQuat() const {
		YVec3 xAxis = YVec3::UpVector ^ (*this);
		YVec3 yAxis = (*this) ^ xAxis;

		//Do a transpose
		YMat3x3 angMat = YMat3x3(xAxis, yAxis, *this);
		//.Transpose();

		return YQuat(angMat);
	}

	// MARK FOR REVIEW
	// Converts this vector to an orientation Euler
	YEuler YVec3::ToOrientationEuler() const {
		YVec3 xAxis = YVec3::UpVector ^ (*this);
		YVec3 yAxis = (*this) ^ xAxis;

		//Do a transpose
		YMat3x3 angMat = YMat3x3(xAxis, yAxis, *this);
		//.Transpose();

		return YEuler(angMat);
	}

	// Returns the Spherical Coordinates of the Unit Cartesian Coordinates in this
	// YVec2(theta, phi) , theta -> [0, PI], phi -> [-PI, PI]
	YVec2 YVec3::UnitCartesianToSpherical() const {
		float theta = YMath::ACos(this->z / this->Magnitude());
		float phi;
		if (this->x >= 0) {
			phi = YMath::ATan(this->y / this->x);
		}
		else { 
			phi = yPi + YMath::ATan(this->y / this->x);
		}
		while (phi > yPi) {
			phi -= 2 * yPi;
		}
		while (phi < yPi) {
			phi += 2 * yPi;
		}
		return YVec2(theta, phi);
	}

	// Returns the Euler angles of this vector
	YEuler YVec3::Rotation() const {
		return YEuler();
	}
	
	// Assigns the Best Axis vectors U and V of the Plane given this
	void YVec3::FindBestAxisVectors(const YVec3& OUT Axis1, const YVec3& OUT Axis3) const {
		
	}

	// Gets the absolute value vector of this
	YVec3 YVec3::GetAbs() const {
		return YVec3(YMath::Abs(this->x), YMath::Abs(this->y), YMath::Abs(this->z));
	}

	// Gets the maximum of components in absolut value vector of this
	float YVec3::GetAbsMax() const {
		return YMath::Max(YMath::Max(YMath::Abs(this->x), YMath::Abs(this->y)), YMath::Abs(this->z));
	}

	// Gets the minimum of components in absolut value vector of this
	float YVec3::GetAbsMin() const {
		return YMath::Min(YMath::Min(YMath::Abs(this->x), YMath::Abs(this->y)), YMath::Abs(this->z));
	}

	// Gets the copy vector of this vector with this' magnitude clamped to MaxSize
	YVec3 YVec3::GetClampedToMaxSize(float MaxSize) const {
		return ((*this) * MaxSize)/(this->Magnitude());
	}

	// Gets the copy vector of this vector with this' 2D magnitude clamped to MaxSize
	YVec3 YVec3::GetClampedToMaxSize2D(float MaxSize) const {
		YVec2 clamped(*this);
		return YVec3((clamped * MaxSize)/clamped.Magnitude(), this->z);
	}

	// Gets the copy vector of this with this.x, this.y, this.z clamped between min, max
	YVec3 YVec3::GetClampedToSize(float Min, float Max) const {
		return YVec3(
			YMath::Clamp(this->x, Min, Max),
			YMath::Clamp(this->y, Min, Max),
			YMath::Clamp(this->z, Min, Max)
		);
	}

	// Gets the copy vector of 2D components of this i.e. with this.x, this.y clamped between min, max
	YVec3 YVec3::GetClampedToSize2D(float Min, float Max) const {
		return YVec3(
			YMath::Clamp(this->x, Min, Max),
			YMath::Clamp(this->y, Min, Max),
			this->z
		);
	}

	// Gets the maximum of this.x, this.y, this.z
	float YVec3::GetMax() const {
		return YMath::Max(YMath::Max(this->x, this->y), this->z);
	}

	// Gets the minimum of this.x, this.y, this.z
	float YVec3::GetMin() const {
		return YMath::Min(YMath::Min(this->x, this->y), this->z);
	}

	// Gets the Normalized this vector if Magnitude(YVec3 this) != 0.0f
	// Gets YVec3(0.0f, 0.0f, 0.0f) otherwise
	YVec3 YVec3::GetSafeNormal(float Tolerance) const {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return YVec3(0.0f, 0.0f, 0.0f);
		}
		return (*this) / this->Magnitude();
	}

	// Gets the Normalized 2D components of this vector if Magnitude(YVec3 this) != 0.0f, with this->z = 0
	// Gets YVec3(0.0f, 0.0f, 0.0f) otherwise with a Tolerance
	YVec3 YVec3::GetSafeNormal2D(float Tolerance) const {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return YVec3(0.0f, 0.0f, 0.0f);
		}
		return YVec3(YVec2(this->x, this->y)/this->Magnitude(), 0.0f);
	}

	// Gets the signs of this.x, this.y, this.z as a YVec3(sign(x), sign(y), sign(z))
	YVec3 YVec3::GetSignVector() const {
		return YVec3(
			this->x < 0 ? -1.0f : 1.0f,
			this->y < 0 ? -1.0f : 1.0f,
			this->z < 0 ? -1.0f : 1.0f
		);
	}

	// Gets the normalized version of this vector without checking if the Magnitude is zero
	YVec3 YVec3::GetUnsafeNormal() const {
		return (*this)/this->Magnitude();
	}

	// Gets the normalized 2D version of this vector without checking if the Magnitude is zero
	YVec3 YVec3::GetUnsafeNormal2D() const {
		return YVec3(YVec2(this->x, this->y)/this->Magnitude(), this->z);
	}

	// Returns this with this = (this + V) bounded to a cube with Radius
	// Radius -> Half the length of the Cube
	void YVec3::AddBounded(const YVec3& V, float Radius) {
		*this += V;
		this->x = YMath::Clamp(this->x, -Radius, Radius);
		this->y = YMath::Clamp(this->y, -Radius, Radius);
		this->z = YMath::Clamp(this->z, -Radius, Radius);
	}
	
	// Normalizes this vector
	// Returns true if this vector was normalized otherwise false
	bool YVec3::Normalize(float Tolerance) {
		if (YMath::IsNearlyZero(this->Magnitude(), Tolerance)) {
			return false;
		}
		(*this) /= this->Magnitude();
		return true;
	}

	// Sets the values of this.x, this.y, this.z to InX, InY, InZ
	void YVec3::Set(float InX, float InY, float InZ) {
		this->x = InX;
		this->y = InY;
		this->z = InZ;
	}

	// MARK FOR REVIEW // Make sure it doesn't use while loops
	// Restricts the Euler Angles (Degrees) in this to (-180, 180) 
	void YVec3::UnwindEuler() {
		while (this->x > 180) {
			this->x -= 360;
		}
		while (this->x < -180) {
			this->x += 360;
		}
		while (this->y > 180) {
			this->y -= 360;
		}
		while (this->y < -180) {
			this->y += 360;
		}
		while (this->z > 180) {
			this->z -= 360;
		}
		while (this->z < -180) {
			this->z += 360;
		}
	}

	// Complete PushOut of the box totally out of the plane
	// Returns the PushOut
	float YVec3::BoxPushOut(const YVec3& Normal, const YVec3& Size) {
		return 0.0f;
	}

	// Returns true if the planes with Normals Normal1 and Normal2 are coincident
	bool YVec3::Coincident(const YVec3& Normal1, const YVec3& Normal2, float ParallelCosineThreshold) {
		if (YVec3(Normal1.GetSafeNormal()- Normal2.GetSafeNormal()).IsNearlyZero(ParallelCosineThreshold)) {
			return true;
		}
		return false;
	}

	// Returns true if the planes with Normals Normal1 and Normal2
	// and Base Points Base1 and Base2 are coplanar
	bool YVec3::Coplanar(const YVec3& Base1, const YVec3& Normal1, const YVec3& Base2, const YVec3& Normal2, float ParallelCosineThreshold) {
		if (YMath::IsNearlyZero((Base1 - Base2) | Normal1, ParallelCosineThreshold)) {
			if (YMath::IsNearlyZero((Base1 - Base2) | Normal2, ParallelCosineThreshold)) {
				if (YVec3::CrossProduct(Normal1, Normal2).IsNearlyZero(ParallelCosineThreshold)) {
					return true;
				}
			}
		}
		return false;
	}

	// Takes in the references and Assigns the orthonormal basis of those three vectors to themself
	void YVec3::CreateOrthonormalBasis(YVec3& OUT XAxis, YVec3& OUT YAxis, YVec3& OUT ZAxis) {
		YVec3 inpBasis[3] = { YVec3(XAxis), YVec3(YAxis), YVec3(ZAxis) };
		YVec3 orthoBasis[3] = { XAxis, YAxis, ZAxis };
		for (int i = 0; i < 3; i++) {
			YVec3 tempMinusInput;
			for (int j = 0; j < i; i++) {
				tempMinusInput -= inpBasis[i].ProjectOnTo(orthoBasis[j]);
			}
			orthoBasis[i] = inpBasis[i] - tempMinusInput;
		}
		// Might not be needed
		XAxis = orthoBasis[0];
		YAxis = orthoBasis[1];
		ZAxis = orthoBasis[2];
	}

	// Returns a vector containing degree values converted to radian values
	YVec3 YVec3::DegreesToRadians(const YVec3& DegVector) {
		return YVec3(
			YMath::DegToRad(DegVector.x),
			YMath::DegToRad(DegVector.y),
			YMath::DegToRad(DegVector.z)
		);
	}

	// Returns a vector containing radian values converted to degree values
	YVec3 YVec3::RadiansToDegrees(const YVec3& RadVector) {
		return YVec3(
			YMath::RadToDeg(RadVector.x),
			YMath::RadToDeg(RadVector.y),
			YMath::RadToDeg(RadVector.z)
		);
	}

	// Returns the Distance between two vectors
	float YVec3::Distance(const YVec3& V1, const YVec3& V2) {
		return YVec3(V1 - V2).Magnitude();
	}

	// Returns the 2D Distance between two vectors
	float YVec3::Distance2D(const YVec3& V1, const YVec3& V2) {
		return YVec3(V1 - V2).Magnitude2D();
	}

	// Returns the XY Distance between two vectors i.e. considering the X, Y coordinates
	float YVec3::DistanceXY(const YVec3& V1, const YVec3& V2) {
		return YVec3(YVec3(V1.x, V1.y, 0.0f) - YVec3(V2.x, V2.y, 0.0f)).Magnitude();
	}

	// Returns the Distance Squared between two vectors
	float YVec3::DistanceSquared(const YVec3& V1, const YVec3& V2) {
		return YVec3(V1 - V2).MagnitudeSquared();
	}

	// Returns the 2D Distance Squared between two vectors
	float YVec3::DistanceSquared2D(const YVec3& V1, const YVec3& V2) {
		return YVec3(V1 - V2).MagnitudeSquared2D();
	}

	// Returns the XY Distance Squared between two vectors i.e. considering the X, Y coordinates
	float YVec3::DistanceSquaredXY(const YVec3& V1, const YVec3& V2) {
		return YVec3(YVec3(V1.x, V1.y, 0.0f) - YVec3(V2.x, V2.y, 0.0f)).MagnitudeSquared();
	}

	// Returns the Dot Product between two vectors
	float YVec3::DotProduct(const YVec3& A, const YVec3& B) {
		return A|B;
	}

	// Returns the Cross Product between two vectors
	YVec3 YVec3::CrossProduct(const YVec3& A, const YVec3& B) {
		return A^B;
	}

	// Returns true if two normal vectors are nearly orthogonal with Tolerance - OrthogonalCosineThreshold
	// Normal vectors are assumed to be unit vectors
	bool YVec3::Orthogonal(const YVec3& Normal1, const YVec3& Normal2, float OrthogonalCosineThreshold) {
		if (YMath::IsNearlyZero(Normal1 | Normal2, OrthogonalCosineThreshold)) {
			return true;
		}
		return false;
	}

	// Returns true if two normal vectors are nearly parallel with Tolerance - ParallelCosineThreshold
	// Normal vectors are assumed to be unit vectors
	bool YVec3::Parallel(const YVec3& Normal1, const YVec3& Normal2, float ParallelCosineThreshold) {
		if (YVec3(Normal1 ^ Normal2).IsNearlyZero(ParallelCosineThreshold)) {
			return true;
		}
		return false;
	}

	// Returns the distance from a Point (YVec3) to a Plane 
	// with Base Point as PlaneBase and Normal vector as PlaneNormal
	// PlaneNormal assumed to be a unit vector
	float YVec3::PointPlaneDistance(const YVec3& Point, const YVec3& PlaneBase, const YVec3& PlaneNormal) {
		if (YMath::IsZero((Point - PlaneBase).Magnitude())) {
			return 0.0f;
		}
		float anglePointNormal = YMath::ACos(PlaneNormal | (Point - PlaneBase) / (Point - PlaneBase).Magnitude());
		float distance = YMath::Abs(PlaneNormal | (Point - PlaneBase));
		if (anglePointNormal > yPiBy2) {
			return -distance;
		}
		else if (anglePointNormal < yPiBy2) {
			return distance;
		}
		else {
			return 0.0f;
		}
	}

	// Returns the projection of a Point (YVec3) on a Plane 
	// with three points A, B, C lying in the Plane
	// A, B, C are considered in COUNTER CLOCK-WISE direction
	YVec3 YVec3::PointPlaneProject(const YVec3& Point, const YVec3& A, const YVec3& B, const YVec3& C) {
		YVec3 PlaneNormal = ((B - A) ^ (C - B)).GetSafeNormal();
		return Point - ((Point - A)|PlaneNormal) * PlaneNormal;
	}

	// Returns the projection of a Point (YVec3) on a Plane 
	// with Base Point as PlaneBase and Normal vector as PlaneNormal
	// PlaneNormal assumed to be a unit vector
	YVec3 YVec3::PointPlaneProject(const YVec3& Point, const YVec3& PlaneBase, const YVec3& PlaneNormal) {
		return Point - ((Point - PlaneBase) | PlaneNormal) * PlaneNormal;
	}

	// Returns the projection of a Vector on a Plane 
	// with Normal vector as PlaneNormal
	// PlaneNormal assumed to be a unit vector
	YVec3 YVec3::VectorPlaneProject(const YVec3& V, const YVec3& PlaneNormal) {
		return V - V.ProjectOnTo(PlaneNormal);
	}

	// Returns true if the two points are within a distance - Distance
	bool YVec3::PointsAreNear(const YVec3& Point1, const YVec3& Point2, float Distance) {
		if (YVec3::DistanceSquared(Point1, Point2) < Distance * Distance) {
			return true;
		}
		return false;
	}

	// Returns true if the two points are the same
	bool YVec3::PointsAreSame(const YVec3& Point1, const YVec3& Point2) {
		if (Point1.Equals(Point2)) {
			return true;
		}
		return false;
	}

	// Returns the triple product of X, Y, Z 
	// X dot (Y cross Z)
	float YVec3::TripleProduct(const YVec3& X, const YVec3& Y, const YVec3& Z) {
		return X|(Y^Z);
	}

	//
	// FUNCTIONS END
	//
}
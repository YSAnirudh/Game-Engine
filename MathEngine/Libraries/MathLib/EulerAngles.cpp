#pragma once
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Matrix4x3.h"
#include "GenMath.h"
#include "Vector3D.h"
namespace YSAoo {
	//ROLL, PITCH, YAW Notation (Degrees)
	//similar to bank, pitch, heading
	//
	// STATIC VARIABLE DECLARATIONS
	//

	const YEuler YEuler::ZeroEuler(0.f, 0.f, 0.f);

	//
	// CONSTRUCTORS START
	//
	YEuler::YEuler():roll(0), pitch(0), yaw(0) {}
	YEuler::YEuler(float roll, float pitch, float yaw) : roll(roll), pitch(pitch), yaw(yaw) {}
	
	YEuler::YEuler(float InF) : roll(InF), pitch(InF), yaw(InF) {}
	
	YEuler::YEuler(const YEuler& Euler) : roll(Euler.roll), pitch(Euler.pitch), yaw(Euler.yaw) {}
	
	YEuler::YEuler(const YQuat& Quat) {
		//Is not there right now
	}
	//
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//

	// Assignment -> Assigns the values of Euler to this
	void YEuler::operator=(const YEuler& Euler) {
		roll = Euler.roll;
		pitch = Euler.pitch;
		yaw = Euler.yaw;
	}

	//Equality -> Returns true if this and Euler are equal
	bool YEuler::operator==(const YEuler& Euler) const {
		if (YMath::AreEqual(roll, Euler.roll) &&
			YMath::AreEqual(pitch, Euler.pitch) && 
			YMath::AreEqual(yaw, Euler.yaw)
		) {
			return true;
		}
		return false;
	}
	
	// Inequality -> Returns true if this and Euler are not equal
	bool YEuler::operator!=(const YEuler& Euler) const {
		if (YMath::AreEqual(roll, Euler.roll) &&
			YMath::AreEqual(pitch, Euler.pitch) && 
			YMath::AreEqual(yaw, Euler.yaw)
		) {
			return false;
		}
		return true;
	}
	
	// this + Euler -> Adds this to Euler
	YEuler YEuler::operator+(const YEuler& Euler) const {
		return YEuler(
			roll + Euler.roll,
			pitch + Euler.pitch,
			yaw + Euler.yaw
		);
	}

	// this += Euler -> Adds this to Euler and stores in this
	YEuler YEuler::operator+=(const YEuler& Euler) {
		return (*this) + Euler;
	}

	// Negation -> Makes the values roll, pitch, yaw of this opposite in sign (+ -> - , - -> +)
	YEuler YEuler::operator-() const {
		return YEuler(-roll, -pitch, -yaw);	
	}
	
	// this - Euler -> Subtracts Euler from this respectively
	YEuler YEuler::operator-(const YEuler& Euler) const {
		return YEuler(
			roll - Euler.roll,
			pitch - Euler.pitch,
			yaw - Euler.yaw
		);
	}
	
	// this -= Euler -> Subtracts Euler from this respectively and stores in this
	YEuler YEuler::operator-=(const YEuler& Euler)  {
		return (*this) - Euler;
	}
	
	// Scalar Multiplication -> Multiplies this' values with Scale respectively
	YEuler YEuler::operator*(float Scale) const {
		return YEuler(
			roll * Scale,
			pitch * Scale,
			yaw * Scale
		);
	}
	
	YEuler operator*(float Scale, const YEuler& Euler) {
		return Euler * Scale;
	}

	// Scalar Multiplication -> Multiplies this' values with Scale respectively and stores in this
	YEuler YEuler::operator*=(float Scale) {
		return (*this) * Scale;
	}
	

	// OSTREAM OPERATOR
	std::ostream& operator<<(std::ostream& out, const YEuler& euler) {
		out << "Roll (Z):" << euler.roll << " " << "Pitch (X):" << euler.pitch << " " << "Yaw (Y):" << euler.yaw << std::endl;
		return out;
	}

	// ISTREAM OPERATOR
	std::istream& operator>>(std::istream& in, YEuler& euler) {
		std::cout << "Roll (Z):";
		in >> euler.roll;
		std::cout << "Pitch (X):";
		in >> euler.pitch;
		std::cout << "Yaw (Y):";
		in >> euler.yaw;
		return in;
	}

	// 
	// OPERATORS END
	//

	//
	// FUNCTIONS START
	//

	// Returns a copy with its angles clamped between -PI and PI
	// Should change, Shit implementation
	YEuler YEuler::Clamp() const {
		YEuler temp = (*this);
		temp.pitch = YMath::WrapAngle(temp.pitch, -180, 180);
		temp.roll = YMath::WrapAngle(temp.roll, -180, 180);
		temp.yaw = YMath::WrapAngle(temp.yaw, -180, 180);
		return temp;
	}
	
	// Returns true if any of the values in this are NaN
	bool YEuler::ContainsNaN() const {
		if (
			YMath::IsNaN(roll) || 
			YMath::IsNaN(pitch) || 
			YMath::IsNaN(yaw)
		) {
			return true;
		}
		return false;
	}
	
	// Returns true if this is equal to Euler within some Tolerance
	bool YEuler::Equals(const YEuler& Euler, float Tolerance = yEpsilon) const {
		if (YMath::AreNearlyEqual(roll, Euler.roll, Tolerance) &&
			YMath::AreNearlyEqual(pitch, Euler.pitch, Tolerance) && 
			YMath::AreNearlyEqual(yaw, Euler.yaw, Tolerance)
		) {
			return true;
		}
		return false;
	}
	
	// Returns YVec3 with roll, pitch, taw as their x, y, z rotations
	YVec3 YEuler::Vector() const {
		return YVec3(pitch, yaw, roll);
	}

	// Returns a copy of the Euler with it snapping to the RotGrid size given
	YEuler YEuler::GridSnap(const YEuler& RotGrid) const {
		return YEuler(
			YMath::GridSnapHelp(roll, RotGrid.roll),
			YMath::GridSnapHelp(pitch, RotGrid.pitch),
			YMath::GridSnapHelp(yaw, RotGrid.yaw)
		);
	}
	
	// Returns true if this Euler is nearly zero with some tolerance
	bool YEuler::IsNearlyZero(float Tolerance) const {
		if (YMath::IsNearlyZero(roll, Tolerance) &&
			YMath::IsNearlyZero(pitch, Tolerance) &&
			YMath::IsNearlyZero(yaw, Tolerance)
		) {
			return true;
		}
		return false;
	}
	
	// Returns true if this Euler is Zero
	bool YEuler::IsZero() const {
		if (YMath::IsZero(roll) &&
			YMath::IsZero(pitch) &&
			YMath::IsZero(yaw)
		) {
			return true;
		}
		return false;
	}
	
	// Returns this converted to a Quaternion
	YQuat YEuler::Quaternion() const {
		return YQuat(*this);
	}
	
	// Rotates the Vector by the angles mentioned in this
	YVec3 YEuler::RotateVector(const YVec3& V) const {
		YQuat rotate = this->Quaternion();
		return rotate.RotateVector(V);
	}
	
	// By looking at MakeClosest and its Euler Equivalent 
	// Sets the Euler MakeClosest to the one that is closest to this 
	void YEuler::SetClosestToMe(YEuler& MakeClosest) const {
		if (this->GetManhattanDistance(MakeClosest) > this->GetManhattanDistance(MakeClosest.GetEquivalentEuler())) {
			MakeClosest = MakeClosest.GetEquivalentEuler();
		}
	}
	
	// Rotates the Vector by the angles mentioned in this in the opposite direction
	YVec3 YEuler::UnrotateVector(const YVec3& V) const {
		YQuat rotate = this->Quaternion().GetConjugate();
		return rotate.UnrotateVector(V);
	}
	
	// Gets the Equivalent Euler to this
	YEuler YEuler::GetEquivalentEuler() const {
		return YEuler();
	}
	
	// Gets the Inverse of this Euler (Inverse Rotation)
	YEuler YEuler::GetInverse() const {
		// Check inverse of euler angle and try to change it to 
		// -yaw, -pitch, -roll
		return YQuat(*this).GetConjugate().Rotation();
	}

	// Gets the Manhattan distance between this and Euler
	float YEuler::GetManhattanDistance(const YEuler& Euler) const {
		YQuat Quat1 = YQuat(*this) * YQuat(Euler).GetConjugate();
		YEuler EulerEq = Quat1.Rotation();
		return (EulerEq.roll + EulerEq.pitch + EulerEq.yaw);
	}
	
	// Gets this after it is normalized
	YEuler YEuler::GetNormalized() const {
		YEuler temp = *this;
		temp.pitch = YMath::WrapAngle(temp.pitch, -yPiBy2, yPiBy2);
		temp.roll = YMath::WrapAngle(temp.roll, -yPi, yPi);
		temp.yaw = YMath::WrapAngle(temp.yaw, -yPi, yPi);

		if (YMath::AreEqual(temp.pitch, yPiBy2) || YMath::AreEqual(temp.pitch, -yPiBy2)) {
			return YEuler(0.0f, temp.pitch, temp.yaw);
		}
		return YEuler(temp.roll, temp.pitch, temp.yaw);
	}
	
	//
	void YEuler::GetWindingAndRemainder(YEuler& Winding,
				YEuler& Remainder) const {
		
	}

	// Normalizes this Euler
	void YEuler::Normalize() {
		YEuler temp = *this;
		temp.pitch = YMath::WrapAngle(temp.pitch, -yPiBy2, yPiBy2);
		temp.roll = YMath::WrapAngle(temp.roll, -yPi, yPi);
		temp.yaw = YMath::WrapAngle(temp.yaw, -yPi, yPi);

		if (YMath::AreEqual(temp.pitch, yPiBy2) || YMath::AreEqual(temp.pitch, -yPiBy2)) {
			*this = YEuler(0.0f, temp.pitch, temp.yaw);
		} else {
			*this = temp;
		}
	}

	// Assigns this to the Euler which is converted from RotMat
	void YEuler::FromRotationMat(YMat3x3& RotMat) {
		float sp = -RotMat.m[1][2];
		// Check for Gimbel lock
		if (YMath::Abs(sp) > 0.999999f) {
			// Looking straight up or down
			pitch = yPiBy2 * sp;
			// Compute heading, slam bank to zero
			yaw = atan2(-RotMat.m[2][0], RotMat.m[0][0]);
			roll = 0.0f;
		}
		else {
			// Compute angles. We don't have to use the "safe" asin
			// function because we already checked for range errors when
			// checking for Gimbel lock
			yaw = atan2(RotMat.m[0][2], RotMat.m[2][2]);
			pitch = asin(sp);
			roll = atan2(RotMat.m[1][0], RotMat.m[1][1]);
		}
	}

	// Assigns this to the Euler which is converted from RotMat
	void YEuler::FromRotationMat(YMat4x4& RotMat) {
		float sp = -RotMat.m[1][2];
		// Check for Gimbel lock
		if (YMath::Abs(sp) > 0.999999f) {
			// Looking straight up or down
			pitch = yPiBy2 * sp;
			// Compute heading, slam bank to zero
			yaw = atan2(-RotMat.m[2][0], RotMat.m[0][0]);
			roll = 0.0f;
		}
		else {
			// Compute angles. We don't have to use the "safe" asin
			// function because we already checked for range errors when
			// checking for Gimbel lock
			yaw = atan2(RotMat.m[0][2], RotMat.m[2][2]);
			pitch = asin(sp);
			roll = atan2(RotMat.m[1][0], RotMat.m[1][1]);
		}
	}
	

	//
	// Operators
	//

	//
	// Functions
	//

	void YEuler::canonize() {
		//-180 <= pitch < 180
		this->pitch = WrapPi(this->pitch);

		if (this->pitch < -yPiBy2) {
			this->pitch = -yPi - this->pitch;
			this->yaw += yPi; //heading
			this->roll += yPi; //bank
		}
		else if (this->pitch > yPiBy2) {
			this->pitch = yPi - this->pitch;
			this->yaw += yPi; //heading
			this->roll += yPi; //bank
		}

		//Gimbal Lock condition when pitch = 90 or -90
		if (fabs(this->pitch) > yPiBy2 - yEpsilon) {
			this->yaw += this->roll;
			this->roll = 0;
		}
		else {
			//restrict roll to -180 - 180
			this->roll = WrapPi(this->roll);
		}
		//restrict yaw to -180 - 180
		this->yaw = WrapPi(this->yaw);
	}

	void YEuler::fromObjectToInertialQuat(YQuat& q) {
		// Extract sin(pitch)
		float sp = -2.0f * (q.y * q.z - q.w * q.x);
		// Check for Gimbel lock, giving slight tolerance for numerical imprecision
		if (fabs(sp) > 0.9999f) {
			// Looking straight up or down
			pitch = yPiBy2 * sp;
			// Compute heading, slam bank to zero
			yaw = atan2(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
			roll = 0.0f;
		}
		else {
			pitch = asin(sp);
			yaw = atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
			roll = atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
		}
	}

	void YEuler::fromInertialToObjectQuat(YQuat& q) {
		float sp = -2.0f * (q.y * q.z + q.w * q.x);
		// Check for Gimbel lock, giving slight tolerance for numerical imprecision
		if (fabs(sp) > 0.9999f) {
			// Looking straight up or down
			pitch = yPiBy2 * sp;
			// Compute heading, slam bank to zero
			yaw = atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
			roll = 0.0f;
		}
		else {
			pitch = asin(sp);
			yaw = atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
			roll = atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
		}
	}

	void YEuler::fromWorldToObjectMat(YMat4x3& m) {
		float sp = -m.m23;
		// Check for Gimbel lock
		if (fabs(sp) > 9.99999f) {
			// Looking straight up or down
			pitch = yPiBy2 * sp;
			// Compute heading, slam bank to zero
			yaw = atan2(-m.m31, m.m11);
			roll = 0.0f;
		}
		else {
			// Compute angles. We don't have to use the "safe" asin
			// function because we already checked for range errors when
			// checking for Gimbel lock
			yaw = atan2(m.m13, m.m33);
			pitch = asin(sp);
			roll = atan2(m.m21, m.m22);
		}
	}

	void YEuler::fromObjectToWorldMat(YMat4x3& m) {
		float sp = -m.m32;
		// Check for Gimbel lock
		if (fabs(sp) > 9.99999f) {
			// Looking straight up or down
			pitch = yPiBy2 * sp;
			// Compute heading, slam bank to zero
			yaw = atan2(-m.m23, m.m11);
			roll = 0.0f;
		}
		else {
			// Compute angles. We don't have to use the "safe" asin
			// function because we already checked for range errors when
			// checking for Gimbel lock
			yaw = atan2(m.m31, m.m33);
			pitch = asin(sp);
			roll = atan2(m.m12, m.m22);
		}
	}

	

	//
	// Non Member Functions
	//
}
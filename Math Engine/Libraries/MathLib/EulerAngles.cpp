#include "EulerAngles.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Matrix4x3.h"
#include "GenMath.h"
#include "Vector3D.h"
namespace MathLib {
	//ROLL, PITCH, YAW Notation
	//similar to bank, pitch, heading
	//
	// Global Vars
	//

	const YEuler YEuler::ZeroEuler(0.f, 0.f, 0.f);

	//
	// Constructors
	//
	
	inline YEuler::YEuler():roll(0), pitch(0), yaw(0) {}
	inline YEuler::YEuler(float roll, float pitch, float yaw) : roll(roll), pitch(pitch), yaw(yaw) {}
	
	inline YEuler::YEuler(float InF) : roll(InF), pitch(InF), yaw(InF) {}
	
	inline YEuler::YEuler(const YEuler& Euler) : roll(Euler.roll), pitch(Euler.pitch), yaw(Euler.yaw) {}
	
	inline YEuler::YEuler(const YQuat& Quat) {
		//Is not there right now
	}
	
	inline void YEuler::operator=(const YEuler& Euler) {
		roll = Euler.roll;
		pitch = Euler.pitch;
		yaw = Euler.yaw;
	}

	inline bool YEuler::operator==(const YEuler& Euler) const {
		if (YMath::AreEqual(roll, Euler.roll) &&
			YMath::AreEqual(pitch, Euler.pitch) && 
			YMath::AreEqual(yaw, Euler.yaw)
		) {
			return true;
		}
		return false;
	}
	
	inline bool YEuler::operator!=(const YEuler& Euler) const {
		if (YMath::AreEqual(roll, Euler.roll) &&
			YMath::AreEqual(pitch, Euler.pitch) && 
			YMath::AreEqual(yaw, Euler.yaw)
		) {
			return false;
		}
		return true;
	}
	
	inline YEuler YEuler::operator+(const YEuler& Euler) const {
		return YEuler(
			roll + Euler.roll,
			pitch + Euler.pitch,
			yaw + Euler.yaw
		);
	}
	inline YEuler YEuler::operator+=(const YEuler& Euler) {
		return (*this) + Euler;
	}

	inline YEuler YEuler::operator-() const {
		return YEuler(-roll, -pitch, -yaw);	
	}
	
	inline YEuler YEuler::operator-(const YEuler& Euler) const {
		return YEuler(
			roll - Euler.roll,
			pitch - Euler.pitch,
			yaw - Euler.yaw
		);
	}
	
	inline YEuler YEuler::operator-=(const YEuler& Euler)  {
		return (*this) - Euler;
	}
	
	inline YEuler YEuler::operator*(float Scale) const {
		return YEuler(
			roll * Scale,
			pitch * Scale,
			yaw * Scale
		);
	}
	
	inline YEuler operator*(float Scale, const YEuler& Euler) {
		return Euler * Scale;
	}

	inline YEuler YEuler::operator*=(float Scale) {
		return (*this) * Scale;
	}
	
	inline YEuler YEuler::Clamp() const {
		YEuler temp = (*this);
		if (temp.pitch > yPi) {
			temp.pitch -= y2Pi;
		}
		if (temp.pitch < -yPi) {
			temp.pitch += y2Pi;
		}
		if (temp.roll > yPi) {
			temp.roll -= y2Pi;
		}
		if (temp.roll < -yPi) {
			temp.roll += y2Pi;
		}
		if (temp.yaw > yPi) {
			temp.yaw -= y2Pi;
		}
		if (temp.yaw < -yPi) {
			temp.yaw += y2Pi;
		}
		return temp;
	}
	
	inline bool YEuler::ContainsNaN() const {
		if (
			YMath::IsNaN(roll) || 
			YMath::IsNaN(pitch) || 
			YMath::IsNaN(yaw)
		) {
			return true;
		}
		return false;
	}
	
	inline bool YEuler::Equals(const YEuler& Euler, float Tolerance = yEpsilon) const {
		if (YMath::AreNearlyEqual(roll, Euler.roll, Tolerance) &&
			YMath::AreNearlyEqual(pitch, Euler.pitch, Tolerance) && 
			YMath::AreNearlyEqual(yaw, Euler.yaw, Tolerance)
		) {
			return true;
		}
		return false;
	}
	
	inline YVec3 YEuler::Vector() const {
		return YVec3(pitch, yaw, roll);
	}
	
	inline YEuler YEuler::GetEquivalentEuler() const {
		
	}
	
	inline YEuler YEuler::GetInverse() const {
		// Check inverse of euler angle and try to change it to 
		// -yaw, -pitch, -roll
		return YQuat(*this).GetConjugate().Rotation();
	}
	
	inline float YEuler::GetManhattanDistance(const YEuler& Euler) const {
		YQuat Quat1 = YQuat(*this) * YQuat(Euler).GetConjugate();
		YEuler EulerEq = Quat1.Rotation();
		return (EulerEq.roll + EulerEq.pitch + EulerEq.yaw);
	}
	
	inline YEuler YEuler::GetNormalized() const {
		YEuler temp = *this;
		temp.pitch = YMath::WrapAngle(temp.pitch, -yPiBy2, yPiBy2);
		temp.roll = YMath::WrapAngle(temp.roll, -yPi, yPi);
		temp.yaw = YMath::WrapAngle(temp.yaw, -yPi, yPi);

		if (YMath::AreEqual(temp.pitch, yPiBy2) || YMath::AreEqual(temp.pitch, -yPiBy2)) {
			return YEuler(0.0f, temp.pitch, temp.yaw);
		}
		return YEuler(temp.roll, temp.pitch, temp.yaw);
	}
	
	inline void YEuler::GetWindingAndRemainder(YEuler& Winding,
				YEuler& Remainder) const {
		
	}
	
	inline YEuler YEuler::GridSnap(const YEuler& RotGrid) const {
		return YEuler(
			YMath::GridSnapHelp(roll, RotGrid.roll),
			YMath::GridSnapHelp(pitch, RotGrid.pitch),
			YMath::GridSnapHelp(yaw, RotGrid.yaw)
		);
	}
	
	inline bool YEuler::IsNearlyZero(float Tolerance) const {
		if (YMath::IsNearlyZero(roll, Tolerance) &&
			YMath::IsNearlyZero(pitch, Tolerance) &&
			YMath::IsNearlyZero(yaw, Tolerance)
		) {
			return true;
		}
		return false;
	}
	
	inline bool YEuler::IsZero() const {
		if (YMath::IsZero(roll) &&
			YMath::IsZero(pitch) &&
			YMath::IsZero(yaw)
		) {
			return true;
		}
		return false;
	}
	
	inline void YEuler::Normalize() {
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
	
	inline YQuat YEuler::Quaternion() const {
		return YQuat(*this);
	}
	
	inline YVec3 YEuler::RotateVector(const YVec3& V) const {
		YQuat rotate = this->Quaternion();
		return rotate.RotateVector(V);
	}
	
	inline void YEuler::SetClosestToMe(YEuler& MakeClosest) const {
		if (this->GetManhattanDistance(MakeClosest) > this->GetManhattanDistance(MakeClosest.GetEquivalentEuler())) {
			MakeClosest = MakeClosest.GetEquivalentEuler();
		}
	}
	
	inline YVec3 YEuler::UnRotateVector(const YVec3& V) const {
		YQuat rotate = this->Quaternion().GetConjugate();
		return rotate.RotateVector(V);
	}

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
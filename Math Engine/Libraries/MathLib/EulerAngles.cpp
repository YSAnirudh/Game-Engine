#include "EulerAngles.h"

namespace MathLib {
	//ROLL, PITCH, YAW Notation
	//similar to bank, pitch, heading
	//
	// Global Vars
	//

	const YEuler yIdentityEuler(0.f, 0.f, 0.f);

	//
	// Constructors
	//
	
	YEuler::YEuler():roll(0), pitch(0), yaw(0) {}
	YEuler::YEuler(float roll, float pitch, float yaw) : roll(roll), pitch(pitch), yaw(yaw) {}

	//
	// Operators
	//

	//
	// Functions
	//

	void YEuler::canonize() {
		//-180 <= pitch < 180
		this->pitch = wrapPi(this->pitch);

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
			this->roll = wrapPi(this->roll);
		}
		//restrict yaw to -180 - 180
		this->yaw = wrapPi(this->yaw);
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

	void YEuler::fromRotationMat(YMat3x3& m) {
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

	//
	// Non Member Functions
	//
}
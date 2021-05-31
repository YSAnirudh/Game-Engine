#pragma once
#include <iostream>
#include "Quaternion.h"
#include "Vector3D.h"
#include "EulerAngles.h"
#include "Matrix4x3.h"
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include <assert.h>
#include "GenMath.h"
namespace MathLib {
	//
	// STATIC VARIABLE DECLARATIONS
	//
	const YQuat YQuat::Identity(1.f, 0.f, 0.f, 0.f);

	//
	// CONSTRUCTORS START
	//
	YQuat::YQuat():w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

	YQuat::YQuat(float InW, float InX, float InY, float InZ) : w(InW), x(InX), y(InY), z(InZ) {}

	YQuat::YQuat(const YMat4x4& M) {
		float SQ = M.m[0][0] + M.m[1][1] + M.m[2][2];

		float bigVal = YMath::Sqrt(SQ + 1.0f) * 0.5f;

		float mult = 0.25f / bigVal;

		w = bigVal;
		x = (M.m[2][1] - M.m[1][2]) * mult;
		y = (M.m[0][2] - M.m[2][0]) * mult;
		z = (M.m[1][0] - M.m[0][1]) * mult;
	}

	YQuat::YQuat(const YMat3x3& M) {
		float SQ = M.m[0][0] + M.m[1][1] + M.m[2][2];

		float bigVal = YMath::Sqrt(SQ + 1.0f) * 0.5f;

		float mult = 0.25f / bigVal;

		w = bigVal;
		x = (M.m[2][1] - M.m[1][2]) * mult;
		y = (M.m[0][2] - M.m[2][0]) * mult;
		z = (M.m[1][0] - M.m[0][1]) * mult;
	}

	YQuat::YQuat(const YEuler& E) {
		float sy, sp, sr, cy, cp, cr;

		YMath::SinCos(&sy, &cy, YMath::DegToRad(E.roll / 2));
		YMath::SinCos(&sp, &cp, YMath::DegToRad(E.yaw / 2));
		YMath::SinCos(&sr, &cr, YMath::DegToRad(E.pitch / 2));

		w = cr * cp * cy + sr * sp * sy;
		x = sr * cp * cy - cr * sp * sy;
		y = cr * sp * cy + sr * cp * sy;
		z = cr * cp * sy - sr * sp * cy;
	}

	YQuat::YQuat(const YVec3& Axis, float AngleDeg) {
		float sin, cos;
		YMath::SinCos(&sin, &cos, YMath::DegToRad(AngleDeg/2));

		w = cos;
		x = sin * Axis.x;
		y = sin * Axis.y;
		z = sin * Axis.z;
	}
	
	YQuat::YQuat(float InW, const YVec3& InXYZ) :w(InW), x(InXYZ.x), y(InXYZ.y), z(InXYZ.z) {}
	
	//
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//

	// Assignment -> Assigns Q to this
	YQuat YQuat::operator=(const YQuat& Q) {
		w = Q.w;
		x = Q.x;
		y = Q.y;
		z = Q.z;
		return *this;
	}

	// Equaility -> Returns true if this and Q are equal
	bool YQuat::operator==(const YQuat& Q) const {
		if (
			YMath::AreEqual(w, Q.w) &&
			YMath::AreEqual(x, Q.x) &&
			YMath::AreEqual(y, Q.y) &&
			YMath::AreEqual(z, Q.z)
		) {
			return true;
		}
		return false;
	}

	// Inequality -> Returns true if this and Q are not equal
	bool YQuat::operator!=(const YQuat& Q) const {
		if (
			YMath::AreEqual(w, Q.w) &&
			YMath::AreEqual(x, Q.x) &&
			YMath::AreEqual(y, Q.y) &&
			YMath::AreEqual(z, Q.z)
		) {
			return false;
		}
		return true;
	}

	// this + YQuat -> Adds this to Q
	YQuat YQuat::operator+(const YQuat& Q) const {
		return YQuat(w + Q.w, x + Q.x, y + Q.y, z + Q.z);
	}

	// this += YQuat -> Adds this to Q and stores in this
	YQuat YQuat::operator+=(const YQuat& Q) {
		return (*this) = *this + Q;
	}

	// Negation -> Makes the components of this opposite sign (+ -> - , - -> +)
	YQuat YQuat::operator-() const {
		return YQuat(-w, -x, -y, -z);
	}

	// this - YQuat -> Subtracts Q from this
	YQuat YQuat::operator-(const YQuat& Q) const {
		return YQuat(w - Q.w, x - Q.x, y - Q.y, z - Q.z);
	}

	// this -= YQuat -> Subtracts Q from this and stores in this
	YQuat YQuat::operator-=(const YQuat& Q) {
		return (*this) = *this - Q;
	}
	
	// this * YVec3 -> multiplies V with this
	YVec3 YQuat::operator*(const YVec3& V) const {
		YVec3 result;
		result = V + (w * 2 * YVec3(x, y, z) ^ V) + (YVec3(x, y, z) ^ (2 * (YVec3(x, y, z) ^ V)));
		return result;
	}

	// YVec3 * this -> multiplies V with this
	YVec3 operator*(const YVec3& V, const YQuat& Q) {
		return Q * V;
	}

	// this * YMat3x3 -> multiplies M with this
	YMat3x3 YQuat::operator*(const YMat3x3& M) const	{
		return YMat3x3();
	}

	// this * YMat4x4 -> multiplies M with this
	YMat4x4 YQuat::operator*(const YMat4x4& M) const {
		return YMat4x4();
	}

	// this * YQuat -> multiplies Q with this
	YQuat YQuat::operator*(const YQuat& Q) const {
		YVec3 thisV = YVec3(this->x, this->y, this->z);
		YVec3 QV = YVec3(Q.x, Q.y, Q.z);

		return YQuat(
			this->w * Q.w - (thisV | QV),
			this->w * QV + Q.w * thisV + (thisV ^ QV)
		);
	}

	// this *= YQuat -> multiplies Q with this and stores in this
	YQuat YQuat::operator*=(const YQuat& Q) {
		return (*this) = *this * Q;
	}

	// this * Scale -> multiplies Scale with this
	YQuat YQuat::operator*(const float Scale) const {
		return YQuat(Scale * w, Scale * x, Scale * y, Scale * z);
	}

	// Scale * this -> multiplies Scale with this
	YQuat operator*(const float Scale, const YQuat& Q) {
		return Q * Scale;
	}

	// this *= Scale -> multiplies Scale with this and stores in this
	YQuat YQuat::operator*=(const float Scale) {
		return (*this) = *this * Scale;
	}

	// this / Scale -> divides this by Scale
	YQuat YQuat::operator/(const float Scale) const {
		if (YMath::IsZero(Scale)) {
			return YQuat(1.0f, 0.0f, 0.0f, 0.0f);
		}
		float Scale1 = 1 / Scale;
		return YQuat(Scale1 * w, Scale1 * x, Scale1 * y, Scale1 * z);
	}

	// this /= Scale -> divides this by Scale and stores in this
	YQuat YQuat::operator/=(const float Scale) {
		return (*this) = *this / Scale;
	}

	// Dot Product -> Calculates the Dot Product between this and Q
	float YQuat::operator|(const YQuat& Q) const {
		return w*Q.w + x*Q.x + y*Q.y + z*Q.z;
	}
	
	// Get the rotation angle of the quaternion
	float YQuat::GetRotationAngle() const {
		return YMath::ACos(w) * 2.0f;
	}

	// Get the axis around which the quaternion is set to rotate about
	YVec3 YQuat::GetRotationAxis() const {
		float sinThetaOver2Sq = 1.0f - w * w;
		if (sinThetaOver2Sq <= 0.0f) {
			return YVec3(1.0f, 0.0f, 0.0f);
		}
		float oneOverSinThetaOver2 = 1.0f / YMath::Sqrt(sinThetaOver2Sq);
		return YVec3(
			x * oneOverSinThetaOver2,
			y * oneOverSinThetaOver2,
			z * oneOverSinThetaOver2
		);
	}
	
	// Get the rotation angle of the quaternion
	float YQuat::GetAngle() const {
		return YMath::ACos(w) * 2.0f;
	}
	
	YVec3 YQuat::GetAxisX() const {
		return YVec3();
	}
	
	YVec3 YQuat::GetAxisY() const
	{
		return YVec3();
	}
	
	YVec3 YQuat::GetAxisZ() const
	{
		return YVec3();
	}
	
	YVec3 YQuat::GetForwardVector() const
	{
		return YVec3();
	}
	
	YVec3 YQuat::GetUpVector() const
	{
		return YVec3();
	}
	
	YVec3 YQuat::GetRightVector() const
	{
		return YVec3();
	}
	
	// Gets the normalized form of this quaternion
	YQuat YQuat::GetNormalized(float Tolerance = yEpsilon) const {
		if (YMath::IsNearlyZero(MagnitudeSquared(), Tolerance)) {
			return Identity;
		}
		return (*this) / Magnitude();
	}

	// Returns the conjugate of this Quat
	YQuat YQuat::GetConjugate() const {
		return YQuat(w, -x, -y, -z);
	}

	YQuat YQuat::GetInverse() const {
		return this->GetConjugate() / this->MagnitudeSquared();
	}

	float YQuat::GetTwistAngle(const YVec3& TwistAxis) const {
		return 0.0f;
	}
	
	// Gets the Angular distance between this and Q
	float YQuat::AngularDistance(const YQuat& Q) const {
		YQuat qd = this->GetInverse() * Q;
		return YMath::RadToDeg(2 * YMath::ATan2(YVec3(qd.x, qd.y, qd.z).Magnitude(), qd.w));
	}
	
	// Returns true if a component value is NaN
	bool YQuat::ContainsNan() const {
		if (YMath::IsNaN(w) || 
			YMath::IsNaN(x) || 
			YMath::IsNaN(y) || 
			YMath::IsNaN(z)
		) {
			return true;
		}
		return false;
	}
	
	// Returns true if this is equal to Q with a Tolerance
	bool YQuat::Equals(const YQuat& Q, float Tolerance = yEpsilon) const {
		if (YMath::AreEqual(w, Q.w, Tolerance) &&
			YMath::AreEqual(x, Q.x, Tolerance) &&
			YMath::AreEqual(y, Q.y, Tolerance) &&
			YMath::AreEqual(z, Q.z, Tolerance)
		) {
			return true;
		}
		return false;
	}
	
	// Returns true if this Quaternion is a Identity Quaternion with a Tolerance
	bool YQuat::IsIdentity(float Tolerance = yEpsilon) const {
		if (this->Equals(YQuat::Identity, Tolerance)) {
			return true;
		}
		return false;
	}
	
	// Returns true if this quaternion is normalized
	bool YQuat::IsNormalized() const {
		if (YMath::AreEqual(1.0f, this->MagnitudeSquared())) {
			return true;
		}
		return false;
	}
	
	// Returns a Quaternion with natural log applied to this Quat
	YQuat YQuat::Log() const {
		if (YMath::IsZero(YVec3(x, y, z).Magnitude())) {
			return *this;
		}
		float mag = this->Magnitude();
		return YQuat(
			YMath::Log(mag),
			(YVec3(x,y,z) / YVec3(x,y,z).Magnitude()) * YMath::ACos(w / mag)
		);
	}
	
	// Returns a Quaternion with exponentiation applied to this Quat
	YQuat YQuat::Exp() const {
		YVec3 vec = YVec3(x,y,z);
		if (YMath::IsZero(vec.Magnitude())) {
			return *this;
		}
		float vecMag = vec.Magnitude();

		return YMath::Exp(w) * YQuat(
			YMath::Cos(vecMag),
			vec * YMath::Sin(vecMag) / vecMag
		);
	}
	
	// Returns the vector V rotated using this Quaternion
	YVec3 YQuat::RotateVector(YVec3 V) const {
		YQuat Helper = YQuat(1.0f, V);
		Helper = (*this) * Helper * this->GetInverse();
		return YVec3(Helper.x, Helper.y, Helper.z);
	}
	
	// Returns the Euler angle equivalent of this Quaternion
	YEuler YQuat::Rotation() const {
		return YEuler();
	}

	YMat4x4 YQuat::RotationMatrix4() const {
		return YMat4x4();
	}

	YMat3x3 YQuat::RotationMatrix3() const {
		return YMat3x3();
	}
	
	// Returns the magnitude of this
	float YQuat::Magnitude() const {
		return YMath::Sqrt(w*w + x*x + y*y + z*z);
	}
	
	// Returns the magnitude squared of this
	float YQuat::MagnitudeSquared() const {
		return w*w + x*x + y*y + z*z;
	}

	// Gets the Unrotated vector V of this (- this rotation) 
	YVec3 YQuat::UnrotateVector(YVec3 V) const {
		YQuat Helper = YQuat(1.0f, V);
		Helper = this->GetInverse() * Helper * (*this);
		return YVec3(Helper.x, Helper.y, Helper.z);
	}
	
	YVec3 YQuat::Vector() const {
		return YVec3();
	}
	
	// Assigns the Axis and Angle present in this to Axis and Angle variables
	void YQuat::ToAxisAngle(YVec3& Axis, float& Angle) {
		Angle = YMath::RadToDeg(2 * YMath::ACos(w));
		float sq = YMath::Sqrt(1 - w*w);
		Axis.x = x / sq;
		Axis.y = y / sq;
		Axis.z = z / sq;
	}
	

	void YQuat::EnforceShortestArcWith(const YQuat& Other) {
		
	}

	// Makes this the conjugate of itself
	void YQuat::Conjugate() {
		x = -x;
		y = -y;
		z = -z;
		w = w;
	}

	// Makes this an Identity Quaternion
	void YQuat::ToIdentity() {
		w = 1.0f; x = y = z = 0.0f;
	}

	// Normalizes this Quat
	void YQuat::Normalize() {
		float mag = (float)sqrt(w * w + x * x + y * y + z * z);
		if (mag > 0.0f) {
			float oneOverMag = 1.0f / mag;
			w *= oneOverMag;
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
		else {
			assert(false);
			ToIdentity();
		}
	}

	void YQuat::RotationX(float theta) {
		theta = YMath::DegToRad(theta);
		w = cos(theta * .5f);
		x = sin(theta * .5f);
		y = 0.0f;
		z = 0.0f;
	}
	void YQuat::RotationY(float theta) {
		theta = YMath::DegToRad(theta);
		w = cos(theta * .5f);
		x = 0.0f;
		y = sin(theta * .5f);
		z = 0.0f;
	}
	void YQuat::RotationZ(float theta) {
		theta = YMath::DegToRad(theta);
		w = cos(theta * .5f);
		x = 0.0f;
		y = 0.0f;
		z = sin(theta * .5f);
	}
	
	// Fast Bilerp
	YQuat YQuat::FastBilerp(const YQuat& P00, 
				const YQuat& P10, 
				const YQuat& P01, 
				const YQuat& P11, 
				float FracX,
				float FracY) 
	{
		return YQuat();
	}
	
	// Fast Lerp between A and B with Alpha
	YQuat YQuat::FastLerp(const YQuat& A, const YQuat& B, const float Alpha) {
		return (1 - Alpha) * A + (Alpha * B);
	}
	
	YQuat YQuat::FindBetween(const YVec3& Vector1, const YVec3& Vector2) 
	{
		return YQuat();
	}
	
	YQuat YQuat::FindBetweenNormals(const YVec3& Normal1, const YVec3& Normal2) 
	{
		return YQuat();
	}
	
	YQuat YQuat::FindBetweenVectors(const YVec3& Vector1, const YVec3& Vector2) 
	{
		return YQuat();
	}
	
	YQuat YQuat::MakeFromEuler(const YEuler& Euler) {
		return YQuat();
	}
	
	// Makes a Quaternion from given Axis and Angle Theta
	YQuat YQuat::MakeFromAxisAngle(const YVec3& Axis, float Theta) {
		assert(YMath::AreEqual(YMath::Abs(Axis.Magnitude()), 1.0f));
		float sin, cos;
		YMath::SinCos(&sin, &cos, Theta * 0.5f);
		return YQuat (
			cos,
			Axis.x * sin,
			Axis.y * sin,
			Axis.z * sin
		);
	}

	// Slerp
	YQuat YQuat::Slerp(const YQuat& Quat1, const YQuat& Quat2, float Slerp) {
		if (Slerp <= 0.0f) return Quat1;
		if (Slerp >= 1.0f) return Quat2;
		YQuat q1 = Quat1;
		YQuat q2 = Quat2;
		float cosOmega = Quat1 | Quat2;
		if (cosOmega < 0.0f) {
			q2 = -q2;
			cosOmega = -cosOmega;
		}
		assert(cosOmega < 1.1f);
		float k0, k1;
		if (cosOmega > 0.9999f) {
			k0 = -(Slerp - 1.f);
			k1 = Slerp;
		}
		else {
			float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
			float omega = atan2(sinOmega, cosOmega);
			float oneOverSinOmega = 1.0f / sinOmega;
			// Compute interpolation parameters
			k0 = sin((1.0f - Slerp) * omega) * oneOverSinOmega;
			k1 = sin(Slerp * omega) * oneOverSinOmega;
		}
		return (k0 * q1 + k1 * q2).GetNormalized();
	}
	
	//Slerp Unnormalized
	YQuat YQuat::SlerpUnNormalized(const YQuat& Quat1, const YQuat& Quat2, float Slerp) {
		if (Slerp <= 0.0f) return Quat1;
		if (Slerp >= 1.0f) return Quat2;
		YQuat q1 = Quat1;
		YQuat q2 = Quat2;
		float cosOmega = Quat1 | Quat2;
		if (cosOmega < 0.0f) {
			q2 = -q2;
			cosOmega = -cosOmega;
		}
		assert(cosOmega < 1.1f);
		float k0, k1;
		if (cosOmega > 0.9999f) {
			k0 = -(Slerp - 1.f);
			k1 = Slerp;
		}
		else {
			float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
			float omega = atan2(sinOmega, cosOmega);
			float oneOverSinOmega = 1.0f / sinOmega;
			// Compute interpolation parameters
			k0 = sin((1.0f - Slerp) * omega) * oneOverSinOmega;
			k1 = sin(Slerp * omega) * oneOverSinOmega;
		}
		return (k0 * q1 + k1 * q2);
	}

	//Slerp full path
	YQuat YQuat::SlerpFullPath(const YQuat& Quat1, const YQuat& Quat2, float Alpha) 
	{
		return YQuat();
	}
	
	// Slerp full path unnormalized
	YQuat YQuat::SlerpFullPathUnNormalized(const YQuat& Quat1, const YQuat& Quat2, float Alpha) 
	{
		return YQuat();
	}

	//
	// FUNCTIONS END
	//
}
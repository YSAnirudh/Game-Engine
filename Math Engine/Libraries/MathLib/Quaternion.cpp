#include "Quaternion.h"
#include "Vector3D.h"
#include "EulerAngles.h"
#include "Matrix4x3.h"
#include "Matrix4x4.h"
#include <assert.h>
#include "GenMath.h"
namespace MathLib {
	const YQuat yIdentityQuaternion(1.f, 0.f, 0.f, 0.f);

	YQuat::YQuat():w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

	YQuat::YQuat(float InW, float InX, float InY, float InZ) : w(InW), x(InX), y(InY), z(InZ) {}

	YQuat::YQuat(const YMat4x4& M) {
		float WSQ1 = M.m[0][0] + M.m[1][1] + M.m[2][2];
		float XSQ1 = M.m[0][0] - M.m[1][1] - M.m[2][2];
		float YSQ1 = -M.m[0][0] + M.m[1][1] - M.m[2][2];
		float ZSQ1 = -M.m[0][0] - M.m[1][1] + M.m[2][2];

		int big = 0;
		float SQ = WSQ1;
		if (XSQ1 > SQ) {
			SQ = XSQ1;
			big = 1;
		}
		if (YSQ1 > SQ) {
			SQ = YSQ1;
			big = 2;
		}
		if (ZSQ1 > SQ) {
			SQ = ZSQ1;
			big = 3;
		}

		float bigVal = YMath::Sqrt(SQ + 1.0f) * 0.5f;

		float mult = 0.25f / bigVal;

		switch (big)
		{
		case 0:
			w = bigVal;
			x = (M.m[1][2] - M.m[2][1]) * mult;
			y = (M.m[2][0] - M.m[0][2]) * mult;
			z = (M.m[0][1] - M.m[1][0]) * mult;
			break;
		case 1:
			x = bigVal;
			w = (M.m[1][2] - M.m[2][1]) * mult;
			y = (M.m[0][1] + M.m[1][0]) * mult;
			z = (M.m[2][0] + M.m[0][2]) * mult;
			break;
		case 2:
			y = bigVal;
			x = (M.m[0][1] + M.m[1][0]) * mult;
			w = (M.m[2][0] - M.m[0][2]) * mult;
			z = (M.m[1][2] + M.m[2][1]) * mult;
			break;
		case 3:
			z = bigVal;
			x = (M.m[2][0] + M.m[0][2]) * mult;
			y = (M.m[1][2] + M.m[2][1]) * mult;
			w = (M.m[0][1] - M.m[1][0]) * mult;
			break;
		default:
			break;
		}
	}

	YQuat::YQuat(const YMat3x3& M) {
		float WSQ1 = M.m[0][0] + M.m[1][1] + M.m[2][2];
		float XSQ1 = M.m[0][0] - M.m[1][1] - M.m[2][2];
		float YSQ1 = -M.m[0][0] + M.m[1][1] - M.m[2][2];
		float ZSQ1 = -M.m[0][0] - M.m[1][1] + M.m[2][2];

		int big = 0;
		float SQ = WSQ1;
		if (XSQ1 > SQ) {
			SQ = XSQ1;
			big = 1;
		}
		if (YSQ1 > SQ) {
			SQ = YSQ1;
			big = 2;
		}
		if (ZSQ1 > SQ) {
			SQ = ZSQ1;
			big = 3;
		}

		float bigVal = YMath::Sqrt(SQ + 1.0f) * 0.5f;

		float mult = 0.25f / bigVal;

		switch (big)
		{
		case 0:
			w = bigVal;
			x = (M.m[1][2] - M.m[2][1]) * mult;
			y = (M.m[2][0] - M.m[0][2]) * mult;
			z = (M.m[0][1] - M.m[1][0]) * mult;
			break;
		case 1:
			x = bigVal;
			w = (M.m[1][2] - M.m[2][1]) * mult;
			y = (M.m[0][1] + M.m[1][0]) * mult;
			z = (M.m[2][0] + M.m[0][2]) * mult;
			break;
		case 2:
			y = bigVal;
			x = (M.m[0][1] + M.m[1][0]) * mult;
			w = (M.m[2][0] - M.m[0][2]) * mult;
			z = (M.m[1][2] + M.m[2][1]) * mult;
			break;
		case 3:
			z = bigVal;
			x = (M.m[2][0] + M.m[0][2]) * mult;
			y = (M.m[1][2] + M.m[2][1]) * mult;
			w = (M.m[0][1] - M.m[1][0]) * mult;
			break;
		default:
			break;
		}
	}

	YQuat::YQuat(const YEuler& E) {
		float sin1, sin2, sin3, cos1, cos2, cos3;

		YMath::SinCos(&sin1, &cos1, YMath::DegToRad(E.yaw / 2));
		YMath::SinCos(&sin2, &cos2, YMath::DegToRad(E.pitch / 2));
		YMath::SinCos(&sin3, &cos3, YMath::DegToRad(E.roll / 2));

		w = cos1 * cos2 * cos3 - sin1 * sin2 * sin3;
		x = sin1 * sin2 * cos3 + cos1 * cos2 * sin3;
		y = sin1 * cos2 * cos3 + cos1 * sin2 * sin3;
		z = cos1 * sin2 * cos3 - sin1 * cos2 * sin3;
	}

	YQuat::YQuat(const YVec3& Axis, float AngleDeg) {
		float sin, cos;
		YMath::SinCos(&sin, &cos, YMath::DegToRad(AngleDeg/2));

		w = cos;
		x = sin * Axis.x;
		y = sin * Axis.y;
		z = sin * Axis.z;
	}

	inline bool YQuat::operator==(const YQuat& Q) const
	{
		return false;
	}

	YQuat YQuat::operator*(const YQuat& a) const
	{
		return YQuat (
			w * a.w - x * a.x - y * a.y - z * a.z,
			w * a.x + x * a.w + z * a.y - y * a.z,
			w * a.y + y * a.w + x * a.z - z * a.x,
			w * a.z + z * a.w + y * a.x - x * a.y
		);
	}
	YQuat YQuat::operator*=(const YQuat& a)
	{
		*this = *this * a;
		return *this;
	}
	void YQuat::conjugate() {
		x = -x;
		y = -y;
		z = -z;
		w = w;
	}
	void YQuat::setToIdentity() {
		w = 1.0f; x = y = z = 0.0f;
	}
	void YQuat::normalize() {
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
			setToIdentity();
		}
	}
	float YQuat::getRotationAngle() const {
		return SafeACos(w) * 2.0f;
	}
	YVec3 YQuat::getRotationAxis() const {
		float sinThetaOver2Sq = 1.0f - w * w;
		if (sinThetaOver2Sq <= 0.0f) {
			return YVec3(1.0f, 0.0f, 0.0f);
		}
		float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
		return YVec3(
			x * oneOverSinThetaOver2,
			y * oneOverSinThetaOver2,
			z * oneOverSinThetaOver2
		);
	}
	void YQuat::rotationX(float theta) {
		w = cos(theta * .5f);
		x = sin(theta * .5f);
		y = 0.0f;
		z = 0.0f;
	}
	void YQuat::rotationY(float theta) {
		w = cos(theta * .5f);
		x = 0.0f;
		y = sin(theta * .5f);
		z = 0.0f;
	}
	void YQuat::rotationZ(float theta) {
		w = cos(theta * .5f);
		x = 0.0f;
		y = 0.0f;
		z = sin(theta * .5f);
	}
	void YQuat::axisAngle(const YVec3& axis, float theta) {
		assert((fabs(magnitude(axis) - 1.0f) < .01f));
		float sinThetaOver2 = sin(theta * .5f);
		w = cos(theta * .5f);
		x = axis.x * sinThetaOver2;
		y = axis.y * sinThetaOver2;
		z = axis.z * sinThetaOver2;
	}
	void YQuat::setToRotateObjectToInertial(const YEuler& orientation) {
		float sinp, sinr, siny;
		float cosp, cosr, cosy;
		SinCos(&sinp, &cosp, orientation.pitch * 0.5f);
		SinCos(&sinr, &cosr, orientation.roll * 0.5f);
		SinCos(&siny, &cosy, orientation.yaw * 0.5f);
		w = cosy * cosp * cosr + siny * sinp * sinr;
		x = cosy * sinp * cosr + siny * cosp * sinr;
		y = -cosy * sinp * sinr + siny * cosp * cosr;
		z = -siny * sinp * cosr + cosy * cosp * sinr;
	}
	void YQuat::setToRotateInertialToObject(const YEuler& orientation) {
		float sinp, sinr, siny;
		float cosp, cosr, cosy;
		SinCos(&sinp, &cosp, orientation.pitch * 0.5f);
		SinCos(&sinr, &cosr, orientation.roll * 0.5f);
		SinCos(&siny, &cosy, orientation.yaw * 0.5f);
		w = cosy * cosp * cosr + siny * sinp * sinr;
		x = -cosy * sinp * cosr - siny * cosp * sinr;
		y = cosy * sinp * sinr - siny * cosp * cosr;
		z = siny * sinp * cosr - cosy * cosp * sinr;
	}
	bool YQuat::isUnit() const
	{
		return IsZero(1.0f - w * w - x * x - y * y - z * z);
	}
	float dotProduct(const YQuat& a, const YQuat& b)
	{
		return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	}
	YQuat crossProduct(const YQuat& p, const YQuat& q)
	{
		return YQuat();
	}
	YQuat slerp(const YQuat& q0, const YQuat& q1, float t)
	{
		if (t <= 0.0f) return q0;
		if (t >= 1.0f) return q1;
		float q1w = q1.w;
		float q1x = q1.x;
		float q1y = q1.y;
		float q1z = q1.z;
		float cosOmega = dotProduct(q0, q1);
		if (cosOmega < 0.0f) {
			q1w = -q1w;
			q1x = -q1x;
			q1y = -q1y;
			q1z = -q1z;
			cosOmega = -cosOmega;
		}
		assert(cosOmega < 1.1f);
		// Compute interpolation fraction, checking for quaternions
		// almost exactly the same
		float k0, k1;
		if (cosOmega > 0.9999f) {
			// Very close - just use linear interpolation,
			// which will protect againt a divide by zero
			k0 = -(t - 1.f);
			k1 = t;
		}
		else {
			// Compute the sin of the angle using the
			// trig identity sin^2(omega) + cos^2(omega) = 1
			float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
			// Compute the angle from its sin and cosine
			float omega = atan2(sinOmega, cosOmega);
			// Compute inverse of denominator, so we only have
			// to divide once
			float oneOverSinOmega = 1.0f / sinOmega;
			// Compute interpolation parameters
			k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
			k1 = sin(t * omega) * oneOverSinOmega;
		}
		return YQuat(
			k0 * q0.x + k1 * q1x,
			k0 * q0.y + k1 * q1y,
			k0 * q0.z + k1 * q1z,
			k0 * q0.w + k1 * q1w
		);
	}
	YQuat conjugate(const YQuat& q)
	{
		return YQuat(
			q.w,
			-q.x,
			-q.y,
			-q.z
		);
	}
	YQuat pow(const YQuat& q, float exponent)
	{
		if (fabs(q.w) > .9999f) {
			return q;
		}
		// Extract the half angle alpha (alpha = theta/2)
		float alpha = acos(q.w);
		// Compute new alpha value
		float newAlpha = alpha * exponent;
		// Compute new w value
		float mult = sin(newAlpha) / sin(alpha);
		return YQuat(
			cos(newAlpha),
			q.x * mult,
			q.y * mult,
			q.z * mult
		);
	}
}
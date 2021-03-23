#include "Quaternion.h"

namespace MathLib {
	const YQuat yIdentityQuaternion(1.f, 0.f, 0.f, 0.f);

	YQuat::YQuat():w(1), x(0), y(0), z(0) {}

	YQuat::YQuat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

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
		return safeACos(w) * 2.0f;
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
	void YQuat::setToRotateAboutX(float theta) {
		w = cos(theta * .5f);
		x = sin(theta * .5f);
		y = 0.0f;
		z = 0.0f;
	}
	void YQuat::setToRotateAboutY(float theta) {
		w = cos(theta * .5f);
		x = 0.0f;
		y = sin(theta * .5f);
		z = 0.0f;
	}
	void YQuat::setToRotateAboutZ(float theta) {
		w = cos(theta * .5f);
		x = 0.0f;
		y = 0.0f;
		z = sin(theta * .5f);
	}
	void YQuat::setToRotateAboutAxis(const YVec3& axis, float theta) {
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
		sinCos(&sinp, &cosp, orientation.pitch * 0.5f);
		sinCos(&sinr, &cosr, orientation.roll * 0.5f);
		sinCos(&siny, &cosy, orientation.yaw * 0.5f);
		w = cosy * cosp * cosr + siny * sinp * sinr;
		x = cosy * sinp * cosr + siny * cosp * sinr;
		y = -cosy * sinp * sinr + siny * cosp * cosr;
		z = -siny * sinp * cosr + cosy * cosp * sinr;
	}
	void YQuat::setToRotateInertialToObject(const YEuler& orientation) {
		float sinp, sinr, siny;
		float cosp, cosr, cosy;
		sinCos(&sinp, &cosp, orientation.pitch * 0.5f);
		sinCos(&sinr, &cosr, orientation.roll * 0.5f);
		sinCos(&siny, &cosy, orientation.yaw * 0.5f);
		w = cosy * cosp * cosr + siny * sinp * sinr;
		x = -cosy * sinp * cosr - siny * cosp * sinr;
		y = cosy * sinp * sinr - siny * cosp * cosr;
		z = siny * sinp * cosr - cosy * cosp * sinr;
	}
	bool YQuat::isUnit() const
	{
		return isZero(1.0f - w * w - x * x - y * y - z * z);
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
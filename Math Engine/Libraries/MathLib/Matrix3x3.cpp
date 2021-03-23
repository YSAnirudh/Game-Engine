#include "Matrix3x3.h"
//ONLY USED FOR ROTATION
namespace MathLib {
	//
	// Constructors
	//

	YMat3x3::YMat3x3() {
		m11 = 0.f; m12 = 0.f; m13 = 0.f;
		m21 = 0.f; m22 = 0.f; m23 = 0.f;
		m31 = 0.f; m32 = 0.f; m33 = 0.f;
	}

	YMat3x3::YMat3x3(const float& m11, const float& m12, const float& m13,
		const float& m21, const float& m22, const float& m23, 
		const float& m31, const float& m32, const float& m33)
		:m11(m11), m12(m12), m13(m13),
		m21(m21), m22(m22), m23(m23),
		m31(m31), m32(m32), m33(m33)
	{}

	YMat3x3::YMat3x3(const YMat3x3& a)
		:m11(a.m11), m12(a.m12), m13(a.m13),
		m21(a.m21), m22(a.m22), m23(a.m23),
		m31(a.m31), m32(a.m32), m33(a.m33)
	{}

	YMat3x3::YMat3x3(const YVec3 & a, const YVec3 & b, const YVec3 & c)
		: m11(a.x), m12(a.y), m13(a.z),
		m21(b.x), m22(b.y), m23(b.z),
		m31(c.x), m32(c.y), m33(c.z)
	{}



	inline YMat3x3& YMat3x3::operator=(const YMat3x3& a)
	{
		if (this == &a) return *this;

		return *this;
	}

	YMat3x3 YMat3x3::operator+(const YMat3x3& a) {
		return YMat3x3(
			m11 + a.m11, m12 + a.m12, m13 + a.m13,
			m21 + a.m21, m22 + a.m22, m23 + a.m23,
			m31 + a.m31, m32 + a.m32, m33 + a.m33
		);
	}

	YMat3x3 YMat3x3::operator+=(const YMat3x3& a) {
		return *this + a;
	}

	YMat3x3 YMat3x3::operator-(const YMat3x3& a) {
		return YMat3x3(
			m11 - a.m11, m12 - a.m12, m13 - a.m13,
			m21 - a.m21, m22 - a.m22, m23 - a.m23,
			m31 - a.m31, m32 - a.m32, m33 - a.m33
		);
	}

	YMat3x3 YMat3x3::operator-=(const YMat3x3& a) {
		return *this - a;
	}

	inline YMat3x3 YMat3x3::operator*(const YMat3x3& b) {
		return YMat3x3(
			m11 * b.m11 + m12 * b.m21 + m13 * b.m31,
			m11 * b.m12 + m12 * b.m22 + m13 * b.m32,
			m11 * b.m13 + m12 * b.m23 + m13 * b.m33,
			m21 * b.m11 + m22 * b.m21 + m23 * b.m31,
			m21 * b.m22 + m22 * b.m22 + m23 * b.m32,
			m21 * b.m23 + m22 * b.m23 + m23 * b.m33,
			m31 * b.m11 + m32 * b.m21 + m33 * b.m31,
			m31 * b.m12 + m32 * b.m22 + m33 * b.m32,
			m31 * b.m13 + m32 * b.m23 + m33 * b.m33
		);
	}

	inline YMat3x3 YMat3x3::operator*=(const YMat3x3& b) {
		return *this * b;
	}

	inline YMat3x3 YMat3x3::operator*(const float& mult) {
		return YMat3x3(
			mult * m11, mult * m12, mult * m13,
			mult * m21, mult * m22, mult * m23,
			mult * m31, mult * m32, mult * m33
		);
	}

	inline YMat3x3 YMat3x3::operator/(const float& mult)
	{
		if (fabs(mult) <= yEpsilon) return *this;
		float div = 1.0f / mult;

		return YMat3x3(
			div * m11, div * m12, div * m13,
			div * m21, div * m22, div * m23,
			div * m31, div * m32, div * m33
		);
	}

	inline YMat3x3 YMat3x3::operator/=(const float& div)
	{
		return *this / div;
	}

	YMat3x3 operator*(const YMat3x3& a, const float& mult) {
		return a * mult;
	}

	YMat3x3 operator*(const float& mult, const YMat3x3& a) {
		return a * mult;
	}


	//
	// Functions
	//
	void YMat3x3::transpose() {
		float t12 = m12, 
			t21 = m21, t31 = m31, 
			t13 = m13, t32 = m32, 
			t23 = m23;
		this->m11 = this->m11; m12 = t21; this->m13 = t31;
		this->m21 = t12; this->m22 = m22; this->m23 = t32;
		this->m31 = t13; this->m32 = t23; this->m33 = m33;
	}

	float YMat3x3::determinant() {
		return m11 * (m22 * m33 - m32 * m23) -
			m12 * (-m23 * m31 + m21 * m33) +
			m13 * (m21 * m32 - m22 * m31);
	}

	void YMat3x3::cofactor() {
		float t11 = (m22 * m33 - m32 * m23);
		float t12 = -(m21 * m33 - m31 * m23);
		float t13 = (m21 * m32 - m31 * m22);
		float t21 = -(m12 * m33 - m32 * m13);
		float t22 = (m11 * m33 - m31 * m13);
		float t23 = -(m11 * m32 - m31 * m12);
		float t31 = (m12 * m23 - m22 * m13);
		float t32 = -(m11 * m23 - m21 * m13);
		float t33 = (m11 * m22 - m21 * m12);

		m11 = t11;
		m12 = t12;
		m13 = t13;
		m21 = t21;
		m22 = t22;
		m23 = t23;
		m31 = t31;
		m32 = t32;
		m33 = t33;
	}

	void YMat3x3::adjoint() {
		cofactor();
		transpose();
	}

	void YMat3x3::inverse() {
		float det = determinant();
		if (fabs(det) <= yEpsilon) {
			return;
		}
		
		adjoint();
		*this /= det;
	}
	
	void YMat3x3::setToIdentity() {
		this->m11 = 1.f; this->m12 = 0.f; this->m13 = 0.f;
		this->m21 = 0.f; this->m22 = 1.f; this->m23 = 0.f;
		this->m31 = 0.f; this->m32 = 0.f; this->m33 = 1.f;
	}
	void YMat3x3::setup(const YEuler& orien) {
		float sinr, cosr, sinp, cosp, siny, cosy;
		sinCos(&sinr, &cosr, orien.roll);
		sinCos(&sinp, &cosp, orien.pitch);
		sinCos(&siny, &cosy, orien.yaw);

		m11 = cosy * cosr + siny * sinp * sinr;
		m12 = -cosy * sinr + siny * sinp * cosr;
		m13 = siny * cosp;
		m21 = sinr * cosp;
		m22 = cosr * cosp;
		m23 = -sinp;
		m31 = -siny * cosr + cosy * sinp * sinr;
		m32 = sinr * siny + cosy * sinp * cosr;
		m33 = cosy * cosp;
	}
	void YMat3x3::fromInertialToObjectQuaternion(const YQuat& quat) {
		m11 = 1.0f - 2.0f * (quat.y * quat.y + quat.z * quat.z);
		m12 = 2.0f * (quat.x * quat.y + quat.w * quat.z);
		m13 = 2.0f * (quat.x * quat.z - quat.w * quat.y);
		m21 = 2.0f * (quat.x * quat.y - quat.w * quat.z);
		m22 = 1.0f - 2.0f * (quat.x * quat.x + quat.z * quat.z);
		m23 = 2.0f * (quat.y * quat.z + quat.w * quat.x);
		m31 = 2.0f * (quat.x * quat.z + quat.w * quat.y);
		m32 = 2.0f * (quat.y * quat.z - quat.w * quat.x);
		m33 = 1.0f - 2.0f * (quat.x * quat.x + quat.y * quat.y);
	}
	void YMat3x3::fromObjectToInertialQuaternion(const YQuat& q) {
		m11 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		m12 = 2.0f * (q.x * q.y - q.w * q.z);
		m13 = 2.0f * (q.x * q.z + q.w * q.y);
		m21 = 2.0f * (q.x * q.y + q.w * q.z);
		m22 = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		m23 = 2.0f * (q.y * q.z - q.w * q.x);
		m31 = 2.0f * (q.x * q.z - q.w * q.y);
		m32 = 2.0f * (q.y * q.z + q.w * q.x);
		m33 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
	}
	YVec3 YMat3x3::fromInertialToObject(const YVec3& v) {
		return YVec3 (
			m11 * v.x + m21 * v.y + m31 * v.z,
			m12 * v.x + m22 * v.y + m32 * v.z,
			m13 * v.x + m23 * v.y + m33 * v.z
		);
	}
	YVec3 YMat3x3::fromObjectToInertial(const YVec3& v) {
		return YVec3 (
			m11 * v.x + m12 * v.y + m13 * v.z,
			m21 * v.x + m22 * v.y + m23 * v.z,
			m31 * v.x + m32 * v.y + m33 * v.z
		);
	}
}
#include "Matrix4x3.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "EulerAngles.h"
#include <assert.h>
namespace YSAoo {
	YMat4x3::YMat4x3() {
		m11 = 0.f; m12 = 0.f; m13 = 0.f;
		m21 = 0.f; m22 = 0.f; m23 = 0.f;
		m31 = 0.f; m32 = 0.f; m33 = 0.f;
		tx = 0.f; ty = 0.f; tz = 0.f;
	}
	YMat4x3::YMat4x3(const YMat4x3& m) {
		m11 = m.m11; m12 = m.m21; m13 = m.m31;
		m21 = m.m12; m22 = m.m22; m23 = m.m32;
		m31 = m.m13; m32 = m.m23; m33 = m.m33;
		tx = m.tx; ty = m.ty; tz = m.tz;
	}
	YMat4x3::YMat4x3(const YVec3& top, const YVec3& middle, const YVec3& bottom, const YVec3& translation) {
		m11 = top.x; m12 = top.y; m13 = top.z;
		m21 = middle.x; m22 = middle.y; m23 = middle.z;
		m31 = bottom.x; m32 = bottom.y; m33 = bottom.z;
		tx = translation.x; ty = translation.y; tz = translation.z;
	}
	void YMat4x3::setToIdentity() {
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		tx = 0.0f; ty = 0.0f; tz = 1.0f;
	}
	void YMat4x3::zeroTranslation() {
		tx = 0.f; ty = 0.f; tz = 0.f;
	}
	void YMat4x3::setTranslation(const YVec3& d) {
		tx = d.x; ty = d.y; tz = d.z;
	}
	void YMat4x3::setupTranslation(const YVec3& d) {
		m11 = 1.f; m12 = 0.f; m13 = 0.f;
		m21 = 0.f; m22 = 1.f; m23 = 0.f;
		m31 = 0.f; m32 = 0.f; m33 = 1.f;
		tx = d.x; ty = d.y; tz = d.z;
	}
	void YMat4x3::setupLocalToParent(const YVec3& pos, const YEuler& orient) {
		float sinr, cosr, sinp, cosp, siny, cosy;
		SinCos(&sinr, &cosr, orient.roll);
		SinCos(&sinp, &cosp, orient.pitch);
		SinCos(&siny, &cosy, orient.yaw);

		m11 = cosy * cosr + siny * sinp * sinr;
		m12 = -cosy * sinr + siny * sinp * cosr;
		m13 = siny * cosp;
		m21 = sinr * cosp;
		m22 = cosr * cosp;
		m23 = -sinp;
		m31 = -siny * cosr + cosy * sinp * sinr;
		m32 = sinr * siny + cosy * sinp * cosr;
		m33 = cosy * cosp;
		tx = pos.x; ty = pos.y; tz = pos.z;
	}
	void YMat4x3::setupLocalToParent(const YVec3& pos, const YMat3x3& orient) {
		m11 = orient.m11; m12 = orient.m21; m13 = orient.m31;
		m21 = orient.m12; m22 = orient.m22; m23 = orient.m32;
		m31 = orient.m13; m32 = orient.m23; m33 = orient.m33;
		tx = pos.x; ty = pos.y; tz = pos.z;
	}
	void YMat4x3::setupParentToLocal(const YVec3& pos, const YEuler& orient) {
		float sinr, cosr, sinp, cosp, siny, cosy;
		SinCos(&sinr, &cosr, orient.roll);
		SinCos(&sinp, &cosp, orient.pitch);
		SinCos(&siny, &cosy, orient.yaw);

		m11 = cosy * cosr + siny * sinp * sinr;
		m12 = -cosy * sinr + siny * sinp * cosr;
		m13 = siny * cosp;
		m21 = sinr * cosp;
		m22 = cosr * cosp;
		m23 = -sinp;
		m31 = -siny * cosr + cosy * sinp * sinr;
		m32 = sinr * siny + cosy * sinp * cosr;
		m33 = cosy * cosp;
		tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
		ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
		tz = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
	}
	void YMat4x3::setupParentToLocal(const YVec3& pos, const YMat3x3& orient) {
		m11 = orient.m11; m12 = orient.m12; m13 = orient.m13;
		m21 = orient.m21; m22 = orient.m22; m23 = orient.m23;
		m31 = orient.m31; m32 = orient.m32; m33 = orient.m33;
		tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
		ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
		tz = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
	}
	void YMat4x3::setupRotate(int axis, float theta) {
		float s, c;
		SinCos(&s, &c, theta);
		// Check which axis they are rotating about
		switch (axis) {
		case 1: // Rotate about the x-axis
			m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
			m21 = 0.0f; m22 = c; m23 = s;
			m31 = 0.0f; m32 = -s; m33 = c;
			break;
		case 2: // Rotate about the y-axis
			m11 = c; m12 = 0.0f; m13 = -s;
			m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
			m31 = s; m32 = 0.0f; m33 = c;
			break;
		case 3: // Rotate about the z-axis
			m11 = c; m12 = s; m13 = 0.0f;
			m21 = -s; m22 = c; m23 = 0.0f;
			m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
			break;
		default:
			// bogus axis index
			assert(false);
		}
		// Reset the translation portion
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::setupRotate(const YVec3& axis, float theta) {
		assert(fabs(dotProduct(axis, axis) - 1.0f) < .01f);
		// Get sin and cosine of rotation angle
		float s, c;
		SinCos(&s, &c, theta);
		// Compute 1 - cos(theta) and some common subexpressions
		float a = 1.0f - c;
		float ax = a * axis.x;
		float ay = a * axis.y;
		float az = a * axis.z;
		m11 = ax * axis.x + c;
		m12 = ax * axis.y + axis.z * s;
		m13 = ax * axis.z - axis.y * s;
		m21 = ay * axis.x - axis.z * s;
		m22 = ay * axis.y + c;
		m23 = ay * axis.z + axis.x * s;
		m31 = az * axis.x + axis.y * s;
		m32 = az * axis.y - axis.x * s;
		m33 = az * axis.z + c;
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::fromQuaternion(const YQuat& q) {
		float ww = 2.0f * q.w;
		float xx = 2.0f * q.x;
		float yy = 2.0f * q.y;
		float zz = 2.0f * q.z;
		m11 = 1.0f - yy * q.y - zz * q.z;
		m12 = xx * q.y + ww * q.z;
		m13 = xx * q.z - ww * q.x;
		m21 = xx * q.y - ww * q.z;
		m22 = 1.0f - xx * q.x - zz * q.z;
		m23 = yy * q.z + ww * q.x;
		m31 = xx * q.z + ww * q.y;
		m32 = yy * q.z - ww * q.x;
		m33 = 1.0f - xx * q.x - yy * q.y;
		// Reset the translation portion
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::setupScale(const YVec3& s) {
		m11 = s.x; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = s.y; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = s.z;
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::setupScale(const YVec3& axis, float k) {
		assert(fabs(dotProduct(axis, axis) - 1.0f) < .01f);
		// Compute k-1 and some common subexpressions
		float a = k - 1.0f;
		float ax = a * axis.x;
		float ay = a * axis.y;
		float az = a * axis.z;
		m11 = ax * axis.x + 1.0f;
		m22 = ay * axis.y + 1.0f;
		m32 = az * axis.z + 1.0f;
		m12 = m21 = ax * axis.y;
		m13 = m31 = ax * axis.z;
		m23 = m32 = ay * axis.z;
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::setupShear(int axis, float s, float t) {
		switch (axis) {
		case 1: // Shear y and z using x
			m11 = 1.0f; m12 = s; m13 = t;
			m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
			m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
			break;
		case 2: // Shear x and z using y
			m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
			m21 = s; m22 = 1.0f; m23 = t;
			m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
			break;
		case 3: // Shear x and y using z
			m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
			m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
			m31 = s; m32 = t; m33 = 1.0f;
			break;
		default:
			// bogus axis index
			assert(false);
		}
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::setupProject(const YVec3& n) {
		assert(fabs(dotProduct(n, n) - 1.0f) < .01f);
		m11 = 1.0f - n.x * n.x;
		m22 = 1.0f - n.y * n.y;
		m33 = 1.0f - n.z * n.z;
		m12 = m21 = -n.x * n.y;
		m13 = m31 = -n.x * n.z;
		m23 = m32 = -n.y * n.z;
		tx = ty = tz = 0.0f;
	}
	void YMat4x3::setupReflect(int axis, float k) {
		switch (axis) {
		case 1: // Reflect about the plane x=k
			m11 = -1.0f; m12 = 0.0f; m13 = 0.0f;
			m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
			m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
			tx = 2.0f * k; ty = 0.0f; tz = 0.0f;
			break;
		case 2: // Reflect about the plane y=k
			m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
			m21 = 0.0f; m22 = -1.0f; m23 = 0.0f;
			m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
			tx = 0.0f; ty = 2.0f * k; tz = 0.0f;
			break;
		case 3: // Reflect about the plane z=k
			m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
			m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
			m31 = 0.0f; m32 = 0.0f; m33 = -1.0f;
			tx = 0.0f; ty = 0.0f; tz = 2.0f * k;
			break;
		default:
			// bogus axis index
			assert(false);
		}
	}
	void YMat4x3::setupReflect(const YVec3& n) {
		assert(fabs(dotProduct(n, n) - 1.0f) < .01f);
		float ax = -2.0f * n.x;
		float ay = -2.0f * n.y;
		float az = -2.0f * n.z;
		m11 = 1.0f + ax * n.x;
		m22 = 1.0f + ay * n.y;
		m32 = 1.0f + az * n.z;
		m12 = m21 = ax * n.y;
		m13 = m31 = ax * n.z;
		m23 = m32 = ay * n.z;
		tx = ty = tz = 0.0f;
	}
	YVec3 operator*(const YVec3& p, const YMat4x3& m)
	{
		return YVec3(
			p.x * m.m11 + p.y * m.m21 + p.z * m.m31 + m.tx,
			p.x * m.m12 + p.y * m.m22 + p.z * m.m32 + m.ty,
			p.x * m.m13 + p.y * m.m23 + p.z * m.m33 + m.tz
		);
	}
	YMat4x3 operator*(const YMat4x3& a, const YMat4x3& b) {
		return YMat4x3(
			YVec3(
				a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
				a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
				a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33
			),
			YVec3(
				a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
				a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
				a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33
			),
			YVec3(
				a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
				a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
				a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33
			),
			YVec3(
				a.tx * b.m11 + a.ty * b.m21 + a.tz * b.m31 + b.tx,
				a.tx * b.m12 + a.ty * b.m22 + a.tz * b.m32 + b.ty,
				a.tx * b.m13 + a.ty * b.m23 + a.tz * b.m33 + b.tz
			)
		);
	}
	YMat4x3& operator*=(YMat4x3& a, const YMat4x3& b) {
		a = a * b;
		return a;
	}
	float determinant(const YMat4x3& m) {
		return m.m11 * (m.m22 * m.m33 - m.m23 * m.m32)
			+ m.m12 * (m.m23 * m.m31 - m.m21 * m.m33)
			+ m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
	}
	YMat4x3 inverse(const YMat4x3& m) {
		float det = determinant(m);
		// If we're singular, then the determinant is zero and there's
		// no inverse
		assert(fabs(det) > 0.000001f);
		// Compute one over the determinant, so we divide once and
		// can *multiply* per element
		float oneOverDet = 1.0f / det;
		YMat4x3 r;
		r.m11 = (m.m22 * m.m33 - m.m23 * m.m32) * oneOverDet;
		r.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * oneOverDet;
		r.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * oneOverDet;
		r.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * oneOverDet;
		r.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * oneOverDet;
		r.m23 = (m.m13 * m.m21 - m.m11 * m.m23) * oneOverDet;
		r.m31 = (m.m21 * m.m32 - m.m22 * m.m31) * oneOverDet;
		r.m32 = (m.m12 * m.m31 - m.m11 * m.m32) * oneOverDet;
		r.m33 = (m.m11 * m.m22 - m.m12 * m.m21) * oneOverDet;
		r.tx = -(m.tx * r.m11 + m.ty * r.m21 + m.tz * r.m31);
		r.ty = -(m.tx * r.m12 + m.ty * r.m22 + m.tz * r.m32);
		r.tz = -(m.tx * r.m13 + m.ty * r.m23 + m.tz * r.m33);
		return r;
	}
	YVec3 getTranslation(const YMat4x3& m)
	{
		return YVec3(m.tx, m.ty, m.tz);
	}
	YVec3 getPositionFromParentToLocalMatrix(const YMat4x3& m)
	{
		return YVec3(
			-(m.tx * m.m11 + m.ty * m.m12 + m.tz * m.m13),
			-(m.tx * m.m21 + m.ty * m.m22 + m.tz * m.m23),
			-(m.tx * m.m31 + m.ty * m.m32 + m.tz * m.m33)
		);
	}
	YVec3 getPositionFromLocalToParentMatrix(const YMat4x3& m)
	{
		return YVec3(m.tx, m.ty, m.tz);
	}
}
#include "Matrix4x4.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector4D.h"
namespace MathLib {
	YMat4x4::YMat4x4()
	{
		m11 = m12 = m13 = m14 = 0.0f;
		m21 = m22 = m23 = m24 = 0.0f;
		m31 = m32 = m33 = m34 = 0.0f;
		m41 = m42 = m43 = m44 = 0.0f;
	}

    YMat4x4& YMat4x4::operator=(const YMat4x4& other)
    {
        // if same object
        if (this == &other)
            return *this;

        m11 = other.m11;
        m12 = other.m12;
        m13 = other.m13;
        m14 = other.m14;
        m21 = other.m21;
        m22 = other.m22;
        m23 = other.m23;
        m24 = other.m24;
        m31 = other.m31;
        m32 = other.m32;
        m33 = other.m33;
        m34 = other.m34;
        m41 = other.m41;
        m42 = other.m42;
        m43 = other.m43;
        m44 = other.m44;

        return *this;

    }

    bool YMat4x4::operator==(const YMat4x4& other) const
    {
        if (!AreEqual(m11, other.m11) || !AreEqual(m12, other.m12) || !AreEqual(m13, other.m13) || !AreEqual(m14, other.m14))
            return false;
        if (!AreEqual(m21, other.m21) || !AreEqual(m22, other.m22) || !AreEqual(m23, other.m23) || !AreEqual(m24, other.m24))
            return false;
        if (!AreEqual(m31, other.m31) || !AreEqual(m32, other.m32) || !AreEqual(m33, other.m33) || !AreEqual(m34, other.m34))
            return false;
        if (!AreEqual(m41, other.m41) || !AreEqual(m42, other.m42) || !AreEqual(m43, other.m43) || !AreEqual(m44, other.m44))
            return false;
        return true;
    }

    bool YMat4x4::operator!=(const YMat4x4& other) const
    {
        if (!AreEqual(m11, other.m11) || !AreEqual(m12, other.m12) || !AreEqual(m13, other.m13) || !AreEqual(m14, other.m14))
            return true;
        if (!AreEqual(m21, other.m21) || !AreEqual(m22, other.m22) || !AreEqual(m23, other.m23) || !AreEqual(m24, other.m24))
            return true;
        if (!AreEqual(m31, other.m31) || !AreEqual(m32, other.m32) || !AreEqual(m33, other.m33) || !AreEqual(m34, other.m34))
            return true;
        if (!AreEqual(m41, other.m41) || !AreEqual(m42, other.m42) || !AreEqual(m43, other.m43) || !AreEqual(m44, other.m44))
            return true;
        return false;
    }

    bool YMat4x4::zero() const
    {
        if (!IsZero(m11) || !IsZero(m12) || !IsZero(m13) || !IsZero(m14))
            return false;
        if (!IsZero(m21) || !IsZero(m22) || !IsZero(m23) || !IsZero(m24))
            return false;
        if (!IsZero(m31) || !IsZero(m32) || !IsZero(m33) || !IsZero(m34))
            return false;
        if (!IsZero(m41) || !IsZero(m42) || !IsZero(m43) || !IsZero(m44))
            return false;
        return true;

    }

    bool YMat4x4::isIdentity() const
    {
        return AreEqual(1.0f, m11)
            && AreEqual(1.0f, m22)
            && AreEqual(1.0f, m33)
            && AreEqual(1.0f, m44)
            && IsZero(m21)
            && IsZero(m31)
            && IsZero(m41)
            && IsZero(m12)
            && IsZero(m32)
            && IsZero(m42)
            && IsZero(m13)
            && IsZero(m23)
            && IsZero(m43)
            && IsZero(m14)
            && IsZero(m24)
            && IsZero(m34);

    }

    YMat4x4& YMat4x4::affineInverse()
    {
        YMat4x4 temp = *this;

        // compute upper left 3x3 matrix determinant
        float cofactor0 = temp.m22 * temp.m33 - temp.m32 * temp.m23;
        float cofactor4 = temp.m31 * temp.m23 - temp.m21 * temp.m33;
        float cofactor8 = temp.m21 * temp.m32 - temp.m31 * temp.m22;
        float det = temp.m11 * cofactor0 + temp.m12 * cofactor4 + temp.m13 * cofactor8;
        if (IsZero(det))
        {
            assert(false);
            return *this;
        }

        // create adjunct matrix and multiply by 1/det to get upper 3x3
        float invDet = 1.0f / det;
        m11 = invDet * cofactor0;
        m21 = invDet * cofactor4;
        m31 = invDet * cofactor8;

        m12 = invDet * (temp.m32 * temp.m13 - temp.m12 * temp.m33);
        m22 = invDet * (temp.m11 * temp.m33 - temp.m31 * temp.m13);
        m33 = invDet * (temp.m31 * temp.m12 - temp.m11 * temp.m32);

        m13 = invDet * (temp.m12 * temp.m23 - temp.m22 * temp.m13);
        m23 = invDet * (temp.m21 * temp.m13 - temp.m11 * temp.m23);
        m33 = invDet * (temp.m11 * temp.m22 - temp.m21 * temp.m12);

        // multiply -translation by inverted 3x3 to get its inverse

        m14 = -m11 * temp.m14 - m12 * temp.m24 - m13 * temp.m34;
        m24 = -m21 * temp.m14 - m22 * temp.m24 - m23 * temp.m34;
        m34 = -m31 * temp.m14 - m32 * temp.m24 - m33 * temp.m34;

        return *this;

    }

    YMat4x4& YMat4x4::transpose()
    {
        float temp = m21;
        m21 = m12;
        m12 = temp;

        temp = m31;
        m31 = m13;
        m13 = temp;

        temp = m41;
        m41 = m14;
        m14 = temp;

        temp = m32;
        m32 = m23;
        m23 = temp;

        temp = m42;
        m42 = m24;
        m24 = temp;

        temp = m43;
        m43 = m34;
        m34 = temp;

        return *this;

    }

    YMat4x4& YMat4x4::translation(const YVec3& xlate)
    {
        m11 = 1.0f;
        m21 = 0.0f;
        m31 = 0.0f;
        m41 = 0.0f;
        m12 = 0.0f;
        m22 = 1.0f;
        m32 = 0.0f;
        m42 = 0.0f;
        m13 = 0.0f;
        m23 = 0.0f;
        m33 = 1.0f;
        m43 = 0.0f;
        m14 = xlate.x;
        m24 = xlate.y;
        m34 = xlate.z;
        m44 = 1.0f;

        return *this;

    }

    YMat4x4& YMat4x4::rotation(const YQuat& rotate)
    {
        assert(rotate.isUnit());

        float xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

        xs = rotate.x + rotate.x;
        ys = rotate.y + rotate.y;
        zs = rotate.z + rotate.z;
        wx = rotate.w * xs;
        wy = rotate.w * ys;
        wz = rotate.w * zs;
        xx = rotate.x * xs;
        xy = rotate.x * ys;
        xz = rotate.x * zs;
        yy = rotate.y * ys;
        yz = rotate.y * zs;
        zz = rotate.z * zs;

        m11 = 1.0f - (yy + zz);
        m12 = xy - wz;
        m13 = xz + wy;
        m14 = 0.0f;

        m21 = xy + wz;
        m22 = 1.0f - (xx + zz);
        m23 = yz - wx;
        m24 = 0.0f;

        m31 = xz - wy;
        m32 = yz + wx;
        m33 = 1.0f - (xx + yy);
        m34 = 0.0f;

        m41 = 0.0f;
        m42 = 0.0f;
        m43 = 0.0f;
        m44 = 1.0f;

        return *this;

    }

    YMat4x4& YMat4x4::rotation(const YMat3x3& other)
    {
        m11 = other.m11;
        m21 = other.m21;
        m31 = other.m31;
        m41 = 0;
        m12 = other.m12;
        m22 = other.m22;
        m32 = other.m32;
        m42 = 0;
        m13 = other.m13;
        m23 = other.m23;
        m33 = other.m33;
        m43 = 0;
        m14 = 0;
        m24 = 0;
        m34 = 0;
        m44 = 1;

        return *this;

    }

    YMat4x4& YMat4x4::rotation(float zRotation, float yRotation, float xRotation)
    {
        // This is an "unrolled" contatenation of rotation matrices X Y & Z
        float Cx, Sx;
        SinCos(&Sx, &Cx, xRotation);

        float Cy, Sy;
        SinCos(&Sy, &Cy, yRotation);

        float Cz, Sz;
        SinCos(&Sz, &Cz, zRotation);

        m11 = (Cy * Cz);
        m12 = -(Cy * Sz);
        m13 = Sy;
        m14 = 0.0f;

        m21 = (Sx * Sy * Cz) + (Cx * Sz);
        m22 = -(Sx * Sy * Sz) + (Cx * Cz);
        m23 = -(Sx * Cy);
        m24 = 0.0f;

        m31 = -(Cx * Sy * Cz) + (Sx * Sz);
        m32 = (Cx * Sy * Sz) + (Sx * Cz);
        m33 = (Cx * Cy);
        m34 = 0.0f;

        m41 = 0.0f;
        m42 = 0.0f;
        m43 = 0.0f;
        m44 = 1.0f;

        return *this;

    }

    YMat4x4& YMat4x4::rotation(const YVec3& axis, float angle)
    {
        float c, s;
        SinCos(&s, &c, angle);
        float t = 1.0f - c;

        YVec3 nAxis = axis;
        nAxis.normalize();

        // intermediate values
        float tx = t * nAxis.x;  float ty = t * nAxis.y;  float tz = t * nAxis.z;
        float sx = s * nAxis.x;  float sy = s * nAxis.y;  float sz = s * nAxis.z;
        float txy = tx * nAxis.y; float tyz = ty * nAxis.z; float txz = tx * nAxis.z;

        // set matrix
        m11 = tx * nAxis.x + c;
        m12 = txy - sz;
        m13 = txz + sy;
        m14 = 0.0f;

        m21 = txy + sz;
        m22 = ty * nAxis.y + c;
        m23 = tyz - sx;
        m24 = 0.0f;

        m31 = txz - sy;
        m32 = tyz + sx;
        m33 = tz * nAxis.z + c;
        m34 = 0.0f;

        m41 = 0.0f;
        m42 = 0.0f;
        m43 = 0.0f;
        m44 = 1.0f;

        return *this;

    }  

    YMat4x4& YMat4x4::scaling(const YVec3& scaleFactors)
    {
        m11 = scaleFactors.x;
        m21 = 0.0f;
        m31 = 0.0f;
        m41 = 0.0f;
        m12 = 0.0f;
        m22 = scaleFactors.y;
        m32 = 0.0f;
        m42 = 0.0f;
        m13 = 0.0f;
        m23 = 0.0f;
        m33 = scaleFactors.z;
        m43 = 0.0f;
        m14 = 0.0f;
        m24 = 0.0f;
        m34 = 0.0f;
        m44 = 1.0f;

        return *this;

    }

    YMat4x4& YMat4x4::rotationX(float angle)
    {
        float sintheta, costheta;
        SinCos(&sintheta, &costheta, angle);

        m11 = 1.0f;
        m21 = 0.0f;
        m31 = 0.0f;
        m41 = 0.0f;
        m12 = 0.0f;
        m22 = costheta;
        m32 = sintheta;
        m42 = 0.0f;
        m13 = 0.0f;
        m23 = -sintheta;
        m33 = costheta;
        m43 = 0.0f;
        m14 = 0.0f;
        m24 = 0.0f;
        m34 = 0.0f;
        m44 = 1.0f;

        return *this;

    }

    YMat4x4& YMat4x4::rotationY(float angle)
    {
        float sintheta, costheta;
        SinCos(&sintheta, &costheta, angle);

        m11 = costheta;
        m21 = 0.0f;
        m31 = -sintheta;
        m41 = 0.0f;
        m12 = 0.0f;
        m22 = 1.0f;
        m32 = 0.0f;
        m42 = 0.0f;
        m13 = sintheta;
        m23 = 0.0f;
        m33 = costheta;
        m43 = 0.0f;
        m14 = 0.0f;
        m24 = 0.0f;
        m34 = 0.0f;
        m44 = 1.0f;

        return *this;

    }

    YMat4x4& YMat4x4::rotationZ(float angle)
    {
        float sintheta, costheta;
        SinCos(&sintheta, &costheta, angle);

        m11 = costheta;
        m21 = sintheta;
        m31 = 0.0f;
        m41 = 0.0f;
        m12 = -sintheta;
        m22 = costheta;
        m32 = 0.0f;
        m42 = 0.0f;
        m13 = 0.0f;
        m23 = 0.0f;
        m33 = 1.0f;
        m43 = 0.0f;
        m14 = 0.0f;
        m24 = 0.0f;
        m34 = 0.0f;
        m44 = 1.0f;

        return *this;

    }

    void YMat4x4::getFixedAngles(float& zRotation, float& yRotation, float& xRotation)
    {
        float Cx, Sx;
        float Cy, Sy;
        float Cz, Sz;

        Sy = m13;
        Cy = Sqrt(1.0f - Sy * Sy);
        // normal case
        if (!IsZero(Cy))
        {
            float factor = 1.0f / Cy;
            Sx = -m23 * factor;
            Cx = m33 * factor;
            Sz = -m12 * factor;
            Cz = m11 * factor;
        }
        // x and z axes aligned
        else
        {
            Sz = 0.0f;
            Cz = 1.0f;
            Sx = m32;
            Cx = m22;
        }

        zRotation = atan2f(Sz, Cz);
        yRotation = atan2f(Sy, Cy);
        xRotation = atan2f(Sx, Cx);

    }

    void YMat4x4::getAxisAngle(YVec3& axis, float& angle)
    {
        float trace = m11 + m22 + m33;
        float cosTheta = 0.5f * (trace - 1.0f);
        angle = acosf(cosTheta);

        // angle is zero, axis can be anything
        if (IsZero(angle))
        {
            axis = YVec3(1.0f, 0.0f, 0.0f);
        }
        // standard case
        else if (angle < yPi - yEpsilon)
        {
            axis.set(m32 - m23, m13 - m31, m21 - m12);
            axis.normalize();
        }
        // angle is 180 degrees
        else
        {
            unsigned int i = 0;
            if (m22 > m11)
                i = 1;
            if (m33 > (i,i))
                i = 2;
            unsigned int j = (i + 1) % 3;
            unsigned int k = (j + 1) % 3;
            float s = Sqrt((i, i) - (j, j) - (k, k) + 1.0f);
            axis[i] = 0.5f * s;
            float recip = 1.0f / s;
            axis[j] = ((i, j)) * recip;
            axis[k] = ((k, i)) * recip;
        }

    }

    YMat4x4 YMat4x4::operator+(const YMat4x4& other) const
    {
        YMat4x4 result;

        result.m11 = m11 + other.m11;
        result.m12 = m12 + other.m12;
        result.m13 = m13 + other.m13;
        result.m14 = m14 + other.m14;
        result.m21 = m21 + other.m21;
        result.m22 = m22 + other.m22;
        result.m23 = m23 + other.m23;
        result.m24 = m24 + other.m24;
        result.m31 = m31 + other.m31;
        result.m32 = m32 + other.m32;
        result.m33 = m33 + other.m33;
        result.m34 = m34 + other.m34;
        result.m41 = m41 + other.m41;
        result.m42 = m42 + other.m42;
        result.m43 = m43 + other.m43;
        result.m44 = m44 + other.m44;

        return result;

    }

    YMat4x4& YMat4x4::operator+=(const YMat4x4& other)
    {
        *this = *this + other;

        return *this;

    }

    YMat4x4 YMat4x4::operator-(const YMat4x4& other) const
    {
        YMat4x4 result;

        result.m11 = m11 - other.m11;
        result.m12 = m12 - other.m12;
        result.m13 = m13 - other.m13;
        result.m14 = m14 - other.m14;
        result.m21 = m21 - other.m21;
        result.m22 = m22 - other.m22;
        result.m23 = m23 - other.m23;
        result.m24 = m24 - other.m24;
        result.m31 = m31 - other.m31;
        result.m32 = m32 - other.m32;
        result.m33 = m33 - other.m33;
        result.m34 = m34 - other.m34;
        result.m41 = m41 - other.m41;
        result.m42 = m42 - other.m42;
        result.m43 = m43 - other.m43;
        result.m44 = m44 - other.m44;

        return result;

    }

    YMat4x4& YMat4x4::operator-=(const YMat4x4& other)
    {
        *this = *this - other;

        return *this;

    }

    YMat4x4 YMat4x4::operator-() const
    {
        YMat4x4 result;

        result.m11 = -m11;
        result.m12 = -m12;
        result.m13 = -m13;
        result.m14 = -m14;
        result.m21 = -m21;
        result.m22 = -m22;
        result.m23 = -m23;
        result.m24 = -m24;
        result.m31 = -m31;
        result.m32 = -m32;
        result.m33 = -m33;
        result.m34 = -m34;
        result.m41 = -m41;
        result.m42 = -m42;
        result.m43 = -m43;
        result.m44 = -m44;

        return result;

    }

    YMat4x4 YMat4x4::operator*(const YMat4x4& other) const
    {
        YMat4x4 result;

        result.m11 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31
            + m14 * other.m41;
        result.m21 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31
            + m24 * other.m41;
        result.m31 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31
            + m34 * other.m41;
        result.m41 = m41 * other.m11 + m42 * other.m21 + m43 * other.m31
            + m44 * other.m41;

        result.m12 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32
            + m14 * other.m42;
        result.m22 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32
            + m24 * other.m42;
        result.m32 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32
            + m34 * other.m42;
        result.m42 = m41 * other.m12 + m42 * other.m22 + m43 * other.m32
            + m44 * other.m42;

        result.m13 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33
            + m14 * other.m43;
        result.m23 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33
            + m24 * other.m43;
        result.m33 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33
            + m34 * other.m43;
        result.m43 = m41 * other.m13 + m42 * other.m23 + m43 * other.m33
            + m44 * other.m43;

        result.m14 = m11 * other.m14 + m12 * other.m24 + m13 * other.m34
            + m14 * other.m44;
        result.m24 = m21 * other.m14 + m22 * other.m24 + m23 * other.m34
            + m24 * other.m44;
        result.m34 = m31 * other.m14 + m32 * other.m24 + m33 * other.m34
            + m34 * other.m44;
        result.m44 = m41 * other.m14 + m42 * other.m24 + m43 * other.m34
            + m44 * other.m44;

        return result;

    }

    YMat4x4& YMat4x4::operator*=(const YMat4x4& other)
    {
        YMat4x4 result;

        result.m11 = m11 * other.m11 + m12 * other.m21 + m13 * other.m31
            + m14 * other.m41;
        result.m21 = m21 * other.m11 + m22 * other.m21 + m23 * other.m31
            + m24 * other.m41;
        result.m31 = m31 * other.m11 + m32 * other.m21 + m33 * other.m31
            + m34 * other.m41;
        result.m41 = m41 * other.m11 + m42 * other.m21 + m43 * other.m31
            + m44 * other.m41;

        result.m12 = m11 * other.m12 + m12 * other.m22 + m13 * other.m32
            + m14 * other.m42;
        result.m22 = m21 * other.m12 + m22 * other.m22 + m23 * other.m32
            + m24 * other.m42;
        result.m32 = m31 * other.m12 + m32 * other.m22 + m33 * other.m32
            + m34 * other.m42;
        result.m42 = m41 * other.m12 + m42 * other.m22 + m43 * other.m32
            + m44 * other.m42;

        result.m13 = m11 * other.m13 + m12 * other.m23 + m13 * other.m33
            + m14 * other.m43;
        result.m23 = m21 * other.m13 + m22 * other.m23 + m23 * other.m33
            + m24 * other.m43;
        result.m33 = m31 * other.m13 + m32 * other.m23 + m33 * other.m33
            + m34 * other.m43;
        result.m43 = m41 * other.m13 + m42 * other.m23 + m43 * other.m33
            + m44 * other.m43;

        result.m14 = m11 * other.m14 + m12 * other.m24 + m13 * other.m34
            + m14 * other.m44;
        result.m24 = m21 * other.m14 + m22 * other.m24 + m23 * other.m34
            + m24 * other.m44;
        result.m34 = m31 * other.m14 + m32 * other.m24 + m33 * other.m34
            + m34 * other.m44;
        result.m44 = m41 * other.m14 + m42 * other.m24 + m43 * other.m34
            + m44 * other.m44;

        m11 = result.m11;
        m12 = result.m12;
        m13 = result.m13;
        m14 = result.m14;
        m21 = result.m21;
        m22 = result.m22;
        m23 = result.m23;
        m24 = result.m24;
        m31 = result.m31;
        m32 = result.m32;
        m33 = result.m33;
        m34 = result.m34;
        m41 = result.m41;
        m42 = result.m42;
        m43 = result.m43;
        m44 = result.m44;

        return *this;

    }

    YVec4 YMat4x4::operator*(const YVec4& other) const
    {
        YVec4 result;

        result.x = m11 * other.x + m12 * other.y + m13 * other.z + m14 * other.w;
        result.y = m21 * other.x + m22 * other.y + m23 * other.z + m24 * other.w;
        result.z = m31 * other.x + m32 * other.y + m33 * other.z + m34 * other.w;
        result.w = m41 * other.x + m42 * other.y + m43 * other.z + m44 * other.w;

        return result;

    }

    YVec4 operator*(const YVec4& vector, const YMat4x4& matrix)
    {
        YVec4 result;

        result.x = matrix.m11 * vector.x + matrix.m21 * vector.y
            + matrix.m31 * vector.z + matrix.m41 * vector.w;
        result.y = matrix.m12 * vector.x + matrix.m22 * vector.y
            + matrix.m32 * vector.z + matrix.m42 * vector.w;
        result.z = matrix.m13 * vector.x + matrix.m23 * vector.y
            + matrix.m33 * vector.z + matrix.m43 * vector.w;
        result.w = matrix.m14 * vector.x + matrix.m24 * vector.y
            + matrix.m34 * vector.z + matrix.m44 * vector.w;

        return result;

    }

    YMat4x4& YMat4x4::operator*=(float scalar)
    {
        m11 *= scalar;
        m21 *= scalar;
        m31 *= scalar;
        m41 *= scalar;
        m12 *= scalar;
        m22 *= scalar;
        m32 *= scalar;
        m42 *= scalar;
        m13 *= scalar;
        m23 *= scalar;
        m33 *= scalar;
        m43 *= scalar;
        m14 *= scalar;
        m24 *= scalar;
        m34 *= scalar;
        m44 *= scalar;

        return *this;
    }

    YMat4x4 operator*(float scalar, const YMat4x4& matrix)
    {
        YMat4x4 result;
        result.m11 = matrix.m11 * scalar;
        result.m21 = matrix.m21 * scalar;
        result.m31 = matrix.m31 * scalar;
        result.m41 = matrix.m41 * scalar;
        result.m12 = matrix.m12 * scalar;
        result.m22 = matrix.m22 * scalar;
        result.m32 = matrix.m32 * scalar;
        result.m42 = matrix.m42 * scalar;
        result.m13 = matrix.m13 * scalar;
        result.m23 = matrix.m23 * scalar;
        result.m33 = matrix.m33 * scalar;
        result.m43 = matrix.m43 * scalar;
        result.m14 = matrix.m14 * scalar;
        result.m24 = matrix.m24 * scalar;
        result.m34 = matrix.m34 * scalar;
        result.m44 = matrix.m44 * scalar;

        return result;
    }

    YMat4x4 YMat4x4::operator*(float scalar) const
    {
        YMat4x4 result;
        result.m11 = m11 * scalar;
        result.m21 = m21 * scalar;
        result.m31 = m31 * scalar;
        result.m41 = m41 * scalar;
        result.m12 = m12 * scalar;
        result.m22 = m22 * scalar;
        result.m32 = m32 * scalar;
        result.m42 = m42 * scalar;
        result.m13 = m13 * scalar;
        result.m23 = m23 * scalar;
        result.m33 = m33 * scalar;
        result.m43 = m43 * scalar;
        result.m14 = m14 * scalar;
        result.m24 = m24 * scalar;
        result.m34 = m34 * scalar;
        result.m44 = m44 * scalar;

        return result;
    }

    YVec3 YMat4x4::transform(const YVec3& other) const
    {
        YVec3 result;

        result.x = m11 * other.x + m12 * other.y + m13 * other.z;
        result.y = m21 * other.x + m22 * other.y + m23 * other.z;
        result.z = m31 * other.x + m32 * other.y + m33 * other.z;

        return result;

    } 

    YVec3 YMat4x4::transformPoint(const YVec3& other) const
    {
        YVec3 result;

        result.x = m11 * other.x + m12 * other.y + m13 * other.z + m14;
        result.y = m21 * other.x + m22 * other.y + m23 * other.z + m24;
        result.z = m31 * other.x + m32 * other.y + m33 * other.z + m34;

        return result;

    }

    YMat4x4 transpose(const YMat4x4& mat)
    {
        YMat4x4 result;

        result.m11 = mat.m11;
        result.m21 = mat.m12;
        result.m31 = mat.m13;
        result.m41 = mat.m14;
        result.m12 = mat.m21;
        result.m22 = mat.m22;
        result.m32 = mat.m23;
        result.m42 = mat.m24;
        result.m13 = mat.m31;
        result.m23 = mat.m32;
        result.m33 = mat.m33;
        result.m43 = mat.m34;
        result.m14 = mat.m41;
        result.m24 = mat.m42;
        result.m34 = mat.m43;
        result.m44 = mat.m44;

        return result;

    }
    YMat4x4 affineInverse(const YMat4x4& mat)
    {
        YMat4x4 result;

        // compute upper left 3x3 matrix determinant
        float cofactor0 = mat.m22 * mat.m33 - mat.m32 * mat.m23;
        float cofactor4 = mat.m31 * mat.m23 - mat.m21 * mat.m33;
        float cofactor8 = mat.m21 * mat.m32 - mat.m31 * mat.m22;
        float det = mat.m11 * cofactor0 + mat.m12 * cofactor4 + mat.m13 * cofactor8;
        if (IsZero(det))
        {
            assert(false);
            return result;
        }

        // create adjunct matrix and multiply by 1/det to get upper 3x3
        float invDet = 1.0f / det;
        result.m11 = invDet * cofactor0;
        result.m21 = invDet * cofactor4;
        result.m31 = invDet * cofactor8;

        result.m12 = invDet * (mat.m32 * mat.m13 - mat.m12 * mat.m33);
        result.m22 = invDet * (mat.m11 * mat.m33 - mat.m31 * mat.m13);
        result.m33 = invDet * (mat.m31 * mat.m12 - mat.m11 * mat.m32);

        result.m13 = invDet * (mat.m12 * mat.m23 - mat.m22 * mat.m13);
        result.m23 = invDet * (mat.m21 * mat.m13 - mat.m11 * mat.m23);
        result.m33 = invDet * (mat.m11 * mat.m22 - mat.m21 * mat.m12);

        // multiply -translation by inverted 3x3 to get its inverse

        result.m14 = -result.m11 * mat.m14 - result.m12 * mat.m24 - result.m13 * mat.m34;
        result.m24 = -result.m21 * mat.m14 - result.m22 * mat.m24 - result.m23 * mat.m34;
        result.m34 = -result.m31 * mat.m14 - result.m32 * mat.m24 - result.m33 * mat.m34;

        return result;

    }
}
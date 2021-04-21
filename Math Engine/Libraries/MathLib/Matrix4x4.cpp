#include "Matrix4x4.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector4D.h"
#include "Plane.h"
#include "GenMath.h"
namespace MathLib {
    //
    // STATIC VARIABLE DECLARATIONS
    //



    //
    // CONSTRUCTORS START
    //
    inline YMat4x4::YMat4x4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = 0.0f;
            }
        }
    }

    inline YMat4x4::YMat4x4(const YVec4& InX, const YVec4& InY, const YVec4& InZ, const YVec4& InW) {
        m[0][j] = InX.x;
        m[0][j] = InX.y;
        m[0][j] = InX.z;
        m[0][j] = InX.w;
        m[1][j] = InY.x;
        m[1][j] = InY.y;
        m[1][j] = InY.z;
        m[1][j] = InY.w;
        m[2][j] = InZ.x;
        m[2][j] = InZ.y;
        m[2][j] = InZ.z;
        m[2][j] = InZ.w;
        m[3][j] = InW.x;
        m[3][j] = InW.y;
        m[3][j] = InW.z;
        m[3][j] = InW.w;
    }
    inline YMat4x4::YMat4x4(const YMat3x3& InMat3x3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = InMat3x3.m[i][j]
            }
        }
        for (int j = 0; j < 3; j++) {
            m[j][3] = 0.0f;
        }
        for (int j = 0; j < 3; j++) {
            m[3][j] = 0.0f;
        }
        m[3][3] = 1.0f;
    }
    //
    // CONSTRUCTORS END
    //

    // 
    // OPERATORS START
    //

    // Assignment -> Assigns the values other to this
    inline YMat4x4 YMat4x4::operator=(const YMat4x4& other) {
        // if same object
        if (this == &other)
            return *this;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = other.m[i][j];
            }
        }

        return *this;
    }

    //Equality -> Returns true if this and Other are equal
    inline bool YMat4x4::operator==(const YMat4x4& Other) const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!YMath::AreEqual(m[i][j], Other.m[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    // Inequality -> Returns true if this and Other are not equal
    inline bool YMat4x4::operator!=(const YMat4x4& Other) const
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!YMath::AreEqual(m[i][j], Other.m[i][j])) {
                    return true;
                }
            }
        }
        return false;
    }

    // this + Other(YMat4x4) -> Adds this to Other
    inline YMat4x4 YMat4x4::operator+(const YMat4x4& Other) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = m[i][j] + Other.m[i][j];
            }
        }

        return result;

    }

    // this += Other(YMat4x4) -> Adds this to Other and stores in this
    inline YMat4x4 YMat4x4::operator+=(const YMat4x4& Other) {
        return (*this) + Other;
    }

    // Negation -> Makes the values in the matrix of the opposite sign (+ -> -, - -> +)
    inline YMat4x4 YMat4x4::operator-() const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = -m[i][j];
            }
        }

        return result;
    }

    // this - Other(YMat4x4) -> Subtracts Other from this
    inline YMat4x4 YMat4x4::operator-(const YMat4x4& Other) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = m[i][j] - Other.m[i][j];
            }
        }

        return result;

    }

    // this -= Other(YMat4x4) -> Subtracts Other from this and stores in this
    inline YMat4x4 YMat4x4::operator-=(const YMat4x4& Other) {
        return (*this) - Other;
    }

    // this * Other(YMat4x4) -> Matrix Multiplication (this * Other)
    inline YMat4x4 YMat4x4::operator*(const YMat4x4& Other) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] = m[i][k] * Other.m[k][j];
                }
            }
        }

        return result;
    }

    // this * Other(YMat4x4) -> Matrix Multiplication (this * Other) and stores in this
    inline YMat4x4 YMat4x4::operator*=(const YMat4x4& Other) {
        return (*this) * Other;
    }

    // freind for Matrix * Scalar
    inline YMat4x4 operator*(float Scalar, const YMat4x4& Matrix) {
        return Matrix * Scalar;
    }

    // this * Scalar -> Matrix * Scalar multiplication (Component wise not scaling)
    inline YMat4x4 YMat4x4::operator*(float Scalar) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = m[i][j] * Scalar;
            }
        }

        return result;
    }

    // this * Scalar -> Matrix * Scalar multiplication (Component wise not scaling) stores in this
    inline YMat4x4 YMat4x4::operator*=(float Scalar) {
        return *this * Scalar;
    }

    // Matrix accessor
    inline float& YMat4x4::operator()(unsigned int i, unsigned int j) {
        return m[i][j];
    }

    // Matrix accessor
    inline float YMat4x4::operator()(unsigned int i, unsigned int j) const {
        return m[i][j];
    }

    // Returns Row Vector = Matrix * YVec4 (Matrix * Row Vector)
    inline YVec4 YMat4x4::operator*(const YVec4& Other) const {
        YVec4 result;

        for (int j = 0; j < 4; j++) {
            result.x += m[0][j] * Other.x;
        }
        for (int j = 0; j < 4; j++) {
            result.y += m[1][j] * Other.y;
        }
        for (int j = 0; j < 4; j++) {
            result.z = m[2][j] * Other.z;
        }
        for (int j = 0; j < 4; j++) {
            result.w = m[3][j] * Other.w;
        }

        return result;
    }

    // Returns Column Vector = YVec4 * Matrix (Column Vector * Matrix)
    inline YVec4 operator*(const YVec4& Other, const YMat4x4& Matrix) {
        YVec4 result;

        for (int j = 0; j < 4; j++) {
            result.x += Matrix.m[j][0] * Other.x;
        }
        for (int j = 0; j < 4; j++) {
            result.y += Matrix.m[j][1] * Other.y;
        }
        for (int j = 0; j < 4; j++) {
            result.z = Matrix.m[j][2] * Other.z;
        }
        for (int j = 0; j < 4; j++) {
            result.w = Matrix.m[j][3] * Other.w;
        }

        return result;
    }

    // Returns the determinant of the cofactor matrix for index i, j
    inline float YMat4x4::GetCofactor(int IndexI, int IndexJ) const {
        YMat3x3 temp;
        int i3 = 0, j3 = 0;
        for (int i = 0; i < 4; i++) {
            if (i == IndexI) {
                continue;
            }
            j3 = 0;
            for (int j = 0; j < 4; j++) {
                if (j == IndexJ) {
                    continue;
                }
                else {
                    temp.m[i3][j3] = m[i][j];
                }
                j3++;
            }
            i3++;
        }
        return temp.Determinant();
    }

    inline bool YMat4x4::IsZero() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!YMath::IsZero(m[i][j])) {
                    return false;
                }
            }
        }
        return true;

    }

    bool YMat4x4::IsIdentity() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    if (!YMath::IsZero(m[i][j] - 1.0f)) {
                        return false;
                    }
                }
                else {
                    if (!YMath::IsZero(m[i][j])) {
                        return false;
                    }
                }
            }
        }
        return true;

    }

    inline float YMat4x4::Determinant() const {
        float det = 0.0f;
        det += m[0][0] * YMat3x3(YVec3(m[1][1], m[1][2], m[1][3]), YVec3(m[2][1], m[2][2], m[2][3]), YVec3(m[3][1], m[3][2], m[3][3]));
        det -= m[0][0] * YMat3x3(YVec3(m[1][0], m[1][2], m[1][3]), YVec3(m[2][0], m[2][2], m[2][3]), YVec3(m[3][0], m[3][2], m[3][3]));
        det += m[0][0] * YMat3x3(YVec3(m[1][0], m[1][1], m[1][3]), YVec3(m[2][0], m[2][1], m[2][3]), YVec3(m[3][0], m[3][1], m[3][3]));
        det -= m[0][0] * YMat3x3(YVec3(m[1][0], m[1][1], m[1][2]), YVec3(m[2][0], m[2][1], m[2][2]), YVec3(m[3][0], m[3][1], m[3][2]));
        return det;
    }

    inline bool YMat4x4::Equals(const YMat4x4& Other) const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!YMath::AreEqual(m[i][j], Other.m[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    inline YMat4x4 YMat4x4::Adjoint() const {
        YMat4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = GetCofactor(i, j);
            }
        }
        result.Transpose();
        return result;
    }

    inline YMat4x4 YMat4x4::Inverse() const {
        if (YMath::IsZero(Determinant())) {
            return YMat4x4();
        }
        return Adjoint() * (1/Determinant());
    }

    inline YMat4x4 YMat4x4::InverseFast() const
    {
        return YMat4x4();
    }

    inline YVec3 YMat4x4::InverseTransformPosition(const YVec3& V) const
    {
        return YVec3();
    }

    inline YVec3 YMat4x4::InverseTransformVector(const YVec3& V) const
    {
        return YVec3();
    }

    inline YVec3 YMat4x4::GetColumn(int i) const {
        return YVec3(m[0][i], m[1][i], m[2][i]);
    }

    inline YVec3 YMat4x4::GetRow(int i) const {
        return YVec3(m[i][0], m[i][1], m[i][2]);
    }

    inline bool YMat4x4::GetFrustumBottomPlane(YPlane& OUT OutPlane) const
    {
        return false;
    }

    inline bool YMat4x4::GetFrustumTopPlane(YPlane& OUT OutPlane) const
    {
        return false;
    }

    inline bool YMat4x4::GetFrustumRightPlane(YPlane& OUT OutPlane) const
    {
        return false;
    }

    inline bool YMat4x4::GetFrustumLeftPlane(YPlane& OUT OutPlane) const
    {
        return false;
    }

    inline bool YMat4x4::GetFrustumNearPlane(YPlane& OUT OutPlane) const
    {
        return false;
    }

    inline bool YMat4x4::GetFrustumFarPlane(YPlane& OUT OutPlane) const
    {
        return false;
    }

    inline YMat4x4 YMat4x4::GetMatrixWithoutScale(float Tolerance) const
    {
        return YMat4x4();
    }

    inline YVec3 YMat4x4::GetOrigin() const
    {
        return YVec3();
    }

    inline float YMat4x4::GetMaximumAxisScale() const {
        float magA = YVec3(m[0][0], m[0][1], m[0][2]).Magnitude();
        float magB = YVec3(m[1][0], m[1][1], m[1][2]).Magnitude();
        float magC = YVec3(m[2][0], m[2][1], m[2][2]).Magnitude();

        return YMath::Max(YMath::Max(magA, magC), magB);
    }

    inline void YMat4x4::GetScaledAxes(YVec3& OUT X, YVec3& OUT Y, YVec3& OUT Z) const {
        X = YVec3(m[0][0], m[0][1], m[0][2]);
        Y = YVec3(m[1][0], m[1][1], m[1][2]);
        Z = YVec3(m[2][0], m[2][1], m[2][2]);
    }

    inline YVec3 YMat4x4::GetScaledVector() const {
        return YVec3(
            YVec3(m[0][0], m[0][1], m[0][2]).Magnitude(),
            YVec3(m[1][0], m[1][1], m[1][2]).Magnitude(),
            YVec3(m[2][0], m[2][1], m[2][2]).Magnitude()
        );
    }

    inline void YMat4x4::SetColumn(int i, YVec3 Value) {
        m[0][i] = Value.x;
        m[1][i] = Value.y;
        m[2][i] = Value.z;
    }

    inline void YMat4x4::SetRow(int i, YVec3 Value) {
        m[0][i] = Value.x;
        m[1][i] = Value.y;
        m[2][i] = Value.z;
    }

    inline bool YMat4x4::IsRotationMatrix() const {
        for (int i = 0; i < 3; i++) {
            if (!YMath::AreEqual(1.0f, YVec3(m[i][0], m[i][1], m[i][2]).Magnitude())) {
                return false;
            }
        }
        return true;
    }

    inline void YMat4x4::Transpose() {
        YMat4x4 helper;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                helper.m[j][i] = m[i][j];
            }
        }
        *this = helper;
    }

    inline void YMat4x4::RemoveScaling(float Tolerance)
    {
    }

    inline YMat4x4 YMat4x4::RemoveTranslation(float Tolerance) const
    {
        return YMat4x4();
    }

    inline YEuler YMat4x4::Rotation() const {
        assert(IsRotationMatrix());

        return YEuler();
    }

    inline void YMat4x4::SetupRotation(const YMat3x3& Matrix) {
        *this = YMat4x4(Matrix);
    }

    inline void YMat4x4::SetupRotation(const YQuat& Rotate) {
        float x = Rotate.x;
        float y = Rotate.y;
        float z = Rotate.z;
        float w = Rotate.w;
        m[0][0] = 2 * (w * w + x * x) - 1;
        m[0][1] = 2 * (x * y - w * z);
        m[0][2] = 2 * (x * z + w * y);
        m[1][0] = 2 * (x * y + w * z);
        m[1][1] = 2 * (w * w + y * y) - 1;
        m[1][2] = 2 * (y * z - w * x);
        m[2][0] = 2 * (x * z - w * y);
        m[2][1] = 2 * (y * z + w * x);
        m[2][2] = 2 * (w * w + z * z) - 1;
    }



    inline void YMat4x4::SetupRotation(float xRotation, float yRotation, float zRotation) {
        YMat3x3 Rx = YMat3x3(
            YVec3(1.0f, 0.0f, 0.0f),
            YVec3(0.0f, YMath::Cos(xRotation), -YMath::Sin(xRotation)),
            YVec3(0.0f, YMath::Sin(xRotation), YMath::Cos(xRotation))
        );
        YMat3x3 Ry = YMat3x3(
            YVec3(YMath::Cos(yRotation), 0.0f, YMath::Sin(yRotation)),
            YVec3(0.0f, 1.0f, 0.0f),
            YVec3(-YMath::Sin(yRotation), 0.0f, YMath::Cos(yRotation))
        );
        YMat3x3 Rz = YMat3x3(
            YVec3(YMath::Cos(zRotation), -YMath::Sin(zRotation), 0.0f),
            YVec3(YMath::Sin(zRotation), YMath::Cos(zRotation), 0.0f),
            YVec3(0.0f, 0.0f, 1.0f)
        );
        YMat3x3 RotMat = Rx * Ry * Rz;
        *this = YMat4x4(RotMat);
    }

    inline void YMat4x4::SetupRotation(const YVec3& axis, float angle) {
        return YMat4x4();
    }

    inline void YMat4x4::SetupRotation(const YEuler& Euler) {
        YMat3x3 Rx = YMat3x3(
            YVec3(1.0f, 0.0f, 0.0f),
            YVec3(0.0f, YMath::Cos(Euler.pitch), -YMath::Sin(Euler.pitch)),
            YVec3(0.0f, YMath::Sin(Euler.pitch), YMath::Cos(Euler.pitch))
        );
        YMat3x3 Ry = YMat3x3(
            YVec3(YMath::Cos(Euler.yaw), 0.0f, YMath::Sin(Euler.yaw)),
            YVec3(0.0f, 1.0f, 0.0f),
            YVec3(-YMath::Sin(Euler.yaw), 0.0f, YMath::Cos(Euler.yaw))
        );
        YMat3x3 Rz = YMat3x3(
            YVec3(YMath::Cos(Euler.roll), -YMath::Sin(Euler.roll), 0.0f),
            YVec3(YMath::Sin(Euler.roll), YMath::Cos(Euler.roll), 0.0f),
            YVec3(0.0f, 0.0f, 1.0f)
        );
        YMat3x3 RotMat = Rx * Ry * Rz;
        *this = YMat4x4(RotMat);
    }

    inline void YMat4x4::SetupRotationX(float xAngle) {
        YMat3x3 Rx = YMat3x3(
            YVec3(1.0f, 0.0f, 0.0f),
            YVec3(0.0f, YMath::Cos(xAngle), -YMath::Sin(xAngle)),
            YVec3(0.0f, YMath::Sin(xAngle), YMath::Cos(xAngle))
        );
        *this = YMat4x4(Rx);
    }

    inline void YMat4x4::SetupRotationY(float yAngle) {
        YMat3x3 Ry = YMat3x3(
            YVec3(YMath::Cos(yAngle), 0.0f, YMath::Sin(yAngle)),
            YVec3(0.0f, 1.0f, 0.0f),
            YVec3(-YMath::Sin(yAngle), 0.0f, YMath::Cos(yAngle))
        );
        *this = YMat4x4(Ry);
    }

    inline void YMat4x4::SetupRotationZ(float zAngle) {
        YMat3x3 Rz = YMat3x3(
            YVec3(YMath::Cos(zAngle), -YMath::Sin(zAngle), 0.0f),
            YVec3(YMath::Sin(zAngle), YMath::Cos(zAngle), 0.0f),
            YVec3(0.0f, 0.0f, 1.0f)
        );
        *this = YMat4x4(Rz);
    }

    inline void YMat4x4::SetupScale(float Scale) {
        *this = YMat4x4(
            YVec4(Scale, 0.0f, 0.0f, 0.0f),
            YVec4(0.0f, Scale, 0.0f, 0.0f),
            YVec4(0.0f, 0.0f, Scale, 0.0f),
            YVec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    inline void YMat4x4::SetupScale(const YVec3& Scale) {
        *this = YMat4x4(
            YVec4(Scale.x, 0.0f, 0.0f, 0.0f),
            YVec4(0.0f, Scale.y, 0.0f, 0.0f),
            YVec4(0.0f, 0.0f, Scale.z, 0.0f),
            YVec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    inline void YMat4x4::SetupTranslation(const YVec3& xLate) {
        *this = YMat4x4(
            YVec4(1.0f, 0.0f, 0.0f, xLate.x),
            YVec4(0.0f, 1.0f, 0.0f, xLate.y),
            YVec4(0.0f, 0.0f, 1.0f, xLate.z),
            YVec4(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    inline void YMat4x4::ScaleTranslation(const YVec3& Scale3D) {
        m[0][3] *= Scale3D.x;
        m[1][3] *= Scale3D.y;
        m[2][3] *= Scale3D.z;
    }

    inline void YMat4x4::GetFixedAngles(float& zRotation, float& yRotation, float& xRotation)
    {
    }

    inline void YMat4x4::GetAxisAngle(YVec3& axis, float& angle)
    {
    }

    inline YQuat YMat4x4::Quaternion() const {

        return YQuat();
    }

    inline YVec4 YMat4x4::TransformVec4(const YVec4& V) const
    {
        return YVec4();
    }

    inline YVec4 YMat4x4::TransformPosition(const YVec3& V) const
    {
        return YVec4();
    }

    inline YVec4 YMat4x4::TransformVector(const YVec3& V) const
    {
        return YVec4();
    }

    inline YVec3 YMat4x4::Transform(const YVec3& point) const
    {
        return YVec3();
    }

    inline YMat4x4 YMat4x4::AffineInverse()
    {
        // TODO: insert return statement here
    }

    YMat4x4& YMat4x4::affineInverse() {
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
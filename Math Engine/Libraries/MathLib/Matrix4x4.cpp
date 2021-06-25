#pragma once
#include "Matrix4x4.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector4D.h"
#include "Plane.h"
#include "GenMath.h"
#include "Vector3D.h"
#include "Matrix3x3.h"
#include <climits>
namespace MathLib {
    //
    // STATIC VARIABLE DECLARATIONS
    //
    const YMat4x4 YMat4x4::Identity = YMat4x4(
        YVec4(1.0f, 0.0f, 0.0f, 0.0f),
        YVec4(0.0f, 1.0f, 0.0f, 0.0f),
        YVec4(0.0f, 0.0f, 1.0f, 0.0f),
        YVec4(0.0f, 0.0f, 0.0f, 1.0f)
    );

    //
    // CONSTRUCTORS START
    //
    YMat4x4::YMat4x4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = 0.0f;
            }
        }
    }

    YMat4x4::YMat4x4(const YVec4 &InX, const YVec4 &InY, const YVec4 &InZ, const YVec4 &InW) {
        m[0][0] = InX.x;
        m[0][1] = InX.y;
        m[0][2] = InX.z;
        m[0][3] = InX.w;
        m[1][0] = InY.x;
        m[1][1] = InY.y;
        m[1][2] = InY.z;
        m[1][3] = InY.w;
        m[2][0] = InZ.x;
        m[2][1] = InZ.y;
        m[2][2] = InZ.z;
        m[2][3] = InZ.w;
        m[3][0] = InW.x;
        m[3][1] = InW.y;
        m[3][2] = InW.z;
        m[3][3] = InW.w;
    }
    
    YMat4x4::YMat4x4(const YMat3x3 &InMat3x3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = InMat3x3.m[i][j];
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

    YMat4x4::YMat4x4(const YMat4x4 &InMat4x4) {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m[i][j] = InMat4x4.m[i][j];
            }
        }
    }
    //
    // CONSTRUCTORS END
    //

    //
    // OPERATORS START
    //

    // Assignment -> Assigns the values other to this
    YMat4x4 YMat4x4::operator=(const YMat4x4 &Other) {
        // if same object
        if (this == &Other)
            return *this;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = Other.m[i][j];
            }
        }
        return *this;
    }

    //Equality -> Returns true if this and Other are equal
    bool YMat4x4::operator==(const YMat4x4 &Other) const {
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
    bool YMat4x4::operator!=(const YMat4x4 &Other) const {
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
    YMat4x4 YMat4x4::operator+(const YMat4x4 &Other) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = m[i][j] + Other.m[i][j];
            }
        }

        return result;
    }

    // this += Other(YMat4x4) -> Adds this to Other and stores in this
    YMat4x4 YMat4x4::operator+=(const YMat4x4 &Other) {
        return (*this) = (*this) + Other;
    }

    // Negation -> Makes the values in the matrix of the opposite sign (+ -> -, - -> +)
    YMat4x4 YMat4x4::operator-() const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = -m[i][j];
            }
        }

        return result;
    }

    // this - Other(YMat4x4) -> Subtracts Other from this
    YMat4x4 YMat4x4::operator-(const YMat4x4 &Other) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = m[i][j] - Other.m[i][j];
            }
        }

        return result;
    }

    // this -= Other(YMat4x4) -> Subtracts Other from this and stores in this
    YMat4x4 YMat4x4::operator-=(const YMat4x4 &Other) {
        return (*this) = (*this) - Other;
    }

    // this * Other(YMat4x4) -> Matrix Multiplication (this * Other)
    YMat4x4 YMat4x4::operator*(const YMat4x4 &Other) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * Other.m[k][j];
                }
            }
        }

        return result;
    }

    // this * Other(YMat4x4) -> Matrix Multiplication (this * Other) and stores in this
    YMat4x4 YMat4x4::operator*=(const YMat4x4 &Other) {
        return (*this) = (*this) * Other;
    }

    // freind for Matrix * Scalar
    YMat4x4 operator*(float Scalar, const YMat4x4 &Matrix) {
        return Matrix * Scalar;
    }

    // this * Scalar -> Matrix * Scalar multiplication (Component wise not scaling)
    YMat4x4 YMat4x4::operator*(float Scalar) const {
        YMat4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = m[i][j] * Scalar;
            }
        }

        return result;
    }

    // this * Scalar -> Matrix * Scalar multiplication (Component wise not scaling) stores in this
    YMat4x4 YMat4x4::operator*=(float Scalar) {
        return (*this) = *this * Scalar;
    }

    // Matrix accessor
    float &YMat4x4::operator()(unsigned int i, unsigned int j) {
        return m[i][j];
    }

    // Matrix accessor
    float YMat4x4::operator()(unsigned int i, unsigned int j) const {
        return m[i][j];
    }

    // Returns Column Vector = Matrix * YVec4 (Matrix * Column Vector)
    YVec4 YMat4x4::operator*(const YVec4 &Vector) const {
        YVec4 result;
        result.x = m[0][0] * Vector.x + m[0][1] * Vector.y + m[0][2] * Vector.z + m[0][3] * Vector.w;
        result.y = m[1][0] * Vector.x + m[1][1] * Vector.y + m[1][2] * Vector.z + m[1][3] * Vector.w;
        result.z = m[2][0] * Vector.x + m[2][1] * Vector.y + m[2][2] * Vector.z + m[2][3] * Vector.w;
        result.w = m[3][0] * Vector.x + m[3][1] * Vector.y + m[3][2] * Vector.z + m[3][3] * Vector.w;
        
        return result;
    }

    // Returns Row Vector = YVec4 * Matrix (Row Vector * Matrix)
    YVec4 operator*(const YVec4 &Vector, const YMat4x4 &matrix) {
        YVec4 result;
        YMat4x4 Matrix = matrix.GetTranspose();
        for (int j = 0; j < 4; j++) {
            result.x += Matrix.m[j][0] * Vector.x;
        }
        for (int j = 0; j < 4; j++) {
            result.y += Matrix.m[j][1] * Vector.y;
        }
        for (int j = 0; j < 4; j++) {
            result.z += Matrix.m[j][2] * Vector.z;
        }
        for (int j = 0; j < 4; j++) {
            result.w += Matrix.m[j][3] * Vector.w;
        }

        return result;
    }

    // OSTREAM OPERATOR
    std::ostream& operator<<(std::ostream& out, const YMat4x4& matrix) {
        out << "Matrix 4x4 (Row Major):" << std::endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                out << matrix.m[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    //
    // OPERATORS END
    //

    //
    // FUNCTIONS START
    //

    // Returns the determinant of the cofactor matrix for index i, j
    float YMat4x4::GetCofactor(int IndexI, int IndexJ) const {
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

    // Returns true in every elemtn is zero in this
    bool YMat4x4::IsZero() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!YMath::IsZero(m[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    // Returns true if this is an identity 4x4 Matrix
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

    // Returns true if this is equal to Other
    bool YMat4x4::Equals(const YMat4x4 &Other) const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!YMath::AreEqual(m[i][j], Other.m[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    // Returns the transpose of this
    YMat4x4 YMat4x4::GetTranspose() const {
        YMat4x4 helper;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                helper.m[j][i] = m[i][j];
            }
        }
        return helper;
    }

    // Returns the determinant of this (4x4 Matrix)
    float YMat4x4::Determinant() const {
        float det = 0.0f;
        det += m[0][0] * GetCofactor(0, 0);
        det -= m[0][1] * GetCofactor(0, 1);
        det += m[0][2] * GetCofactor(0, 2);
        det -= m[0][3] * GetCofactor(0, 3);
        return det;
    }

    // Returns the adjoint matrix of this (4x4 Matrix)
    YMat4x4 YMat4x4::GetAdjoint() const {
        YMat4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = GetCofactor(i, j);
                if ((i + j) % 2 == 1) {
                    result.m[i][j] = -result.m[i][j];
                }
            }
        }
        result.Transpose();
        return result;
    }

    // Returns the inverse matrix of this (4x4 Matrix)
    YMat4x4 YMat4x4::GetInverse() const {
        if (YMath::IsZero(Determinant())) {
            return YMat4x4();
        }
        return GetAdjoint() * (1 / Determinant());
    }

    // MARK FOR REVIEW
    // Returns the inverse matrix of this (4x4 Matrix) faster
    YMat4x4 YMat4x4::GetInverseFast() const {
        return YMat4x4();
    }

    // Opposite transformations to normal transformations expected by this matrix
    // Reverses the transformations that this matrix might have performed
    // On YVec4
    YVec4 YMat4x4::InverseTransformVec4(const YVec4& V) const {
        YMat4x4 Rotation = YMat4x4(YMat3x3(*this)).GetInverse();
        YMat4x4 Translation;
        Translation.SetupTranslation(YVec3(this->m[0][3], this->m[1][3], this->m[2][3]));
        Translation = Translation.GetInverse();
        YMat4x4 Helper = Rotation * Translation;
        return YVec4(Helper.TransformVec4(V));
    }

    // Takes into account only translation part
    // Opposite translations to normal translations expected by this matrix
    // Reverses the translations that this matrix might have performed
    // On YVec3
    YVec3 YMat4x4::InverseTransformPosition(const YVec3 &V) const {
        YMat4x4 Translation;
        Translation.SetupTranslation(YVec3(this->m[0][3], this->m[1][3], this->m[2][3]));
        Translation = Translation.GetInverse();
        return YVec3(Translation.TransformPosition(V));
    }

    // Takes into account everything expect translation - rotation, scale etc.
    // Opposite rotations to normal rotations expected by this matrix
    // Reverses the rotations that this matrix might have performed
    // On YVec3
    YVec3 YMat4x4::InverseTransformVector(const YVec3 &V) const {
        YMat4x4 Rotation = YMat4x4(YMat3x3(*this)).GetInverse();
        return YVec3(Rotation.TransformVector(V));
    }

    // Opposite transformations to normal transformations expected by this matrix
    // Reverses the transformations that this matrix might have performed
    // On YVec3
    YVec3 YMat4x4::InverseTransformVec3(const YVec3& V) const {
        YMat4x4 Rotation = YMat4x4(YMat3x3(*this)).GetInverse();
        YMat4x4 Translation;
        Translation.SetupTranslation(YVec3(this->m[0][3], this->m[1][3], this->m[2][3]));
        Translation = Translation.GetInverse();
        YMat4x4 Helper = Rotation * Translation;
        return YVec3(Helper.TransformVec3(V));
    }

    // Returns the matrix with the translation part removed from this matrix
    YMat4x4 YMat4x4::RemoveTranslation(float Tolerance) const {
        return YMat4x4(YMat3x3(*this));
    }

    // Returns the Euler angle found by using this
    YEuler YMat4x4::Rotation() const {
        assert(IsRotationMatrix());
        float pitch = 0.0f; //x rot
        float yaw = 0.0f;   //y rot
        float roll = 0.0f;  //z rot
        float sinPitch = -m[2][0];

        /*if (YMath::AreEqual(1.0f, sinPitch)) {
            pitch = yPiBy2;
            roll = 0.0f;
            yaw = YMath::ATan2(m[2][1], m[2][2]);
        }
        else if (YMath::AreEqual(-1.0f, sinPitch)) {
            pitch = -yPiBy2;
            roll = 0.0f;
            yaw = YMath::ATan2(m[2][1], m[2][2]);
        }
        else {
            pitch = YMath::ASin(sinPitch);
            roll = YMath::ATan2(m[1][0], m[0][0]);
            yaw = YMath::ATan2(m[2][1], m[2][2]);
        }*/

        // SHOULD AVOID GIMBAL LOCK

        pitch = YMath::ATan2(-m[2][0], YMath::Sqrt(m[2][1]*m[2][1] + m[2][2]*m[2][2]));
        roll = YMath::ATan2(m[1][0], m[0][0]);
        yaw = YMath::ATan2(m[2][1], m[2][2]);
        return YEuler(
            YMath::RadToDeg(roll), 
            YMath::RadToDeg(pitch),
            YMath::RadToDeg(yaw));
    }

    // Returns true if this is a Rotation matrix
    // Make it Inverse fast after implementation !!!!!!!!!!!
    bool YMat4x4::IsRotationMatrix() const {
        if (YMat3x3(*this).Inverse() == YMat3x3(*this).GetTranspose()) {
            return true;
        }
        return false;
    }

    // Returns the Quaternion converted from this
    YQuat YMat4x4::Quaternion() const {
        YQuat ez;
        float SQ = m[0][0] + m[1][1] + m[2][2];

        float bigVal = YMath::Sqrt(SQ + 1.0f) * 0.5f;

        float mult = 1.0f /(4 * bigVal);

        ez.w = bigVal;
        ez.x = -(m[1][2] - m[2][1]) * mult;
        ez.y = -(m[2][0] - m[0][2]) * mult;
        ez.z = -(m[0][1] - m[1][0]) * mult;
        return ez;
    }

    // Transforms the YVec4 using this matrix
    YVec4 YMat4x4::TransformVec4(const YVec4 &V) const {
        return (*this)*V;
    }

    // Transform the YVec3 using only translation => Only Translates
    YVec3 YMat4x4::TransformPosition(const YVec3 &V) const {
        YMat4x4 Helper = YMat4x4::Identity;
        Helper.m[0][3] = this->m[0][3];
        Helper.m[1][3] = this->m[1][3];
        Helper.m[2][3] = this->m[2][3];
        return YVec3(Helper * YVec4(V, 1.0f));
    }

    // Transform the YVec3 not using translation => Does everything except translate
    YVec3 YMat4x4::TransformVector(const YVec3 &V) const {
        YMat4x4 Helper = YMat4x4(YMat3x3(*this));
        return YVec3(Helper * YVec4(V, 1.0f));
    }

    // Transforms the YVec3 using this matrix
    YVec3 YMat4x4::TransformVec3(const YVec3 &Point) const {
        YVec4 result = (*this) * YVec4(Point, 1.0f);
        return YVec3(result.x, result.y, result.z);
    }

    // "Adds" the Rotation of Matrix to this
    // Or in other words Multiplies Matrix and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotation(const YMat3x3 &Matrix) const {
        YMat4x4 Helper;
        Helper.SetupRotation(Matrix);
        return Helper * (*this);
    }

    // "Adds" the Rotation of Matrix to this
    // Or in other words Multiplies Matrix and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotation(const YMat4x4& Matrix) const {
        YMat4x4 Helper;
        Helper.SetupRotation(Matrix);
        return Helper * (*this);
    }

    // "Adds" the Rotation of Rotate Quaternion to this
    // Or in other words Multiplies Quaternion Rotation and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotation(const YQuat &Rotate) const {
        YMat4x4 Helper;
        Helper.SetupRotation(Rotate);
        return Helper * (*this);
    }

    // "Adds" the Rotation x,y,z to this
    // Or in other words Multiplies Rotation matrix formed by x,y,z and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotation(float xRotation, float yRotation, float zRotation) const {
        YMat4x4 Helper;
        Helper.SetupRotation(xRotation, yRotation, zRotation);
        return Helper * (*this);
    }

    // "Adds" the Rotation from Axis and angle to this
    // Or in other words Multiplies matrix formed by Axis and Angle and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotation(const YVec3 &Axis, float Angle) const {
        YMat4x4 Helper;
        Helper.SetupRotation(Axis, Angle);
        return Helper * (*this);
    }

    // "Adds" the Rotation from Euler to this
    // Or in other words Multiplies Euler Rotation and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotation(const YEuler &Euler) const {
        YMat4x4 Helper;
        Helper.SetupRotation(Euler);
        return Helper * (*this);
    }

    // "Adds" the Rotation of xAngle to X Axis of this
    // Or in other words Multiplies matrix X Rotation and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotationX(float xAngle) const {
        YMat4x4 Helper;
        Helper.SetupRotationX(xAngle);
        return Helper * (*this);
    }

    // "Adds" the Rotation of yAngle to Y Axis of this
    // Or in other words Multiplies matrix Y Rotation and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotationY(float yAngle) const {
        YMat4x4 Helper;
        Helper.SetupRotationY(yAngle);
        return Helper * (*this);
    }

    // "Adds" the Rotation of zAngle to Z Axis of this
    // Or in other words Multiplies matrix Z Rotation and this to apply the set transformation
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyRotationZ(float zAngle) const {
        YMat4x4 Helper;
        Helper.SetupRotationZ(zAngle);
        return Helper * (*this);
    }

    // Applies a Scale on top of the scale of this
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyScale(float Scale) const {
        YMat4x4 Helper;
        Helper.SetupScale(Scale);
        return Helper * (*this);
    }

    // Applies a Scale on top of the scale of this
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyScale(const YVec3 &Scale) const {
        YMat4x4 Helper;
        Helper.SetupScale(Scale);
        return Helper * (*this);
    }

    // Applies Translation on top of translation of this
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyTranslation(const YVec3 &xLate) const {
        YMat4x4 Helper;
        Helper.SetupTranslation(xLate);
        return Helper * (*this);
    }

    // Applies projection to this
    // Applies Transformation
    YMat4x4 YMat4x4::ApplyProject(const YVec3 &Normal) const {
        YMat4x4 Helper;
        Helper.SetupProject(Normal);
        return Helper * (*this);
    }

    // Gets the ith column
    YVec3 YMat4x4::GetColumn(int i) const {
        return YVec3(m[0][i], m[1][i], m[2][i]);
    }

    // Gets the ith row
    YVec3 YMat4x4::GetRow(int i) const {
        return YVec3(m[i][0], m[i][1], m[i][2]);
    }

    bool YMat4x4::GetFrustumBottomPlane(YPlane &OUT OutPlane) const {
        return false;
    }

    bool YMat4x4::GetFrustumTopPlane(YPlane &OUT OutPlane) const {
        return false;
    }

    bool YMat4x4::GetFrustumRightPlane(YPlane &OUT OutPlane) const {
        return false;
    }

    bool YMat4x4::GetFrustumLeftPlane(YPlane &OUT OutPlane) const {
        return false;
    }

    bool YMat4x4::GetFrustumNearPlane(YPlane &OUT OutPlane) const {
        return false;
    }

    bool YMat4x4::GetFrustumFarPlane(YPlane &OUT OutPlane) const {
        return false;
    }

    // Gets this Matrix with scale factor removed
    YMat4x4 YMat4x4::GetMatrixWithoutScale(float Tolerance) const {
        YVec3 Helper = GetScaledVector();
        if (YMath::IsNearlyZero(Helper.x, Tolerance) ||
            YMath::IsNearlyZero(Helper.y, Tolerance) ||
            YMath::IsNearlyZero(Helper.z, Tolerance)) {
            return *this;
        }

        return YMat4x4(
            YVec4(YVec3(m[0][0], m[0][1], m[0][2]) / Helper.x, this->m[0][3]),
            YVec4(YVec3(m[1][0], m[1][1], m[1][2]) / Helper.y, this->m[1][3]),
            YVec4(YVec3(m[2][0], m[2][1], m[2][2]) / Helper.z, this->m[2][3]),
            YVec4(this->m[3][0], this->m[3][1], this->m[3][2], 1.0f)
        );
    }

    YVec3 YMat4x4::GetOrigin() const {
        return YVec3();
    }

    // Gets the Maximum of Scale of Each Axis
    float YMat4x4::GetMaximumAxisScale() const {
        float magA = YVec3(m[0][0], m[0][1], m[0][2]).Magnitude();
        float magB = YVec3(m[1][0], m[1][1], m[1][2]).Magnitude();
        float magC = YVec3(m[2][0], m[2][1], m[2][2]).Magnitude();

        return YMath::Max(YMath::Max(magA, magC), magB);
    }

    // Gets the Scaled Axes from Rows of this
    void YMat4x4::GetScaledAxes(YVec3 &OUT X, YVec3 &OUT Y, YVec3 &OUT Z) const {
        X = YVec3(m[0][0], m[0][1], m[0][2]);
        Y = YVec3(m[1][0], m[1][1], m[1][2]);
        Z = YVec3(m[2][0], m[2][1], m[2][2]);
    }

    // Gets the Scaled Vector from the Magnitude of Rows of this
    YVec3 YMat4x4::GetScaledVector() const {
        return YVec3(
            YVec3(m[0][0], m[0][1], m[0][2]).Magnitude(),
            YVec3(m[1][0], m[1][1], m[1][2]).Magnitude(),
            YVec3(m[2][0], m[2][1], m[2][2]).Magnitude());
    }

    // Sets the Column i with the values in Value YVec3
    void YMat4x4::SetColumn(int i, YVec3 Value) {
        m[0][i] = Value.x;
        m[1][i] = Value.y;
        m[2][i] = Value.z;
    }

    // Sets the Row i with the values in Value YVec3
    void YMat4x4::SetRow(int i, YVec3 Value) {
        m[0][i] = Value.x;
        m[1][i] = Value.y;
        m[2][i] = Value.z;
    }

    // Transposes this
    void YMat4x4::Transpose() {
        YMat4x4 helper;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                helper.m[j][i] = m[i][j];
            }
        }
        *this = helper;
    }

    // Adjoint this this
    void YMat4x4::Adjoint() {
        YMat4x4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = GetCofactor(i, j);
                if ((i + j) % 2 == 1) {
                    result.m[i][j] = -result.m[i][j];
                }
            }
        }
        result.Transpose();
        *this = result;
    }

    // Makes this into its inverse
    void YMat4x4::Inverse() {
        if (YMath::IsZero(Determinant())) {
            return;
        }
        *this =  GetAdjoint() * (1 / Determinant());
    }

    // Makes this into its inverse (faster)
    void YMat4x4::InverseFast() {
        return;
    }

    // Removes Scaling from this matrix, i.e. Make magnitude of column vectors 1
    void YMat4x4::RemoveScaling(float Tolerance) {
        YVec3 Helper = GetScaledVector();
        if (YMath::IsNearlyZero(Helper.x, Tolerance) ||
            YMath::IsNearlyZero(Helper.y, Tolerance) ||
            YMath::IsNearlyZero(Helper.z, Tolerance)) {
            return;
        }
        
        *this = YMat4x4(
            YVec4(YVec3(m[0][0], m[0][1], m[0][2]) / Helper.x, this->m[0][3]),
            YVec4(YVec3(m[1][0], m[1][1], m[1][2]) / Helper.y, this->m[1][3]),
            YVec4(YVec3(m[2][0], m[2][1], m[2][2]) / Helper.z, this->m[2][3]),
            YVec4(this->m[3][0], this->m[3][1], this->m[3][2], 1.0f)
        );
    }

    // Sets the Rotation part of this using Matrix (3x3 Matrix)
    void YMat4x4::SetupRotation(const YMat3x3 &Matrix) {
        *this = YMat4x4(Matrix);
    }

    // Sets the Rotation part of this using Matrix (4x4 Matrix)
    void YMat4x4::SetupRotation(const YMat4x4& Matrix) {
        *this = YMat4x4(Matrix);
    }

    // Sets the Rotation part of this using Rotate (Quaternion)
    void YMat4x4::SetupRotation(const YQuat &Rotate) {
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
        for (int i = 0; i < 3; i++) {
            m[3][i] = 0.0f;
            m[i][3] = 0.0f;
        }
        m[3][3] = 1.0f;
    }

    // Sets the Rotation part of this using x,y,z Rotations
    void YMat4x4::SetupRotation(float xRotation, float yRotation, float zRotation) {
        xRotation = YMath::DegToRad(xRotation);
        yRotation = YMath::DegToRad(yRotation);
        zRotation = YMath::DegToRad(zRotation);
        YMat3x3 Rx = YMat3x3(
            YVec3(1.0f, 0.0f, 0.0f),
            YVec3(0.0f, YMath::Cos(xRotation), -YMath::Sin(xRotation)),
            YVec3(0.0f, YMath::Sin(xRotation), YMath::Cos(xRotation)));
        YMat3x3 Ry = YMat3x3(
            YVec3(YMath::Cos(yRotation), 0.0f, YMath::Sin(yRotation)),
            YVec3(0.0f, 1.0f, 0.0f),
            YVec3(-YMath::Sin(yRotation), 0.0f, YMath::Cos(yRotation)));
        YMat3x3 Rz = YMat3x3(
            YVec3(YMath::Cos(zRotation), -YMath::Sin(zRotation), 0.0f),
            YVec3(YMath::Sin(zRotation), YMath::Cos(zRotation), 0.0f),
            YVec3(0.0f, 0.0f, 1.0f));
        YMat3x3 RotMat = Rz * Ry * Rx;
        *this = YMat4x4(RotMat);
    }

    // Sets the Rotation part of this using Axis and Angle
    void YMat4x4::SetupRotation(const YVec3 &Axis, float Angle) {
        Angle = YMath::DegToRad(Angle);
        YVec3 Helper = Axis;
        if (!Helper.IsUnit(yEpsilon)) {
            Helper = Helper.GetSafeNormal();
        }
        float sin, cos;
        YMath::SinCos(&sin, &cos, Angle);

        YMat3x3 CM = cos * YMat3x3::Identity;
        YMat3x3 TM = (1-cos) * YMat3x3(
            YVec3(Helper.x * Helper.x, Helper.x * Helper.y, Helper.x * Helper.z),
            YVec3(Helper.x * Helper.y, Helper.y * Helper.y, Helper.y * Helper.z),
            YVec3(Helper.x * Helper.z, Helper.z * Helper.y, Helper.z * Helper.z)
        );
        YMat3x3 SM = sin * YMat3x3(
            YVec3(0.0f, -Helper.z, Helper.y),
            YVec3(Helper.z, 0.0f, -Helper.x),
            YVec3(-Helper.y, Helper.x, 0.0f)
        );

        *this = YMat4x4(CM + TM + SM);

        for (int i = 0; i < 3; i++) {
            m[3][i] = 0.0f;
            m[i][3] = 0.0f;
        }
        m[3][3] = 1.0f;
    }

    // Sets the Rotation part of this using Euler Angles
    void YMat4x4::SetupRotation(const YEuler &Euler) {
        float pitch = YMath::DegToRad(Euler.pitch);
        float yaw = YMath::DegToRad(Euler.yaw);
        float roll = YMath::DegToRad(Euler.roll);
        YMat3x3 Rx = YMat3x3(
            YVec3(1.0f, 0.0f, 0.0f),
            YVec3(0.0f, YMath::Cos(pitch), -YMath::Sin(pitch)),
            YVec3(0.0f, YMath::Sin(pitch), YMath::Cos(pitch)));
        YMat3x3 Ry = YMat3x3(
            YVec3(YMath::Cos(yaw), 0.0f, YMath::Sin(yaw)),
            YVec3(0.0f, 1.0f, 0.0f),
            YVec3(-YMath::Sin(yaw), 0.0f, YMath::Cos(yaw)));
        YMat3x3 Rz = YMat3x3(
            YVec3(YMath::Cos(roll), -YMath::Sin(roll), 0.0f),
            YVec3(YMath::Sin(roll), YMath::Cos(roll), 0.0f),
            YVec3(0.0f, 0.0f, 1.0f));
        YMat3x3 RotMat = Rz * Ry * Rx;
        *this = YMat4x4(RotMat);
    }

    // Sets the Rotation part of this to Rotate around X Axis
    void YMat4x4::SetupRotationX(float xAngle) {
        xAngle = YMath::DegToRad(xAngle);
        YMat3x3 Rx = YMat3x3(
            YVec3(1.0f, 0.0f, 0.0f),
            YVec3(0.0f, YMath::Cos(xAngle), -YMath::Sin(xAngle)),
            YVec3(0.0f, YMath::Sin(xAngle), YMath::Cos(xAngle)));
        *this = YMat4x4(Rx);
    }

    // Sets the Rotation part of this to Rotate around Y Axis
    void YMat4x4::SetupRotationY(float yAngle) {
        yAngle = YMath::DegToRad(yAngle);
        YMat3x3 Ry = YMat3x3(
            YVec3(YMath::Cos(yAngle), 0.0f, YMath::Sin(yAngle)),
            YVec3(0.0f, 1.0f, 0.0f),
            YVec3(-YMath::Sin(yAngle), 0.0f, YMath::Cos(yAngle)));
        *this = YMat4x4(Ry);
    }

    // Sets the Rotation part of this to Rotate around Z Axis
    void YMat4x4::SetupRotationZ(float zAngle) {
        zAngle = YMath::DegToRad(zAngle);
        YMat3x3 Rz = YMat3x3(
            YVec3(YMath::Cos(zAngle), -YMath::Sin(zAngle), 0.0f),
            YVec3(YMath::Sin(zAngle), YMath::Cos(zAngle), 0.0f),
            YVec3(0.0f, 0.0f, 1.0f));
        *this = YMat4x4(Rz);
    }

    // Sets the Scale part of this using Scale(float)
    // Scales along all the axes equally
    void YMat4x4::SetupScale(float Scale) {
        *this = YMat4x4(
            YVec4(Scale, 0.0f, 0.0f, 0.0f),
            YVec4(0.0f, Scale, 0.0f, 0.0f),
            YVec4(0.0f, 0.0f, Scale, 0.0f),
            YVec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    // Sets the Scale part of this using Scale(YVec3)
    // Scales along the axes according to x,y,z of Scale
    void YMat4x4::SetupScale(const YVec3 &Scale) {
        *this = YMat4x4(
            YVec4(Scale.x, 0.0f, 0.0f, 0.0f),
            YVec4(0.0f, Scale.y, 0.0f, 0.0f),
            YVec4(0.0f, 0.0f, Scale.z, 0.0f),
            YVec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    // Sets the Translation part of this using xLate
    void YMat4x4::SetupTranslation(const YVec3 &xLate) {
        *this = YMat4x4(
            YVec4(1.0f, 0.0f, 0.0f, xLate.x),
            YVec4(0.0f, 1.0f, 0.0f, xLate.y),
            YVec4(0.0f, 0.0f, 1.0f, xLate.z),
            YVec4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    // Scales the translation part of the Matrix by x,y,x of Scale3D
    void YMat4x4::ScaleTranslation(const YVec3 &Scale3D) {
        m[0][3] *= Scale3D.x;
        m[1][3] *= Scale3D.y;
        m[2][3] *= Scale3D.z;
    }

    // Sets up this which can be used to project onto Normal
    void YMat4x4::SetupProject(const YVec3 &Normal) {
        assert(Normal.IsUnit(yEpsilon));

        m[0][0] = 1.0f - Normal.x * Normal.x;
        m[1][1] = 1.0f - Normal.y * Normal.y;
        m[2][2] = 1.0f - Normal.z * Normal.z;

        m[0][1] = m[1][0] = -Normal.x * Normal.y;
        m[0][2] = m[2][0] = -Normal.x * Normal.z;
        m[1][2] = m[2][1] = -Normal.y * Normal.z;

        for (int i = 0; i < 3; i++) {
            m[3][i] = 0.0f;
            m[i][3] = 0.0f;
        }
        m[3][3] = 1.0f;
    }

    // Gets Fixed Angles present in this
    void YMat4x4::GetFixedAngles(float &xRotation, float &yRotation, float &zRotation) {
        // pitch x
        // roll z
        // yaw y

        //float sinPitch = -m[1][2];
        //if (sinPitch <= -1.0f) {
        //    xRotation = -yPiBy2;
        //}
        //else if (sinPitch >= 1.0f) {
        //    xRotation = yPiBy2;
        //}
        //else {
        //    xRotation = YMath::ASin(sinPitch);
        //}

        //// avoiding gimbal lock
        //if (sinPitch > 0.9999f) {
        //    // zRotation to zero
        //    // set just yRotation
        //    zRotation = 0.0f;
        //    yRotation = YMath::ATan2(-m[2][0], m[0][0]);
        //}
        //else {
        //    yRotation = YMath::ATan2(m[0][2], m[2][2]);
        //    zRotation = YMath::ATan2(m[1][0], m[1][1]);
        //}

        xRotation = YMath::ATan2(-m[2][0], YMath::Sqrt(m[2][1] * m[2][1] + m[2][2] * m[2][2]));
        zRotation = YMath::ATan2(m[1][0], m[0][0]);
        yRotation = YMath::ATan2(m[2][1], m[2][2]);


    }

    // MARK FOR REVIEW
    // Gets the Axis and angle present in this
    void YMat4x4::GetAxisAngle(YVec3 &Axis, float &Angle) {
        Angle = YMath::ACos((m[0][0] + m[1][1] + m[2][2] - 1) / 2);
        Angle = YMath::RadToDeg(Angle);
        Axis.x = m[2][1] - m[1][2] /
            YMath::Sqrt((m[2][1] - m[1][2]) * (m[2][1] - m[1][2]) +
                        (m[0][2] - m[2][0]) * (m[0][2] - m[2][0]) +
                        (m[1][0] - m[0][1]) * (m[1][0] - m[0][1]));
        Axis.y = m[0][2] - m[2][0] /
            YMath::Sqrt((m[2][1] - m[1][2]) * (m[2][1] - m[1][2]) +
                        (m[0][2] - m[2][0]) * (m[0][2] - m[2][0]) +
                        (m[1][0] - m[0][1]) * (m[1][0] - m[0][1]));
        Axis.z = m[1][0] - m[0][1] /
            YMath::Sqrt((m[2][1] - m[1][2]) * (m[2][1] - m[1][2]) +
                        (m[0][2] - m[2][0]) * (m[0][2] - m[2][0]) +
                        (m[1][0] - m[0][1]) * (m[1][0] - m[0][1]));
    }

    //
    // FUNCTIONS END
    //
}
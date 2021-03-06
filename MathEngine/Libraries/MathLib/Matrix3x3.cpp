#pragma once
#include "Matrix3x3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include "GenMath.h"
#include "Matrix4x4.h"
//ONLY USED FOR ROTATION
namespace YSAoo {

	const YMat3x3 YMat3x3::Identity = YMat3x3(
		YVec3(1.0f, 0.0f, 0.0f),
		YVec3(0.0f, 1.0f, 0.0f),
		YVec3(0.0f, 0.0f, 1.0f)
	);
	//
	// Constructors
	//

	YMat3x3::YMat3x3() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	YMat3x3::YMat3x3(const YMat3x3& InMat3x3) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = InMat3x3.m[i][j];
			}
		}
	}
	YMat3x3::YMat3x3(const YMat4x4& InMat4x4) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = InMat4x4.m[i][j];
			}
		}
	}
	YMat3x3::YMat3x3(const YVec3& InX, const YVec3& InY, const YVec3& InZ) {
		m[0][0] = InX.x;
		m[0][1] = InX.y;
		m[0][2] = InX.z;
		m[1][0] = InY.x;
		m[1][1] = InY.y;
		m[1][2] = InY.z;
		m[2][0] = InZ.x;
		m[2][1] = InZ.y;
		m[2][2] = InZ.z;
	}

	void YMat3x3::operator=(const YMat3x3& Other) {
		if (this == &Other)
			return;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = Other.m[i][j];
			}
		}
	}

	bool YMat3x3::operator==(const YMat3x3& Other) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!YMath::AreEqual(m[i][j], Other.m[i][j])) {
					return false;
				}
			}
		}
		return true;
	}

	bool YMat3x3::operator!=(const YMat3x3& Other) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!YMath::AreEqual(m[i][j], Other.m[i][j])) {
					return true;
				}
			}
		}
		return false;
	}

	YMat3x3 YMat3x3::operator+(const YMat3x3& Other) const {
		YMat3x3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.m[i][j] = m[i][j] + Other.m[i][j];
			}
		}

		return result;
	}

	YMat3x3 YMat3x3::operator+=(const YMat3x3& Other) {
		return *this + Other;
	}

	// Negation -> Makes the values in the matrix of the opposite sign (+ -> -, - -> +)
	YMat3x3 YMat3x3::operator-() const {
		YMat3x3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.m[i][j] = -m[i][j];
			}
		}

		return result;
	}

	YMat3x3 YMat3x3::operator-(const YMat3x3& Other) const {
		YMat3x3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.m[i][j] = m[i][j] - Other.m[i][j];
			}
		}

		return result;
	}

	YMat3x3 YMat3x3::operator-=(const YMat3x3& Other) {
		return *this - Other;
	}

	YMat3x3 YMat3x3::operator*(const YMat3x3& Other) const {
		YMat3x3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					result.m[i][j] += m[i][k] * Other.m[k][j];
				}
			}
		}

		return result;
	}

	YMat3x3 YMat3x3::operator*=(const YMat3x3& Other) {
		return *this * Other;
	}

	YMat3x3 YMat3x3::operator*(float Scalar) const {
		YMat3x3 result;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.m[i][j] = m[i][j] * Scalar;
			}
		}

		return result;
	}

	YMat3x3 operator*(float Scalar, const YMat3x3& Other) {
		return Other * Scalar;
	}

	YMat3x3 YMat3x3::operator*=(float Scalar) {
		return (*this) * Scalar;
	}


	// Matrix accessor
	float& YMat3x3::operator()(unsigned int i, unsigned int j) {
		return m[i][j];
	}

	// Matrix accessor
	float YMat3x3::operator()(unsigned int i, unsigned int j) const {
		return m[i][j];
	}

	YVec3 YMat3x3::operator*(const YVec3& Vector) const {
		YVec3 result;
		result.x = m[0][0] * Vector.x + m[0][1] * Vector.y + m[0][2] * Vector.z;
		result.y = m[1][0] * Vector.x + m[1][1] * Vector.y + m[1][2] * Vector.z;
		result.z = m[2][0] * Vector.x + m[2][1] * Vector.y + m[2][2] * Vector.z;
		return result;
	}

	YVec3 operator*(const YVec3& Vector, const YMat3x3& matrix) {
		YVec3 result;
		YMat3x3 Matrix = matrix.GetTranspose();
		for (int j = 0; j < 3; j++) {
			result.x += Matrix.m[j][0] * Vector.x;
		}
		for (int j = 0; j < 3; j++) {
			result.y += Matrix.m[j][1] * Vector.y;
		}
		for (int j = 0; j < 3; j++) {
			result.z += Matrix.m[j][2] * Vector.z;
		}

		return result;
	}


	// OSTREAM OPERATOR
	std::ostream& operator<<(std::ostream& out, const YMat3x3& matrix) {
		out << "Matrix 3x3 (Row Major):" << std::endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				out << matrix.m[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	//
	// Functions
	//
	void YMat3x3::Transpose() {
		YMat3x3 helper;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				helper.m[j][i] = m[i][j];
			}
		}
		*this = helper;
	}

	YMat3x3 YMat3x3::GetTranspose() const {
		YMat3x3 helper;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				helper.m[j][i] = m[i][j];
			}
		}
		return helper;
	}

	float YMat3x3::GetCofactor(int IndexI, int IndexJ) const {
		int i1, j1, i2, j2;
		if (IndexI == 0) {
			i1 = 1;
			i2 = 2;
		}
		else if (IndexI == 1) {
			i1 = 0;
			i2 = 2;
		}
		else if (IndexI == 2) {
			i1 = 0;
			i2 = 1;
		}
		else {
			std::cout << "Error" << std::endl;
			return 0;
		}
		if (IndexJ == 0) {
			j1 = 1;
			j2 = 2;
		}
		else if (IndexJ == 1) {
			j1 = 0;
			j2 = 2;
		}
		else if (IndexJ == 2) {
			j1 = 0;
			j2 = 1;
		}
		else {
			std::cout << "Error" << std::endl;
			return 0;
		}
		return m[i1][j1] * m[i2][j2] - m[i1][j2]*m[i2][j1];
	}

	float YMat3x3::Determinant() const {
		float det = 0.0f;
		det += m[0][0] * GetCofactor(0, 0);
		det -= m[0][1] * GetCofactor(0, 1);
		det += m[0][2] * GetCofactor(0, 2);
		return det;
	}

	YMat3x3 YMat3x3::Adjoint() const {
		YMat3x3 result;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.m[i][j] = GetCofactor(i, j);
				if ((i + j) % 2 == 1) {
					result.m[i][j] = -result.m[i][j];
				}
			}
		}
		result.Transpose();
		return result;
	}

	YMat3x3 YMat3x3::Inverse() const {
		if (YMath::IsZero(Determinant())) {
			return YMat3x3();
		}
		return Adjoint() * (1 / Determinant());
	}
	
	YMat3x3 YMat3x3::InverseFast() const {
		return YMat3x3();
	}
	
	void YMat3x3::ToIdentity() {
		*this = YMat4x4();
		for (int i = 0; i < 3; i++) {
			m[i][i] = 1.0f;
		}
	}

	void YMat3x3::SetupRotation(const YEuler& Euler) {
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
		*this = Rx * Ry * Rz;
	}

	// Sets the Rotation part of this using Matrix (4x4 Matrix)
	void YMat3x3::SetupRotation(const YMat3x3& Matrix) {
		*this = Matrix;
	}

	// Sets the Rotation part of this using Rotate (Quaternion)
	void YMat3x3::SetupRotation(const YQuat& Rotate) {
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

	// Sets the Rotation part of this using x,y,z Rotations
	void YMat3x3::SetupRotation(float xRotation, float yRotation, float zRotation) {
		xRotation = YMath::DegToRad(xRotation);
		yRotation = YMath::DegToRad(yRotation);
		zRotation = YMath::DegToRad(zRotation);
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
		*this = Rx * Ry * Rz;
	}

	// Sets the Rotation part of this using Axis and Angle
	void YMat3x3::SetupRotation(const YVec3& Axis, float Angle) {
		YVec3 Helper = Axis;
		if (!Helper.IsUnit(yEpsilon)) {
			Helper = Helper.GetSafeNormal();
		}
		float sin, cos;
		YMath::SinCos(&sin, &cos, Angle);

		float a = 1.0f - cos;
		float ax = a * Helper.x;
		float ay = a * Helper.y;
		float az = a * Helper.z;

		m[0][0] = ax * Helper.x + cos;
		m[0][1] = ax * Helper.y + Helper.z * sin;
		m[0][2] = ax * Helper.z - Helper.y * sin;
		m[1][0] = ay * Helper.x - Helper.z * sin;
		m[1][1] = ay * Helper.y + cos;
		m[1][2] = ay * Helper.z + Helper.x * sin;
		m[2][0] = az * Helper.x + Helper.y * sin;
		m[2][1] = az * Helper.y - Helper.x * sin;
		m[2][2] = az * Helper.z + cos;
	}

	YEuler YMat3x3::Rotation() const {
		assert(IsRotationMatrix());
		float pitch = 0.0f; //x rot
		float yaw = 0.0f;   //y rot
		float roll = 0.0f;  //z rot
		float sinPitch = -m[1][2];
		if (sinPitch <= -1.0f) {
			pitch = -yPiBy2;
		}
		else if (sinPitch >= 1.0f) {
			pitch = yPiBy2;
		}
		else {
			pitch = YMath::ASin(sinPitch);
		}

		// avoiding gimbal lock
		if (sinPitch > 0.9999f) {
			roll = 0.0f;
			yaw = YMath::ATan2(-m[2][0], m[0][0]);
		}
		else {
			yaw = YMath::ATan2(m[0][2], m[2][2]);
			roll = YMath::ATan2(m[1][0], m[1][1]);
		}

		return YEuler(
			YMath::RadToDeg(roll),
			YMath::RadToDeg(pitch),
			YMath::RadToDeg(yaw));
	}

	// Returns true if this is a Rotation matrix
	// Make it Inverse fast after implementation !!!!!!!!!!!
	bool YMat3x3::IsRotationMatrix() const {
		if (this->Inverse() == this->GetTranspose()) {
			return true;
		}
		return false;
	}

	//// Sets the Rotation part of this using Euler Angles
	//inline void YMat3x3::SetupRotation(const YEuler& Euler) {
	//	YMat3x3 Rx = YMat3x3(
	//		YVec3(1.0f, 0.0f, 0.0f),
	//		YVec3(0.0f, YMath::Cos(Euler.pitch), -YMath::Sin(Euler.pitch)),
	//		YVec3(0.0f, YMath::Sin(Euler.pitch), YMath::Cos(Euler.pitch))
	//	);
	//	YMat3x3 Ry = YMat3x3(
	//		YVec3(YMath::Cos(Euler.yaw), 0.0f, YMath::Sin(Euler.yaw)),
	//		YVec3(0.0f, 1.0f, 0.0f),
	//		YVec3(-YMath::Sin(Euler.yaw), 0.0f, YMath::Cos(Euler.yaw))
	//	);
	//	YMat3x3 Rz = YMat3x3(
	//		YVec3(YMath::Cos(Euler.roll), -YMath::Sin(Euler.roll), 0.0f),
	//		YVec3(YMath::Sin(Euler.roll), YMath::Cos(Euler.roll), 0.0f),
	//		YVec3(0.0f, 0.0f, 1.0f)
	//	);
	//	*this = Rx * Ry * Rz;
	//}

	// Sets the Rotation part of this to Rotate around X Axis
	void YMat3x3::SetupRotationX(float xAngle) {
		xAngle = YMath::DegToRad(xAngle);
		*this = YMat3x3(
			YVec3(1.0f, 0.0f, 0.0f),
			YVec3(0.0f, YMath::Cos(xAngle), -YMath::Sin(xAngle)),
			YVec3(0.0f, YMath::Sin(xAngle), YMath::Cos(xAngle))
		);
	}

	// Sets the Rotation part of this to Rotate around Y Axis
	void YMat3x3::SetupRotationY(float yAngle) {
		yAngle = YMath::DegToRad(yAngle);
		*this = YMat3x3(
			YVec3(YMath::Cos(yAngle), 0.0f, YMath::Sin(yAngle)),
			YVec3(0.0f, 1.0f, 0.0f),
			YVec3(-YMath::Sin(yAngle), 0.0f, YMath::Cos(yAngle))
		);
	}

	// Sets the Rotation part of this to Rotate around Z Axis
	void YMat3x3::SetupRotationZ(float zAngle) {
		zAngle = YMath::DegToRad(zAngle);
		*this = YMat3x3(
			YVec3(YMath::Cos(zAngle), -YMath::Sin(zAngle), 0.0f),
			YVec3(YMath::Sin(zAngle), YMath::Cos(zAngle), 0.0f),
			YVec3(0.0f, 0.0f, 1.0f)
		);
	}

	// Sets the Scale part of this using Scale(float)
	// Scales along all the axes equally
	void YMat3x3::SetupScale(float Scale) {
		*this = YMat3x3(
			YVec3(Scale, 0.0f, 0.0f),
			YVec3(0.0f, Scale, 0.0f),
			YVec3(0.0f, 0.0f, Scale)
		);
	}

	// Sets the Scale part of this using Scale(YVec3)
	// Scales along the axes according to x,y,z of Scale
	void YMat3x3::SetupScale(const YVec3& Scale) {
		*this = YMat3x3(
			YVec3(Scale.x, 0.0f, 0.0f),
			YVec3(0.0f, Scale.y, 0.0f),
			YVec3(0.0f, 0.0f, Scale.z)
		);
	}

	// Sets up this which can be used to project onto Normal
	void YMat3x3::SetupProject(const YVec3& Normal) {
		assert(Normal.IsUnit(yEpsilon));

		m[0][0] = 1.0f - Normal.x * Normal.x;
		m[1][1] = 1.0f - Normal.y * Normal.y;
		m[2][2] = 1.0f - Normal.z * Normal.z;

		m[0][1] = m[1][0] = -Normal.x * Normal.y;
		m[0][2] = m[2][0] = -Normal.x * Normal.z;
		m[1][2] = m[2][1] = -Normal.y * Normal.z;
	}

	// "Adds" the Rotation of Matrix to this
	// Or in other words Multiplies Matrix and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotation(const YMat3x3& Matrix) const {
		YMat3x3 Helper;
		Helper.SetupRotation(Matrix);
		return Helper * (*this);
	}

	// "Adds" the Rotation of Rotate Quaternion to this
	// Or in other words Multiplies Quaternion Rotation and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotation(const YQuat& Rotate) const {
		YMat3x3 Helper;
		Helper.SetupRotation(Rotate);
		return Helper * (*this);
	}

	// "Adds" the Rotation x,y,z to this
	// Or in other words Multiplies Rotation matrix formed by x,y,z and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotation(float xRotation, float yRotation, float zRotation) const {
		YMat3x3 Helper;
		Helper.SetupRotation(xRotation, yRotation, zRotation);
		return Helper * (*this);
	}

	// "Adds" the Rotation from Axis and angle to this
	// Or in other words Multiplies matrix formed by Axis and Angle and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotation(const YVec3& Axis, float Angle) const {
		YMat3x3 Helper;
		Helper.SetupRotation(Axis, Angle);
		return Helper * (*this);
	}

	// "Adds" the Rotation from Euler to this
	// Or in other words Multiplies Euler Rotation and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotation(const YEuler& Euler) const {
		YMat3x3 Helper;
		Helper.SetupRotation(Euler);
		return Helper * (*this);
	}

	// "Adds" the Rotation of xAngle to X Axis of this
	// Or in other words Multiplies matrix X Rotation and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotationX(float xAngle) const {
		YMat3x3 Helper;
		Helper.SetupRotationX(xAngle);
		return Helper * (*this);
	}

	// "Adds" the Rotation of yAngle to Y Axis of this
	// Or in other words Multiplies matrix Y Rotation and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotationY(float yAngle) const {
		YMat3x3 Helper;
		Helper.SetupRotationY(yAngle);
		return Helper * (*this);
	}

	// "Adds" the Rotation of zAngle to Z Axis of this
	// Or in other words Multiplies matrix Z Rotation and this to apply the set transformation
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyRotationZ(float zAngle) const {
		YMat3x3 Helper;
		Helper.SetupRotationZ(zAngle);
		return Helper * (*this);
	}

	// Applies a Scale on top of the scale of this
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyScale(float Scale) const {
		YMat3x3 Helper;
		Helper.SetupScale(Scale);
		return Helper * (*this);
	}

	// Applies projection to this
	// Applies Transformation
	YMat3x3 YMat3x3::ApplyProject(const YVec3& Normal) const {
		YMat3x3 Helper;
		Helper.SetupProject(Normal);
		return Helper * (*this);
	}

	// Gets the ith column
	YVec3 YMat3x3::GetColumn(int i) const {
		return YVec3(m[0][i], m[1][i], m[2][i]);
	}

	// Gets the ith column
	YVec3 YMat3x3::GetRow(int i) const {
		return YVec3(m[i][0], m[i][1], m[i][2]);
	}

	// Sets the Column i with the values in Value YVec3
	void YMat3x3::SetColumn(int i, YVec3 Value) {
		m[0][i] = Value.x;
		m[1][i] = Value.y;
		m[2][i] = Value.z;
	}

	// Sets the Row i with the values in Value YVec3
	void YMat3x3::SetRow(int i, YVec3 Value) {
		m[0][i] = Value.x;
		m[1][i] = Value.y;
		m[2][i] = Value.z;
	}
}
#pragma once
#define OUT

namespace MathLib {
	class YVec3;
	class YVec4;
	class YMat3x3;
	class YQuat;
	class YPlane;
	class YEuler;
	class YMat4x4 {
	public:
		float m[4][4];

		//
		// CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes every entry to 0.0f
		YMat4x4();
		// Constructor - 4 YVec4s (ROW WISE Assignment)
		// Initializes rows to corresponding YVec4s
		YMat4x4(
			const YVec4& InX,
			const YVec4& InY,
			const YVec4& InZ,
			const YVec4& InW
		);
		// Constructor - 1 YMat3x3 (ROW WISE Assignment)
		// Initializes rows to corresponding rows in YMat3x3
		// Leaves out other columns to be zero and (4,4) to be 1
		YMat4x4(const YMat3x3& InMat3x3);
		// Constructor - 1 YMat4x4 (ROW WISE Assignment)
		// Initializes rows to corresponding rows in YMat4x4
		YMat4x4(const YMat4x4& InMat4x4);
		// Constructor - 4 YPlane s
		// Initializes ?
		/*inline YMat4x4(
			const YPlane& InX,
			const YPlane& InY,
			const YPlane& InZ,
			const YPlane& InW
		);*/

		//
		// CONSTRUCTOR OVERLOADS END
		//

		//
		// OPERATORS START
		//


		// Operator - Assignment
		YMat4x4 operator=(const YMat4x4& Other);

		// COMPARISION OPERATORS

		// Operator - Equality
		bool operator==(const YMat4x4& Other) const;
		// Operator - Inequality
		bool operator!=(const YMat4x4& Other) const;

		// ARITHMETIC OPERATORS

		// Addition

		// Operator -> this + Other(YMat4x4)
		YMat4x4 operator+(const YMat4x4& Other) const;
		// Operator -> this += Other(YMat4x4)
		YMat4x4 operator+=(const YMat4x4& Other);

		// Subtraction

		// Operator -> Negation
		YMat4x4 operator-() const;
		// Operator -> this - Other(YMat4x4)
		YMat4x4 operator-(const YMat4x4& Other) const;
		// Operator -> this -= Other(YMat4x4)
		YMat4x4 operator-=(const YMat4x4& Other);

		// Multiplication

		// Operator -> this * Other(YMat4x4)
		YMat4x4 operator*(const YMat4x4& Other) const;
		// Operator -> this *= Other(YMat4x4)
		YMat4x4 operator*=(const YMat4x4& Other);
		// Operator -> Scalar * this *
		friend YMat4x4 operator*(float Scalar, const YMat4x4& Matrix);
		// Operator -> this * Scalar
		YMat4x4 operator*(float Scalar) const;
		// Operator -> this *= Scalar
		YMat4x4 operator*=(float Scalar);

		// ACCESSING OPERATORS

		// Operator - (row,column) Accessor
		float& operator()(unsigned int i, unsigned int j);
		// Operator - (row,column) Accessor
		float operator()(unsigned int i, unsigned int j) const;

		// SPECIAL OPERATORS

		// this * YVec4 (Column Vector) 
		YVec4 operator*(const YVec4& Vector) const;
		// this * YVec4 (Row Vector)
		friend YVec4 operator*(const YVec4& Vector, const YMat4x4& matrix);

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Helper Functions
		float GetCofactor(int i, int j) const;

		// Const Functions
		bool IsZero() const;
		bool IsIdentity() const;
		float Determinant() const;
		bool Equals(const YMat4x4& Other) const;
		YMat4x4 Adjoint() const;
		YMat4x4 Inverse() const;
		YMat4x4 InverseFast() const;
		YVec3 InverseTransformPosition(const YVec3& V) const;
		YVec3 InverseTransformVector(const YVec3& V) const;
		YMat4x4 RemoveTranslation(float Tolerance) const;
		YEuler Rotation() const;
		bool IsRotationMatrix() const;
		YQuat Quaternion() const;
		YVec4 TransformVec4(const YVec4& V) const;
		YVec4 TransformPosition(const YVec3& V) const;
		YVec4 TransformVector(const YVec3& V) const;
		YVec3 Transform(const YVec3& point) const;

		/* DANGEROUS PRONE TO GIMBAL LOCK (BELOW)*/
		YMat4x4 ApplyRotation(const YMat3x3& Matrix) const;
		YMat4x4 ApplyRotation(const YQuat& Rotate) const;
		YMat4x4 ApplyRotation(float xRotation, float yRotation, float zRotation) const;
		YMat4x4 ApplyRotation(const YVec3& Axis, float Angle) const;
		YMat4x4 ApplyRotation(const YEuler& Euler) const;
		YMat4x4 ApplyRotationX(float xAngle) const;
		YMat4x4 ApplyRotationY(float yAngle) const;
		YMat4x4 ApplyRotationZ(float zAngle) const;
		YMat4x4 ApplyScale(float Scale) const;
		YMat4x4 ApplyScale(const YVec3& Scale) const;
		YMat4x4 ApplyTranslation(const YVec3& xLate) const;
		YMat4x4 ApplyProject(const YVec3& Normal) const;
		/* DANGEROUS PRONE TO GIMBAL LOCK (ABOVE)*/

		// Const GET Functions
		YVec3 GetColumn(int i) const;
		YVec3 GetRow(int i) const;
		bool GetFrustumBottomPlane(YPlane& OUT OutPlane) const;
		bool GetFrustumTopPlane(YPlane& OUT OutPlane) const;
		bool GetFrustumRightPlane(YPlane& OUT OutPlane) const;
		bool GetFrustumLeftPlane(YPlane& OUT OutPlane) const;
		bool GetFrustumNearPlane(YPlane& OUT OutPlane) const;
		bool GetFrustumFarPlane(YPlane& OUT OutPlane) const;
		YMat4x4 GetMatrixWithoutScale(float Tolerance) const;
		YVec3 GetOrigin() const;
		float GetMaximumAxisScale() const;
		void GetScaledAxes(
			YVec3& OUT X,
			YVec3& OUT Y,
			YVec3& OUT Z
		) const;
		YVec3 GetScaledVector() const;

		// Set Functions
		void SetColumn(int i, YVec3 Value);
		void SetRow(int i, YVec3 Value);
		
		// Non Const Functions
		//inline void Mirror();
		void Transpose();
		void RemoveScaling(float Tolerance);
		void SetupRotation(const YMat3x3& Matrix);
		void SetupRotation(const YQuat& Rotate);
		void SetupRotation(float xRotation, float yRotation, float zRotation);
		void SetupRotation(const YVec3& Axis, float Angle);
		void SetupRotation(const YEuler& Euler);
		void SetupRotationX(float xAngle);
		void SetupRotationY(float yAngle);
		void SetupRotationZ(float zAngle);
		void SetupScale(float Scale);
		void SetupScale(const YVec3& Scale);
		void SetupTranslation(const YVec3& xLate);
		void ScaleTranslation(const YVec3& Scale3D);
		void SetupProject(const YVec3& Normal);
		void GetFixedAngles(float& xRotation, float& yRotation, float& zRotation);
		void GetAxisAngle(YVec3& axis, float& angle);
		//inline YMat4x4 AffineInverse();

		// Static Functions

		//
		// FUNCTIONS END
		//

		//
		// STATIC VARIABLES START
		//

		static const YMat4x4 Identity;

		//
		// STATIC VARIABLES END
		//

		//YMat4x4& transpose();
		//friend YMat4x4 transpose(const YMat4x4& mat);
		//// point ops
		//YVec3 transformPoint(const YVec3& point) const;
	};
	//YMat4x4 affineInverse(const YMat4x4& mat);
	//YMat4x4 transpose(const YMat4x4& mat);
	
}
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
		inline YMat4x4();
		// Constructor - 4 YVec4s (ROW WISE Assignment)
		// Initializes rows to corresponding YVec4s
		inline YMat4x4(
			const YVec4& InX,
			const YVec4& InY,
			const YVec4& InZ,
			const YVec4& InW
		);
		// Constructor - 1 YMat3x3 (ROW WISE Assignment)
		// Initializes rows to corresponding rows in YMat3x3
		// Leaves out other columns to be zero and (4,4) to be 1
		inline YMat4x4(const YMat3x3& InMat3x3);
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
		inline YMat4x4 operator=(const YMat4x4& other);

		// COMPARISION OPERATORS

		// Operator - Equality
		inline bool operator==(const YMat4x4& other) const;
		// Operator - Inequality
		inline bool operator!=(const YMat4x4& other) const;

		// ARITHMETIC OPERATORS

		// Addition

		// Operator -> this + Other(YMat4x4)
		inline YMat4x4 operator+(const YMat4x4& Other) const;
		// Operator -> this += Other(YMat4x4)
		inline YMat4x4 operator+=(const YMat4x4& Other);

		// Subtraction

		// Operator -> Negation
		inline YMat4x4 operator-() const;
		// Operator -> this - Other(YMat4x4)
		inline YMat4x4 operator-(const YMat4x4& Other) const;
		// Operator -> this -= Other(YMat4x4)
		inline YMat4x4 operator-=(const YMat4x4& Other);

		// Multiplication

		// Operator -> this * Other(YMat4x4)
		inline YMat4x4 operator*(const YMat4x4& Other) const;
		// Operator -> this *= Other(YMat4x4)
		inline YMat4x4 operator*=(const YMat4x4& Other);
		// Operator -> Scalar * this *
		inline friend YMat4x4 operator*(float Scalar, const YMat4x4& Matrix);
		// Operator -> this * Scalar
		inline YMat4x4 operator*(float Scalar) const;
		// Operator -> this *= Scalar
		inline YMat4x4 operator*=(float Scalar);

		// ACCESSING OPERATORS

		// Operator - (row,column) Accessor
		inline float& operator()(unsigned int i, unsigned int j);
		// Operator - (row,column) Accessor
		inline float operator()(unsigned int i, unsigned int j) const;

		// SPECIAL OPERATORS

		// this * YVec4 (Column Vector) 
		inline YVec4 operator*(const YVec4& vector) const;
		// this * YVec4 (Row Vector)
		inline friend YVec4 operator*(const YVec4& vector, const YMat4x4& matrix);

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Helper Functions
		inline float GetCofactor(int i, int j) const;

		// Const Functions
		inline bool IsZero() const;
		inline bool IsIdentity() const;
		inline float Determinant() const;
		inline bool Equals(const YMat4x4& Other) const;
		inline YMat4x4 Adjoint() const;
		inline YMat4x4 Inverse() const;
		inline YMat4x4 InverseFast() const;
		inline YVec3 InverseTransformPosition(const YVec3& V) const;
		inline YVec3 InverseTransformVector(const YVec3& V) const;
		inline YMat4x4 RemoveTranslation(float Tolerance) const;
		inline YEuler Rotation() const;
		inline bool IsRotationMatrix() const;
		inline YQuat Quaternion() const;
		inline YVec4 TransformVec4(const YVec4& V) const;
		inline YVec4 TransformPosition(const YVec3& V) const;
		inline YVec4 TransformVector(const YVec3& V) const;
		inline YVec3 Transform(const YVec3& point) const;

		/* DANGEROUS PRONE TO GIMBAL LOCK (BELOW)*/
		inline YMat4x4 ApplyRotation(const YMat3x3& Matrix) const;
		inline YMat4x4 ApplyRotation(const YQuat& Rotate) const;
		inline YMat4x4 ApplyRotation(float xRotation, float yRotation, float zRotation) const;
		inline YMat4x4 ApplyRotation(const YVec3& Axis, float Angle) const;
		inline YMat4x4 ApplyRotation(const YEuler& Euler) const;
		inline YMat4x4 ApplyRotationX(float xAngle) const;
		inline YMat4x4 ApplyRotationY(float yAngle) const;
		inline YMat4x4 ApplyRotationZ(float zAngle) const;
		inline YMat4x4 ApplyScale(float Scale) const;
		inline YMat4x4 ApplyScale(const YVec3& Scale) const;
		inline YMat4x4 ApplyTranslation(const YVec3& xLate) const;
		inline YMat4x4 ApplyProject(const YVec3& Normal) const;
		/* DANGEROUS PRONE TO GIMBAL LOCK (ABOVE)*/

		// Const GET Functions
		inline YVec3 GetColumn(int i) const;
		inline YVec3 GetRow(int i) const;
		inline bool GetFrustumBottomPlane(YPlane& OUT OutPlane) const;
		inline bool GetFrustumTopPlane(YPlane& OUT OutPlane) const;
		inline bool GetFrustumRightPlane(YPlane& OUT OutPlane) const;
		inline bool GetFrustumLeftPlane(YPlane& OUT OutPlane) const;
		inline bool GetFrustumNearPlane(YPlane& OUT OutPlane) const;
		inline bool GetFrustumFarPlane(YPlane& OUT OutPlane) const;
		inline YMat4x4 GetMatrixWithoutScale(float Tolerance) const;
		inline YVec3 GetOrigin() const;
		inline float GetMaximumAxisScale() const;
		inline void GetScaledAxes(
			YVec3& OUT X,
			YVec3& OUT Y,
			YVec3& OUT Z
		) const;
		inline YVec3 GetScaledVector() const;

		// Set Functions
		inline void SetColumn(int i, YVec3 Value);
		inline void SetRow(int i, YVec3 Value);
		
		// Non Const Functions
		//inline void Mirror();
		inline void Transpose();
		inline void RemoveScaling(float Tolerance);
		inline void SetupRotation(const YMat3x3& Matrix);
		inline void SetupRotation(const YQuat& Rotate);
		inline void SetupRotation(float xRotation, float yRotation, float zRotation);
		inline void SetupRotation(const YVec3& Axis, float Angle);
		inline void SetupRotation(const YEuler& Euler);
		inline void SetupRotationX(float xAngle);
		inline void SetupRotationY(float yAngle);
		inline void SetupRotationZ(float zAngle);
		inline void SetupScale(float Scale);
		inline void SetupScale(const YVec3& Scale);
		inline void SetupTranslation(const YVec3& xLate);
		inline void ScaleTranslation(const YVec3& Scale3D);
		inline void SetupProject(const YVec3& Normal);
		inline void GetFixedAngles(float& xRotation, float& yRotation, float& zRotation);
		inline void GetAxisAngle(YVec3& axis, float& angle);
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
#pragma once
#define OUT

namespace MathLib {
	// Forward Declarations
	// Vector 2D
	class YVec2;
	// Vector 4D
	class YVec4;
	// Euler Angles
	class YEuler;
	// Quaternion
	class YQuat;
	class YVec3 {
	public:
		float x, y, z;
		//
		//CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes x,y,z to 0.0f
		inline YVec3();

		// Constructor - 1 float value
		// Initializes x and y to InFloat
		inline YVec3(float InF);

		// Constructor - 3 float values
		// Initializes x, y, z to InX, InY, InZ
		inline YVec3(float InX, float InY, float InZ);

		// Constructor - 1 YVec4 reference
		// Initializes x, y, z to InVec4.x, InVec4.y, InVec4.z
		inline YVec3(const YVec4& V);

		// Constructor - 1 YVec3 reference
		// Initializes x, y, z to InVec3.x, InVec3.y, InVec3.z
		inline YVec3(const YVec3& V);
		//One For Color

		// Constructor - 1 YVec2 reference, 1 float
		// Initializes x, y to InVec2.x, InVec2.y and z to InZ
		inline YVec3(const YVec2& V, float InZ);

		//
		// CONSTRUCTOR OVERLOADS END
		//

		//
		// OPERATORS START
		//

		// COMPARISION OPERATORS

		// Operator -> Equality
		inline bool operator==(const YVec3& Other) const;
		// Operator -> Inequality
		inline bool operator!=(const YVec3& Other) const;
		// Operator -> Less than
		inline bool operator<(const YVec3& Other) const;
		// Operator -> Less than or Equal to 
		inline bool operator<=(const YVec3& Other) const;
		// Operator -> Greater than
		inline bool operator>(const YVec3& Other) const;
		// Operator -> Greater than or Equal to 
		inline bool operator>=(const YVec3& Other) const;

		// ARITHMETIC OPERATORS

		// Addition
		
		// Operator -> this + YVec3 V
		inline YVec3 operator+(const YVec3& V) const;
		// Operator -> this + float A
		inline YVec3 operator+(float A) const;
		// Operator -> this += YVec3 V
		inline YVec3 operator+=(const YVec3& V);
		// Operator -> this += float A
		inline YVec3 operator+=(float A);

		// Subtraction

		// Operator -> Negation
		inline YVec3 operator-() const;
		// Operator -> this - YVec3 V
		inline YVec3 operator-(const YVec3& V) const;
		// Operator -> this - float A
		inline YVec3 operator-(float A) const;
		// Operator -> this -= YVec3 V
		inline YVec3 operator-=(const YVec3& V);
		// Operator -> this -= float A
		inline YVec3 operator-=(float A);

		// Multiplication

		// Operator -> this * YVec3 V
		inline YVec3 operator*(const YVec3& V) const;
		// Operator -> this * A
		inline YVec3 operator*(float A) const;
		// Operator -> V * A (friend)
		//inline friend YVec3 operator*(const YVec3& a, const float& mult);
		// Operator -> A * V (friend)
		inline friend YVec3 operator*(float A, const YVec3& V);
		// Operator -> this *= YVec3 V
		inline YVec3 operator*=(const YVec3& V);
		// Operator -> this *= float A
		inline YVec3 operator*=(float A);

		// Division

		// Operator -> this / YVec3 V
		inline YVec3 operator/(const YVec3& V) const;
		// Operator -> this / float A
		inline YVec3 operator/(float A) const;
		// Operator -> this /= YVec3 V
		inline YVec3 operator/=(const YVec3& V);
		// Operator -> this /= A
		inline YVec3 operator/=(float A);

		// ACCESSING OPERATORS

		// Operator - [] Accessor
		inline float& operator[](unsigned int i) { return (&x)[i]; }
		// Operator - [] Accessor
		inline float operator[](unsigned int i) const { return (&x)[i]; }

		// SPECIAL OPERATORS

		// Operator - Dot Product
		inline float operator|(const YVec3& V) const;
		// Operator - Cross product
		inline YVec3 operator^(const YVec3& V) const;
		
		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Const Functions
		inline bool AllComponentsEqual(float Tolerance) const;
		inline YVec3 BoundToBox(const YVec3& Max, const YVec3& Min) const;
		inline YVec3 BoundToCube(float Radius) const;
		inline YVec3 ComponentMax(const YVec3& Other) const;
		inline YVec3 ComponentMin(const YVec3& Other) const;
		inline bool ContainsNaN() const;
		inline float CosineAngle2D(YVec3 B) const;
		inline bool Equals(const YVec3& V, float Tolerance) const;
		inline YVec3 GridSnap(const float& GridSize) const;
		inline float HeadingAngle() const;
		inline bool IsNearlyZero(float Tolerance) const;
		inline bool IsZero() const;
		inline bool IsNormalized() const;
		inline bool IsUniform(float Tolerance) const;
		inline bool IsUnit(float LengthSquaredTolerance) const;
		//inline YVec3 MirrorByPlane(const YPlane& Plane) const;
		inline YVec3 MirrorByVector(const YVec3& MirrorNormal) const;
		inline YVec3 Projection() const;
		inline YVec3 ProjectOnTo(const YVec3& A) const;
		inline YVec3 ProjectOnToNormal(const YVec3& Normal) const;
		inline YVec3 Reciprocal() const;
		inline YVec3 RotateAngleAxis(const float AngleDeg, const YVec3& Axis) const;
		inline float Magnitude() const;
		inline float Magnitude2D() const;
		inline float MagnitudeSquared() const;
		inline float MagnitudeSquared2D() const;
		inline void ToDirectionAndLength(YVec3& OUT OutDir, float& OUT OutLength) const;
		inline YQuat ToOrientationQuat() const;
		inline YEuler ToOrientationEuler() const;
		inline YVec2 UnitCartesianToSpherical() const;
		inline YEuler Rotation() const;
		inline void FindBestAxisVectors(const YVec3& OUT Axis1, const YVec3& OUT Axis3) const;

		// Const GET Functions
		inline YVec3 GetAbs() const;
		inline float GetAbsMax() const;
		inline float GetAbsMin() const;
		inline YVec3 GetClampedToMaxSize(float MaxSize) const;
		inline YVec3 GetClampedToMaxSize2D(float MaxSize) const;
		inline YVec3 GetClampedToSize(float Min, float Max) const;
		inline YVec3 GetClampedToSize2D(float Min, float Max) const;
		inline float GetMax() const;
		inline float GetMin() const;
		inline YVec3 GetSafeNormal(float Tolerance) const;
		inline YVec3 GetSafeNormal2D(float Tolerance) const;
		inline YVec3 GetSignVector() const;
		inline YVec3 GetUnsafeNormal() const;
		inline YVec3 GetUnsafeNormal2D() const;

		//Non Const Functions
		inline void AddBounded(const YVec3& V, float Radius);
		inline bool Normalize(float Tolerance);
		inline void Set(float InX, float InY, float InZ);
		inline void UnwindEuler();

		// Static Functions
		static float BoxPushOut(const YVec3& Normal, const YVec3& Size);
		static bool Coincident(const YVec3& Normal1, const YVec3& Normal2, float ParallelCosineThreshold);
		static bool Coplanar(
			const YVec3& Base1, const YVec3& Normal1,
			const YVec3& Base2, const YVec3& Normal2,
			float ParallelCosineThreshold
		);
		static void CreateOrthonormalBasis(
			YVec3& OUT XAxis,
			YVec3& OUT YAxis,
			YVec3& OUT ZAxis
		);
		static YVec3 DegreesToRadians(const YVec3& DegVector);
		static YVec3 RadiansToDegrees(const YVec3& RadVector);
		static float Distance(const YVec3& V1, const YVec3& V2);
		static float Distance2D(const YVec3& V1, const YVec3& V2);
		static float DistanceXY(const YVec3& V1, const YVec3& V2);
		static float DistanceSquared(const YVec3& V1, const YVec3& V2);
		static float DistanceSquared2D(const YVec3& V1, const YVec3& V2);
		static float DistanceSquaredXY(const YVec3& V1, const YVec3& V2);
		static float DotProduct(const YVec3& A, const YVec3& B);
		static YVec3 CrossProduct(const YVec3& A, const YVec3& B);
		//Evaluate bezier
		//Generate cluster centers
		static bool Orthogonal(
			const YVec3& Normal1, 
			const YVec3& Normal2,
			float OrthogonalCosineThreshold
		);
		static bool Parallel(
			const YVec3& Normal1,
			const YVec3& Normal2,
			float ParallelCosineThreshold
		);
		static float PointPlaneDistance(
			const YVec3& Point,
			const YVec3& PlaneBase,
			const YVec3& PlaneNormal
		);
		//counterclockwise
		static YVec3 PointPlaneProject(
			const YVec3& Point,
			const YVec3& A,
			const YVec3& B,
			const YVec3& C
		);
		/*static YVec3 PointPlaneProject(
			const YVec3& Point,
			const YPlane& Plane
		);*/
		static YVec3 PointPlaneProject(
			const YVec3& Point,
			const YVec3& PlaneBase,
			const YVec3& PlaneNormal
		);
		static YVec3 VectorPlaneProject(
			const YVec3& V,
			const YVec3& PlaneNormal
		);
		static bool PointsAreNear(
			const YVec3& Point1,
			const YVec3& Point2,
			float Distance
		);
		static bool PointsAreSame(
			const YVec3& Point1,
			const YVec3& Point2
		);
		static float TripleProduct(
			const YVec3& X, 
			const YVec3& Y,
			const YVec3& Z
		);

		//
		// FUNCTIONS END
		//

		//
		// STATIC VARIABLES START
		//

		static const YVec3 BackVector;
		static const YVec3 FrontVector;
		static const YVec3 LeftVector;
		static const YVec3 RightVector;
		static const YVec3 UpVector;
		static const YVec3 DownVector;
		static const YVec3 XAxis;
		static const YVec3 YAxis;
		static const YVec3 ZAxis;
		static const YVec3 OneVector;
		static const YVec3 ZeroVector;

		//
		// STATIC VARIABLES END
		//

		//
		//Functions START
		//

		//Makes a vector3d 0
		void makeZero();
		// normalizes a vector3d
		void normalize();

		//Functions END
		inline float dot(const YVec3& a) const;

		inline void set(float X, float Y, float Z) {
			X = x;
			Y = y;
			Z = z;
		}
	};
	//
	// Non Member Functions
	//

	//DOT PRODUCT between two vector3ds
	extern inline float dotProduct(const YVec3& a, const YVec3& b);
	//CROSS PRODUCT between two vector3ds
	extern inline YVec3 crossProduct(const YVec3& a, const YVec3& b);
	//Magnitude of a vector3d specified
	extern inline float magnitude(const YVec3& a);
	//Distance between two vector3ds
	extern inline float distance(const YVec3& a, const YVec3& b);
	// Non Member Functions END
}
#pragma once


namespace MathLib {
	// Foward Declarations
	// Vector 2D
	class YVec2;
	// Vector 3D
	class YVec3;
	// Quaternion
	class YQuat;
	// Euler Angles
	class YEuler;
	class YVec4 {
	public:
		float x, y, z, w;
		//
		//CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes x,y,z to 0.0f
		inline YVec4();

		// Constructor - 1 float value
		// Initializes x and y to InFloat
		inline YVec4(float InF);

		// Constructor - 4 float values
		// Initializes x, y, z to InX, InY, InZ
		inline YVec4(float InX, float InY, float InZ, float InW);

		// Constructor - 1 YVec4 reference
		// Initializes x, y, z, w to InVec4.x, InVec4.y, InVec4.z, InVec4.w
		inline YVec4(const YVec4& InVec4);

		// Constructor - 1 YVec3 reference, 1 float
		// Initializes x, y, z to InVec3.x, InVec3.y, InVec3.z, w to InW
		inline YVec4(const YVec3& InVec3, float InW);
		//One For Color

		// Constructor - 1 YVec2 reference, 2 floats
		// Initializes x, y to InVec2.x, InVec2.y, z, w to InZ, InW
		inline YVec4(const YVec2& InXY, const YVec2& InZW);

		//
		// CONSTRUCTOR OVERLOADS END
		//

		//
		// OPERATORS START
		//

		// COMPARISION OPERATORS

		// COMPARISION OPERATORS

		// Operator -> Equality
		inline bool operator==(const YVec4& Other) const;
		// Operator -> Inequality
		inline bool operator!=(const YVec4& Other) const;
		// Operator -> Less than
		inline bool operator<(const YVec4& Other) const;
		// Operator -> Less than or Equal to 
		inline bool operator<=(const YVec4& Other) const;
		// Operator -> Greater than
		inline bool operator>(const YVec4& Other) const;
		// Operator -> Greater than or Equal to 
		inline bool operator>=(const YVec4& Other) const;

		// ARITHMETIC OPERATORS

		// Addition

		// Operator -> this + YVec4 V
		inline YVec4 operator+(const YVec4& V) const;
		// Operator -> this + float A
		inline YVec4 operator+(float A) const;
		// Operator -> this += YVec4 V
		inline YVec4 operator+=(const YVec4& V);
		// Operator -> this += float A
		inline YVec4 operator+=(float A);

		// Subtraction

		// Operator -> Negation
		inline YVec4 operator-() const;
		// Operator -> this - YVec4 V
		inline YVec4 operator-(const YVec4& V) const;
		// Operator -> this - float A
		inline YVec4 operator-(float A) const;
		// Operator -> this -= YVec4 V
		inline YVec4 operator-=(const YVec4& V);
		// Operator -> this -= float A
		inline YVec4 operator-=(float A);

		// Multiplication

		// Operator -> this * YVec4 V
		inline YVec4 operator*(const YVec4& V) const;
		// Operator -> this * A
		inline YVec4 operator*(float A) const;
		// Operator -> V * A (friend)
		//inline friend YVec4 operator*(const YVec4& a, const float& mult);
		// Operator -> A * V (friend)
		inline friend YVec4 operator*(float A, const YVec4& V);
		// Operator -> this *= YVec4 V
		inline YVec4 operator*=(const YVec4& V);
		// Operator -> this *= float A
		inline YVec4 operator*=(float A);

		// Division

		// Operator -> this / YVec4 V
		inline YVec4 operator/(const YVec4& V) const;
		// Operator -> this / float A
		inline YVec4 operator/(float A) const;
		// Operator -> this /= YVec4 V
		inline YVec4 operator/=(const YVec4& V);
		// Operator -> this /= A
		inline YVec4 operator/=(float A);

		// ACCESSING OPERATORS

		// Operator - [] Accessor
		inline float& operator[](unsigned int i) { return (&x)[i]; }
		// Operator - [] Accessor
		inline float operator[](unsigned int i) const { return (&x)[i]; }

		// SPECIAL OPERATORS

		// Operator - Dot Product
		inline float operator|(const YVec4& V) const;
		// Operator - Cross product
		inline YVec4 operator^(const YVec4& V) const;

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		// Const Functions
		inline bool ContainsNaN() const;
		inline bool Equals(const YVec4& V, float Tolerance) const;
		inline void FindBestAxisVectors3(YVec3 &Axis1, YVec3& Axis2) const;
		inline bool IsNearlyZero3(float Tolerance) const;
		inline bool IsUnit3(float LengthSquaredTolerance) const;
		inline YVec4 Reflect3(const YVec4& Normal) const;
		inline YEuler Rotation() const;
		inline float Magnitude() const;
		inline float Magnitude3() const;
		inline float MagnitudeSquared() const;
		inline float MagnitudeSquared3() const;
		inline YQuat ToOrientationQuat() const;
		inline YEuler ToOrientationEuler() const;

		// Const GET Functions
		inline YVec4 GetSafeNormal(float Tolerance) const;
		inline YVec4 GetUnsafeNormal3() const;

		// Non Const Functions
		inline void Set(float InX, float InY, float InZ, float InW);
		//
		// FUNCTIONS END
		//
		
		//Makes a vector3d 0
		void makeZero();
		// normalizes a vector3d
		void normalize();
		//Functions END

		//DOT PRODUCT between two vector3ds
		inline float dot(const YVec4& a) const;
	};
	//
	//Non Member Functions START
	//
	//DOT PRODUCT between two vector3ds
	extern inline float dotProduct(const YVec4& a, const YVec4& b);
	//Magnitude of a vector3d specified
	extern float magnitude(const YVec4& a);
	//Distance between two vector3ds
	extern float distance(const YVec4& a, const YVec4& b);
	//non member functions END
}
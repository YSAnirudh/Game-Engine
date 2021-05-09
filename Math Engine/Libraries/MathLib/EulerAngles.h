#pragma once

namespace MathLib {
	class YMat4x3;
	class YMat4x4;
	class YMat3x3;
	class YQuat;
	class YVec3;
	class YEuler {
	public:
		// Stored in Degrees
		float roll, pitch, yaw;
		// Z, X, Y
		// right, forward, up axis
		// up/down, tilting head cw/ccw, nodding head left right

		//
		// CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes roll, pitch, yaw to 0.0f
		YEuler();

		// Constructor - 1 float value
		// Initializes roll, pitch, yaw to InF
		YEuler(float InF);

		// Constructor - 3 float values
		// Initializes roll, pitch, yaw to InRoll, InPitch, InYaw
		YEuler(float InRoll, float InPitch, float InYaw);

		// Constructor - 1 Euler Angle reference
		// Initializes this to Euler
		YEuler(const YEuler &Euler);

		// Constructor - 1 Quaternion reference
		// Initializes this to Euler Equivalent of Quat
		YEuler(const YQuat &Quat);
		
		//
		// CONSTRUCTOR OVERLOADS END
		//
		
		//
		// OPERATORS START
		//

		// Operator - Assignment
		inline void operator=(const YEuler &Euler);

		// COMPARISION OPERATORS
		
		// Operator -> Equality 
		inline bool operator==(const YEuler &Euler) const;
		// Operator -> Inequality
		inline bool operator!=(const YEuler &Euler) const;

		// ARITHMETIC OPERATORS
		
		// Addition

		// Operator -> this + YEuler Euler
		inline YEuler operator+(const YEuler &Euler) const;
		// Operator -> this += YEuler Euler
		inline YEuler operator+=(const YEuler &Euler);

		// Subtraction

		// Operator -> Negation
		inline YEuler operator-() const;
		// Operator -> this - YEuler Euler
		inline YEuler operator-(const YEuler &Euler) const;
		// Operator -> this -= YEuler Euler
		inline YEuler operator-=(const YEuler &Euler);

		// Multiplication

		// Operator -> this * Scale
		inline YEuler operator*(float Scale) const;
		// Operator -> Scale * this (friend)
		inline friend YEuler operator*(float Scale, const YEuler &Euler);
		// Operator -> this *= Scale
		inline YEuler operator*=(float Scale);

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		//YEuler Add(float Delta);
		inline YEuler Clamp() const;
		inline bool ContainsNaN() const;
		inline bool Equals(const YEuler &Euler, float Tolerance) const;
		inline YVec3 Vector() const;
		inline YEuler GridSnap(const YEuler &RotGrid) const;
		inline bool IsNearlyZero(float Tolerance) const;
		inline bool IsZero() const;
		inline YQuat Quaternion() const;
		inline YVec3 RotateVector(const YVec3 &V) const;
		inline void SetClosestToMe(YEuler &MakeClosest) const;
		inline YVec3 UnRotateVector(const YVec3 &V) const;

		// Const GET Functions
		inline YEuler GetEquivalentEuler() const;
		inline YEuler GetInverse() const;
		inline float GetManhattanDistance(const YEuler& Euler) const;
		inline YEuler GetNormalized() const;
		inline void GetWindingAndRemainder(
			YEuler &Winding,
			YEuler &Remainder) const;

		// Not Const Functions
		inline void Normalize();
		inline void FromRotationMat(YMat3x3 &RotMat);
		inline void FromRotationMat(YMat4x4 &RotMat);

		// Static Functions

		//
		// FUNCTIONS END
		//

		//
		// STATIC VARIABLES START
		//

		static const YEuler ZeroEuler;

		//
		// STATIC VARIABLES END
		//


		

		void canonize();
		void fromInertialToObjectQuat(YQuat &quat);
		void fromObjectToInertialQuat(YQuat &quat);

		void fromWorldToObjectMat(YMat4x3 &mat);
		void fromObjectToWorldMat(YMat4x3 &mat);

		// Functions END
	};

	//
	// Non Member Functions START
	//

	//YEuler

	// Non Member Functions END
}
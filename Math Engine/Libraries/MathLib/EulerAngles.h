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
		void operator=(const YEuler &Euler);

		// COMPARISION OPERATORS
		
		// Operator -> Equality 
		bool operator==(const YEuler &Euler) const;
		// Operator -> Inequality
		bool operator!=(const YEuler &Euler) const;

		// ARITHMETIC OPERATORS
		
		// Addition

		// Operator -> this + YEuler Euler
		YEuler operator+(const YEuler &Euler) const;
		// Operator -> this += YEuler Euler
		YEuler operator+=(const YEuler &Euler);

		// Subtraction

		// Operator -> Negation
		YEuler operator-() const;
		// Operator -> this - YEuler Euler
		YEuler operator-(const YEuler &Euler) const;
		// Operator -> this -= YEuler Euler
		YEuler operator-=(const YEuler &Euler);

		// Multiplication

		// Operator -> this * Scale
		YEuler operator*(float Scale) const;
		// Operator -> Scale * this (friend)
		friend YEuler operator*(float Scale, const YEuler &Euler);
		// Operator -> this *= Scale
		YEuler operator*=(float Scale);

		//
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

		//YEuler Add(float Delta);
		YEuler Clamp() const;
		bool ContainsNaN() const;
		bool Equals(const YEuler &Euler, float Tolerance) const;
		YVec3 Vector() const;
		YEuler GridSnap(const YEuler &RotGrid) const;
		bool IsNearlyZero(float Tolerance) const;
		bool IsZero() const;
		YQuat Quaternion() const;
		YVec3 RotateVector(const YVec3 &V) const;
		void SetClosestToMe(YEuler &MakeClosest) const;
		YVec3 UnRotateVector(const YVec3 &V) const;

		// Const GET Functions
		YEuler GetEquivalentEuler() const;
		YEuler GetInverse() const;
		float GetManhattanDistance(const YEuler& Euler) const;
		YEuler GetNormalized() const;
		void GetWindingAndRemainder(
			YEuler &Winding,
			YEuler &Remainder) const;

		// Not Const Functions
		void Normalize();
		void FromRotationMat(YMat3x3 &RotMat);
		void FromRotationMat(YMat4x4 &RotMat);

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
#pragma once

namespace MathLib {
	class YMat4x3;
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
		// Constructor overloads
		//
		YEuler();
		YEuler(float InF);
		YEuler(float InRoll, float InPitch, float InYaw);
		YEuler(const YEuler& Euler);
		YEuler(const YQuat& Quat);
		//
		// Operators START
		//

		inline void operator=(const YEuler& Euler);

		inline bool operator==(const YEuler& Euler) const;
		inline bool operator!=(const YEuler& Euler) const;

		inline YEuler operator+(const YEuler& Euler) const;
		inline YEuler operator+=(const YEuler& Euler);
		inline YEuler operator-() const;
		inline YEuler operator-(const YEuler& Euler) const;
		inline YEuler operator-=(const YEuler& Euler);

		inline YEuler operator*(float Scale) const;
		inline friend YEuler operator*(float Scale, const YEuler& Euler);
		inline YEuler operator*=(float Scale);

		// Operators END

		//
		// Functions START
		//

		//YEuler Add(float Delta);
		inline YEuler Clamp() const;
		inline bool ContainsNaN() const;
		inline bool Equals(const YEuler& Euler, float Tolerance) const;
		inline YVec3 Vector() const;
		inline YEuler GetEuquivalentEuler() const;
		inline YEuler GetInverse() const;
		inline float GetManhattanDistance() const;
		inline YEuler GetNormalized() const;
		inline void GetWindingAndRemainder(
			YEuler& Winding,
			YEuler& Remainder
		) const;
		inline YEuler GridSnap(const YEuler& RotGrid) const;
		inline bool IsNearlyZero(float Tolerance) const;
		inline bool IsZero() const;
		inline void Normalize() const;
		inline YQuat Quaternion() const;
		inline YVec3 RotateVector(const YVec3& V) const;
		inline void SetClosestToMe(YEuler& MakeClosest) const;
		inline YVec3 UnRotateVector(const YVec3& V) const;
		inline void FromRotationMat(YMat3x3& RotMat);

		static inline float ClampAxis(float Angle);
		static inline float NormalizeAxis(float Angle);

		static const YEuler ZeroEuler;
		


		void canonize();
		void fromInertialToObjectQuat(YQuat& quat);
		void fromObjectToInertialQuat(YQuat& quat);

		void fromWorldToObjectMat(YMat4x3& mat);
		void fromObjectToWorldMat(YMat4x3& mat);


		// Functions END
	};

	//
	// Non Member Functions START
	//
	
	//YEuler 

	// Non Member Functions END
}
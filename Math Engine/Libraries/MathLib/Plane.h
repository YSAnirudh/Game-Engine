#pragma once
#include "Vector3D.h"
namespace MathLib {
    class YQuat;
    class YMat3x3;
    class YMat4x4;
    class YVec3;
    class YVec4;
	class YPlane {
    public:
        float offset;
        class YVec3 normal;
        //
		// CONSTRUCTOR OVERLOADS START
		//

        // Constructor - Empty
		// Initializes normal to Up Vector and offset to 0
        YPlane();

        // Constructor - 1 YVec3 and 1 float
		// Initializes normal to Normal and offset to Offset
        YPlane(const YVec3& Normal, float Offset);

        // Constructor - 2 YVec3
		// Initializes normal to InNormal and 
        // offset to distance between origin and plane 
        // using InPoint and InNormal to calculate
        YPlane(const YVec3& InPoint, const YVec3& InNormal);

        // Constructor - 4 float values
		// Initializes normal and offset from InX, InY, InZ, InW
        YPlane(float InX, float InY, float InZ, float InW);

        // Constructor - 1 YVec4
		// Initializes normal and offset from V.x, V.y, V.z, V.w
        YPlane(const YVec4& V);
        
        // Constructor - 1 YPlane
		// Initializes normal to Other.normal and offset to Other.offset
        YPlane(const YPlane& Other);
        //YPlane(YVec3 A, YVec3 C, YVec3 C);

        //
		// CONSTRUCTOR OVERLOADS END
		//
		
		//
		// OPERATORS START
		//

        // Operator - Assignment
        void operator=(const YPlane& Plane);

        // COMPARISION OPERATORS
		
		// Operator -> Equality
        bool operator==(const YPlane& Plane) const;
        // Operator -> Inequality
        bool operator!=(const YPlane& Plane) const;

        // ARITHMETIC OPERATORS
		
		// Addition

        // Operator -> this + YPlane Plane
        YPlane operator+(const YPlane& Plane) const;
        // Operator -> this += YPlane Plane
        YPlane operator+=(const YPlane& Plane);

        // Subtraction

        // Operator -> this - YPlane Plane
        YPlane operator-(const YPlane& Plane) const;
        // Operator -> this -= YPlane Plane
        YPlane operator-=(const YPlane& Plane);

        // Multiplication

        // Operator -> this * YPlane Plane
        YPlane operator*(const YPlane& Plane) const;
        // Operator -> this *= YPlane Plane
        YPlane operator*=(const YPlane& Plane) const;
        // Operator -> this * Scale
        YPlane operator*(float Scale) const;
        // Operator -> Scale * this (friend)
        friend YPlane operator*(float Scale, const YPlane& Plane);
        // Operator -> this *= Scale
        YPlane operator*=(float Scale);

        // Division

        // Operator -> this / Scale
        YPlane operator/(float Scale) const;
        // Operator -> this /= Scale
        YPlane operator/=(float Scale);

        // SPECIAL OPERATORS

        // Operator - Dot Product
        float operator|(const YPlane& Plane) const;
        
        //
		// OPERATORS END
		//

		//
		// FUNCTIONS START
		//

        // Const Functions
        YVec3 ClosestPoint(const YVec3& point) const;
        bool Equals(const YPlane& Plane, float Tolerance) const;
        YPlane Flip() const;
        bool IsValid() const;
        float PlaneDot(const YVec3& V) const;
        YPlane TransformBy(const YMat4x4& M) const;
        YPlane TransformBy(const YQuat& Quat) const;
        YPlane TransformBy(
            float scale, 
            const YQuat& rotation,
            const YVec3& translation
        ) const;
        // Const GET Functions
        YVec3 GetNormal() const;
        YVec3 GetOrigin() const;

        // Non Const Functions
        bool Normalize(float Tolerance);
	};
}
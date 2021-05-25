#pragma once
#include "Plane.h"
#include "GenMath.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Vector4D.h"
#include "Matrix4x4.h"
namespace MathLib {
    //
	// STATIC VARIABLE DECLARATIONS
	//

    //
	// CONSTRUCTORS START
	//
    YPlane::YPlane() :
        normal(YVec3(1.0f, 0.0f, 0.0f)),
        offset(0.0f)
    {}

    YPlane::YPlane(float InX, float InY, float InZ, float InW) {
        float lensq = InX * InX + InY * InY + InZ * InZ;
        
        assert(!YMath::IsZero(lensq));

        if (YMath::IsZero(lensq))
        {
            normal = YVec3(1.0f, 0.0f, 0.0f);// IvVector3::xAxis;
            offset = 0.0f;
        }
        else
        {
            normal = YVec3(1.0f, 0.0f, 0.0f);
            offset = InW / YMath::Sqrt(lensq);
        }
    }

    /*YPlane::YPlane(const YVec3& p0, const YVec3& p1, const YVec3& p2)
    {
        set(p0, p1, p2);

    }*/

    YPlane::YPlane(const YPlane& other) :
        normal(other.normal),
        offset(other.offset)
    {}
    
    YPlane::YPlane(const YVec3& Normal, float Offset) :normal(Normal), offset(Offset) {}
    
    YPlane::YPlane(const YVec3& InPoint, const YVec3& InNormal) {
        
    }
    
    YPlane::YPlane(const YVec4& V) {
        float lensq = V.x * V.x + V.y * V.y + V.z * V.z;
        
        assert(!YMath::IsZero(lensq));

        if (YMath::IsZero(lensq))
        {
            normal = YVec3(1.0f, 0.0f, 0.0f);// IvVector3::xAxis;
            offset = 0.0f;
        }
        else
        {
            normal = YVec3(1.0f, 0.0f, 0.0f);
            offset = V.w / YMath::Sqrt(lensq);
        }
    }
    //
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//

    // Assignment -> Assigns the values of Plane to this
    void YPlane::operator=(const YPlane& Plane) {
        normal = Plane.normal;
        offset = Plane.offset;
    }

    //Equality -> Returns true if this and Plane are equal (Both normal and offset)
    bool YPlane::operator==(const YPlane& Plane) const {
        return (Plane.normal == normal && YMath::AreEqual(Plane.offset, offset));
    }

    //Inequality -> Returns true if this and Plane are not equal (Either normal and offset)
    bool YPlane::operator!=(const YPlane& Plane) const {
        return !(Plane.normal == normal && YMath::AreEqual(Plane.offset, offset));
    }
    
    // this + YPlane -> Adds the values of Plane to this
    YPlane YPlane::operator+(const YPlane& Plane) const {
        return YPlane(normal + Plane.normal, offset + Plane.offset);
    }

    // this += YPlane -> Adds the values of Plane to this and stores in this
    YPlane YPlane::operator+=(const YPlane& Plane)  {
        return (*this) + Plane;
    }
    
    // this - YPlane -> Subtracts the values of Plane from this
    YPlane YPlane::operator-(const YPlane& Plane) const {
        return YPlane(normal - Plane.normal, offset - Plane.offset);
    }
    
    // this -= YPlane -> Subtracts the values of Plane from this and stores in this
    YPlane YPlane::operator-=(const YPlane& Plane) {
        return (*this) - Plane;
    }
    
    // this * YPlane -> Multiplies the values of Plane to this
    YPlane YPlane::operator*(const YPlane& Plane) const {
        return YPlane();
    }
    
    // this *= YPlane -> Multiplies the values of Plane to this and stores in this
    YPlane YPlane::operator*=(const YPlane& Plane) const {
        return YPlane();
    }
    
    // this * Scale -> Multiplies Scale to this
    YPlane YPlane::operator*(float Scale) const {
       return YPlane(normal * Scale, offset * Scale);
    }
    YPlane operator*(float Scale, const YPlane& Plane) {
        return Plane * Scale;
    }
    
    // this *= Scale -> Multiplies Scale to this and stores in this
    YPlane YPlane::operator*=(float Scale) {
        return (*this) * Scale;
        
    }
    
    // this / Scale -> Multiplies this by Scale
    YPlane YPlane::operator/(float Scale) const {
        Scale = 1/ Scale;
        return YPlane(normal * Scale, offset * Scale);
    }
    
    // this /= Scale -> Multiplies this by Scale and stores in this
    YPlane YPlane::operator/=(float Scale) {
        return (*this) / Scale;
    }
    
    // Dot Product -> Calculates the Dot Product between this and Plane
    float YPlane::operator|(const YPlane& Plane) const {
        return 0.0f;
    }

    // 
	// OPERATORS END
	//

	//
	// FUNCTIONS START
	//

    // Returns the YVec3 that is the closest point on the plane from Point
    YVec3 YPlane::ClosestPoint(const YVec3& Point) const {
        return Point - (normal|(Point) + offset) * normal;
    }
    
    // Returns true if this and Plane are equal with some Tolerance
    bool YPlane::Equals(const YPlane& Plane, float Tolerance) const {
        if (normal.Equals(Plane.normal, Tolerance) && 
            YMath::AreNearlyEqual(offset, Plane.offset, Tolerance)
        ) {
            return true;
        }
        return false;
    }
    
    // Flips the normal of this (i.e. reverses the direction of this' normal)
    YPlane YPlane::Flip() const {
        return YPlane(-normal, offset);
    }
    
    // Returns true if this' normal is not a zero vector
    bool YPlane::IsValid() const {
        if (!YMath::IsZero(normal.MagnitudeSquared())) {
            return false;
        }
        return true;
    }
    
    // Returns the distance from the Plane to V
    float YPlane::PlaneDot(const YVec3& V) const {
        return 0.0f;
    }
    
    // Return a copy of this after being transformed by M
    YPlane YPlane::TransformBy(const YMat4x4& M) const {
        return YPlane();
    }
    
    // Return a copy of this after being transformed by Quat
    YPlane YPlane::TransformBy(const YQuat& Quat) const {
        return YPlane();
    }

    // Return a copy of this after being transformed by rotate and removing scale
    YPlane YPlane::TransformBy(float scale, const YQuat& rotate, const YVec3& translate) const {
        YPlane plane;

        // get rotation matrix
        YMat3x3 rotmatrix;
        rotmatrix.SetupRotation(rotate);// (rotate);

        // transform to get normal
        plane.normal = rotmatrix * normal / scale;

        // transform to get offset
        YVec3 newTrans = translate * rotmatrix;
        plane.offset = -newTrans|(normal) / scale + offset;

        return plane;
    }

    // Gets the normal of this Plane
    YVec3 YPlane::GetNormal() const {
        return normal;
    }
    
    // Gets the origin of the Plane
    YVec3 YPlane::GetOrigin() const {
        YVec3 temp = normal.GetSafeNormal(yEpsilon);
        return temp * offset;
    }
    
    // Normalizes the Plane within some Tolerance
    bool YPlane::Normalize(float Tolerance) 
    {
        return false;
    }
}
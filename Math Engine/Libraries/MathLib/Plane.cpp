#include "Plane.h"
#include "Vector3D.h"
#include "GenMath.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
#include "Vector4D.h"
#include "Matrix4x4.h"
namespace MathLib {
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

    bool YPlane::operator==(const YPlane& Plane) const {
        return (Plane.normal == normal && YMath::AreEqual(Plane.offset, offset));
    }

    bool YPlane::operator!=(const YPlane& Plane) const {
        return !(Plane.normal == normal && YMath::AreEqual(Plane.offset, offset));
    }
    
    inline YPlane YPlane::operator+(const YPlane& Plane) const {
        return YPlane(normal + Plane.normal, offset + Plane.offset);
    }

    inline YPlane YPlane::operator+=(const YPlane& Plane)  {
        return (*this) + Plane;
    }
    
    inline YPlane YPlane::operator-(const YPlane& Plane) const {
        return YPlane(normal - Plane.normal, offset - Plane.offset);
    }
    
    inline YPlane YPlane::operator-=(const YPlane& Plane) {
        return (*this) - Plane;
    }
    
    inline YPlane YPlane::operator*(const YPlane& Plane) const {
        
    }
    
    inline YPlane YPlane::operator*=(const YPlane& Plane) const {
        
    }
    
    inline YPlane YPlane::operator*(float Scale) const {
       return YPlane(normal * Scale, offset * Scale);
    }
    
    inline YPlane operator*(float Scale, const YPlane& Plane) {
        return Plane * Scale;
    }
    
    inline YPlane YPlane::operator*=(float Scale) {
        return (*this) * Scale;
        
    }
    
    inline YPlane YPlane::operator/(float Scale) const {
        Scale = 1/ Scale;
        return YPlane(normal * Scale, offset * Scale);
    }
    
    inline YPlane YPlane::operator/=(float Scale) {
        return (*this) / Scale;
    }
    
    inline float YPlane::operator|(const YPlane& Plane) const {
        
    }

    inline YVec3 YPlane::ClosestPoint(const YVec3& point) const {
        return point - (normal.dot(point) + offset) * normal;
    }
    
    inline bool YPlane::Equals(const YPlane& Plane, float Tolerance) const {
        if (normal.Equals(Plane.normal, Tolerance) && 
            YMath::AreNearlyEqual(offset, Plane.offset, Tolerance)
        ) {
            return true;
        }
        return false;
    }
    
    inline YPlane YPlane::Flip() const {
        return YPlane(-normal, offset);
    }
    
    inline YVec3 YPlane::GetNormal() const {
        return normal;
    }
    
    inline YVec3 YPlane::GetOrigin() const {
        YVec3 temp = normal.GetSafeNormal();
        return temp * offset;
    }
    
    inline bool YPlane::IsValid() const {
        if (!YMath::IsZero(normal.MagnitudeSquared())) {
            return false;
        }
        return true;
    }
    
    inline float YPlane::PlaneDot(const YVec3& V) const {
        
    }
    
    inline YPlane YPlane::TransformBy(const YMat4x4& M) const {
        
    }
    
    inline YPlane YPlane::TransformBy(const YQuat& Quat) const {
        
    }

    inline YPlane YPlane::TransformBy(float scale, const YQuat& rotate, const YVec3& translate) const {
        YPlane plane;

        // get rotation matrix
        YMat3x3 rotmatrix;// (rotate);

        // transform to get normal
        plane.normal = rotmatrix * normal / scale;

        // transform to get offset
        YVec3 newTrans = translate * rotmatrix;
        plane.offset = -newTrans.dot(normal) / scale + offset;

        return plane;
    }

    
    inline bool YPlane::Normalize(float Tolerance) 
    {
        
    }
}
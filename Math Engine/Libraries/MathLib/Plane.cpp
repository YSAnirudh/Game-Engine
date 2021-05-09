#include "Plane.h"
#include "Vector3D.h"
#include "GenMath.h"
#include "Quaternion.h"
#include "Matrix3x3.h"
namespace MathLib {
    YPlane::YPlane() :
        normal(YVec3(1.0f, 0.0f, 0.0f)),
        offset(0.0f)
    {}

    YPlane::YPlane(float a, float b, float c, float d) {
        float lensq = a * a + b * b + c * c;
        // length of normal had better not be zero
        assert(!IsZero(lensq));

        // recover gracefully
        if (IsZero(lensq))
        {
            normal = YVec3(1.0f, 0.0f, 0.0f);// IvVector3::xAxis;
            offset = 0.0f;
        }
        else
        {
            float recip = 1/Sqrt(lensq);
            normal = YVec3(1.0f, 0.0f, 0.0f);
            offset = d * recip;
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

    bool YPlane::operator==(const YPlane& Plane) const {
        return (Plane.normal == normal && YMath::AreEqual(Plane.offset, offset));
    }

    bool YPlane::operator!=(const YPlane& Plane) const {
        return !(Plane.normal == normal && YMath::AreEqual(Plane.offset, offset));
    }

    YPlane YPlane::Transform(float scale, const YQuat& rotate, const YVec3& translate) const {
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

    YVec3 YPlane::ClosestPoint(const YVec3& point) const {
        return point - Test(point) * normal;
    }
}
#pragma once


namespace MathLib {
    class YVec3;
    class YQuat;
    class YMat3x3;
	class YPlane {
    public:
        YVec3 normal;
        float offset;
        YPlane();
        YPlane(const YVec3& Normal, float Offset);
        YPlane(float a, float b, float c, float d);
        //YPlane(const YVec3& p0, const YVec3& p1, const YVec3& p2);

        // copy operations
        YPlane(const YPlane& other);

        bool operator==(const YPlane& Plane) const;
        bool operator!=(const YPlane& Plane) const;

        YPlane Transform(float scale, const YQuat& rotation,
            const YVec3& translation) const;

        // distance
        inline friend float Distance(const YPlane& plane, const YVec3& point) {
            return YMath::Abs(plane.Test(point));
        }

        // closest point
        YVec3 ClosestPoint(const YVec3& point) const;

        // result of plane test
        inline float Test(const YVec3& point) const
        {
            return normal.dot(point) + offset;
        }
	};
}
#pragma once

#include "Quaternion.h"
namespace MathLib {
    class YVec3;
	class YPlane {
    public:
        YVec3 normal;
        float offset;
        YPlane();
        YPlane(float a, float b, float c, float d);
        //YPlane(const YVec3& p0, const YVec3& p1, const YVec3& p2);
        inline ~YPlane() {}

        // copy operations
        YPlane(const YPlane& other);

        bool operator==(const YPlane& ray) const;
        bool operator!=(const YPlane& ray) const;

        void set(float a, float b, float c, float d);

        YPlane transform(float scale, const YQuat& rotation,
            const YVec3& translation) const;

        // distance
        inline friend float Distance(const YPlane& plane, const YVec3& point)
        {
            return abs(plane.Test(point));
        }

        // closest point
        YVec3 closestPoint(const YVec3& point) const;

        // result of plane test
        inline float Test(const YVec3& point) const
        {
            return normal.dot(point) + offset;
        }
	};
}
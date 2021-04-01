#pragma once

#include "Matrix3x3.h"
#include "Line3D.h"
namespace MathLib {
    class YVec3;
	class YRay3 {
    public:
		YVec3 origin;
		YVec3 direction;

        YRay3();
        YRay3(const YVec3& origin, const YVec3& direction);
        YRay3(const YRay3& other);

		bool operator==(const YRay3& ray) const;
		bool operator!=(const YRay3& ray) const;

        YRay3 transform(float scale, const YQuat& rotation,
            const YVec3& translation) const;
        YRay3 transform(float scale, const YMat3x3& rotation,
            const YVec3& translation) const;

        // distance
        friend float distanceSquared(const YRay3& ray0, const YRay3& ray1,
            float& s_c, float& t_c);
        friend float distanceSquared(const YRay3& ray, const YLine3& line,
            float& s_c, float& t_c);
        inline friend float distanceSquared(const YLine3& line, const YRay3& ray,
            float& s_c, float& t_c)
        {
            return distanceSquared(ray, line, t_c, s_c);
        }
        friend float distanceSquared(const YRay3& ray, const YVec3& point,
            float& t_c);

        // closest points
        friend void closestPoints(YVec3& point0, YVec3& point1,
            const YRay3& ray0,
            const YRay3& ray1);
        friend void closestPoints(YVec3& point0, YVec3& point1,
            const YRay3& ray,
            const YLine3& line);
        YVec3 closestPoint(const YVec3& point) const;
	};
}
#pragma once
#include "Vector3D.h"
#include "Matrix3x3.h"
#include "Line3D.h"
#include "Ray3D.h"
namespace YSAoo {
    class YVec3;
    class YLineSeg3;
    float distanceSquared(const YLineSeg3& seg0, const YLineSeg3& seg1,
        float& s_c, float& t_c);
    float distanceSquared(const YLineSeg3& segment, const YRay3& ray,
        float& s_c, float& t_c);
    float distanceSquared(const YLineSeg3& segment, const YLine3& line,
        float& s_c, float& t_c);
    class YVec3;
    class YMat3x3;
    class YQuat;
    class YLine3;
	class YLineSeg3 {
	public:
		YVec3 origin;
		YVec3 direction;

        YLineSeg3();
        YLineSeg3(const YVec3& endpoint0, const YVec3& endpoint1);
        YLineSeg3(const YLineSeg3& other);

        /*float Length() const;
        float LengthSquared() const;*/

        // comparison
        bool operator==(const YLineSeg3& segment) const;
        bool operator!=(const YLineSeg3& segment) const;

        YLineSeg3 transform(float scale, const YQuat& rotation,
            const YVec3& translation) const;
        YLineSeg3 transform(float scale, const YMat3x3& rotation,
            const YVec3& translation) const;

        // distance
        friend float distanceSquared(const YLineSeg3& segment0,
            const YLineSeg3& segment1,
            float& s_c, float& t_c);
        friend float distanceSquared(const YLineSeg3& segment,
            const YRay3& ray,
            float& s_c, float& t_c);
        inline friend float DistanceSquared(const YRay3& ray,
            const YLineSeg3& segment,
            float& s_c, float& t_c)
        {
            return distanceSquared(segment, ray, t_c, s_c);
        }
        friend float distanceSquared(const YLineSeg3& segment,
            const YLine3& line,
            float& s_c, float& t_c);
        inline friend float distanceSquared(const YLine3& line,
            const YLineSeg3& segment,
            float& s_c, float& t_c)
        {
            return distanceSquared(segment, line, t_c, s_c);
        }
        friend float distanceSquared(const YLineSeg3& segment,
            const YVec3& point,
            float& t_c);

        // closest points
        friend void closestPoints(YVec3& point0, YVec3& point1,
            const YLineSeg3& segment0,
            const YLineSeg3& segment1);
        friend void closestPoints(YVec3& point0, YVec3& point1,
            const YLineSeg3& segment,
            const YRay3& ray);
        friend void closestPoints(YVec3& point0, YVec3& point1,
            const YLineSeg3& segment,
            const YLine3& line);
        YVec3 closestPoint(const YVec3& point) const;
	};
}
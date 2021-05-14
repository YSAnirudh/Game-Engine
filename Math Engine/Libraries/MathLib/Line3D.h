#pragma once
#include "Vector3D.h"
#include "GenMath.h"
namespace MathLib {
    class YVec3;
    class YQuat;
    class YMat3x3;
	class YLine3 {
	public:
		YVec3 origin, direction;
		YLine3();
        YLine3(const YVec3& origin, const YVec3& direction);
        YLine3(const YLine3& other);

		bool operator==(const YLine3& line) const;
		bool operator!=(const YLine3& line) const;

        YLine3 transform(float scale, const YQuat& rotation,
            const YVec3& translation) const;
        YLine3 transform(float scale, const YMat3x3& rotation,
            const YVec3& translation) const;

        // distance
        friend float distanceSquared(const YLine3& line0, const YLine3& line1,
            float& s_c, float& t_c);
        inline friend float distance(const YLine3& line0, const YLine3& line1,
            float& s_c, float& t_c)
        {
            return Sqrt(distanceSquared(line0, line1, s_c, t_c));
        }
        friend float distanceSquared(const YLine3& line, const YVec3& point,
            float& t_c);
        inline friend  float distance(const YLine3& line, const YVec3& point,
            float& t_c)
        {
            return Sqrt(distanceSquared(line, point, t_c));
        }

        // closest points
        friend void closestPoints(YVec3& point0, YVec3& point1,
            const YLine3& line0,
            const YLine3& line1);
        YVec3 closestPoint(const YVec3& point) const;
	};
}
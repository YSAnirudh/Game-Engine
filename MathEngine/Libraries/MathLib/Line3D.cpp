#include "Line3D.h"
#include "Matrix3x3.h"
#include "Quaternion.h"
namespace YSAoo {
    YLine3::YLine3() :
        origin(0.0f, 0.0f, 0.0f),
        direction(1.0f, 0.0f, 0.0f)
    {
    }
    //Change vector to not change init vector in normalize
    YLine3::YLine3(const YVec3& origin, const YVec3& mdirection) :
        origin(origin),
        direction(mdirection)
    {
        direction.normalize();

    }

    YLine3::YLine3(const YLine3& other) :
        origin(other.origin),
        direction(other.direction)
    {
        direction.normalize();
    }

	bool YLine3::operator==(const YLine3& ray) const
	{
		return (ray.origin == origin && ray.direction == direction);
	}

	bool YLine3::operator!=(const YLine3& ray) const
	{
		return !(ray.origin == origin && ray.direction == direction);
	}

    YLine3 YLine3::transform(float scale, const YQuat& quat, const YVec3& translate) const
    {
        YLine3 line;
        YMat3x3 rotate;// (quat);

        line.direction = rotate * direction;
        line.direction *= scale;

        line.origin = rotate * origin;
        line.origin *= scale;
        line.origin += translate;

        return line;

    }

    YLine3 YLine3::transform(float scale, const YMat3x3& rotate, const YVec3& translate) const
    {
        YLine3 line;

        line.direction = rotate * direction;
        line.direction *= scale;

        line.origin = rotate * origin;
        line.origin *= scale;
        line.origin += translate;

        return line;

    }

    float distanceSquared(const YLine3& line0, const YLine3& line1,
        float& s_c, float& t_c)
    {
        YVec3 w0 = line0.origin - line1.origin;
        float a = line0.direction.dot(line0.direction);
        float b = line0.direction.dot(line1.direction);
        float c = line1.direction.dot(line1.direction);
        float d = line0.direction.dot(w0);
        float e = line1.direction.dot(w0);
        float denom = a * c - b * b;
        if (IsZero(denom))
        {
            s_c = 0.0f;
            t_c = e / c;
            YVec3 wc = w0 - t_c * line1.direction;
            return wc.dot(wc);
        }
        else
        {
            s_c = ((b * e - c * d) / denom);
            t_c = ((a * e - b * d) / denom);
            YVec3 wc = w0 + s_c * line0.direction
                - t_c * line1.direction;
            return wc.dot(wc);
        }

    }

    float distanceSquared(const YLine3& line, const YVec3& point, float& t_c)
    {
        YVec3 w = point - line.origin;
        float vsq = line.direction.dot(line.direction);
        float proj = w.dot(line.direction);
        t_c = proj / vsq;

        return w.dot(w) - t_c * proj;

    }

    void closestPoints(YVec3& point0, YVec3& point1,
        const YLine3& line0,
        const YLine3& line1)
    {
        // compute intermediate parameters
        YVec3 w0 = line0.origin - line1.origin;
        float a = line0.direction.dot(line0.direction);
        float b = line0.direction.dot(line1.direction);
        float c = line1.direction.dot(line1.direction);
        float d = line0.direction.dot(w0);
        float e = line1.direction.dot(w0);

        float denom = a * c - b * b;

        if (IsZero(denom))
        {
            point0 = line0.origin;
            point1 = line1.origin + (e / c) * line1.direction;
        }
        else
        {
            point0 = line0.origin + ((b * e - c * d) / denom) * line0.direction;
            point1 = line1.origin + ((a * e - b * d) / denom) * line1.direction;
        }

    }

    YVec3 YLine3::closestPoint(const YVec3& point) const
    {
        YVec3 w = point - origin;
        float vsq = direction.dot(direction);
        float proj = w.dot(direction);

        return origin + (proj / vsq) * direction;

    }
}
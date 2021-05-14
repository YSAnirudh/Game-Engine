#include "LineSegment3D.h"

namespace MathLib {

    YLineSeg3::YLineSeg3() :
        origin(0.0f, 0.0f, 0.0f),
        direction(1.0f, 0.0f, 0.0f)
    {
    }
    YLineSeg3::YLineSeg3(const YVec3& endpoint0, const YVec3& endpoint1) :
        origin(endpoint0),
        direction(endpoint1 - endpoint0)
    {
    }
    YLineSeg3::YLineSeg3(const YLineSeg3& other) :
        origin(other.origin),
        direction(other.direction)
    {
    }
    //YLineSeg3&
    //    YLineSeg3::operator=(const YLineSeg3& other)
    //{
    //    // if same object
    //    if (this == &other)
    //        return *this;

    //    origin = other.origin;
    //    direction = other.direction;

    //    return *this;

    //}
    /*float
        YLineSeg3::Length() const
    {
        return direction.Length();

    }
    float
        YLineSeg3::LengthSquared() const
    {
        return direction.LengthSquared();

    }*/
    bool
        YLineSeg3::operator==(const YLineSeg3& segment) const
    {
        return ((segment.origin == origin && segment.direction == direction) ||
            (segment.origin == origin + direction && segment.direction == -direction));

    }
    bool
        YLineSeg3::operator!=(const YLineSeg3& segment) const
    {
        return !((segment.origin == origin && segment.direction == direction) ||
            (segment.origin == origin + direction && segment.direction == -direction));
    }
    YLineSeg3
        YLineSeg3::transform(float scale, const YQuat& quat, const YVec3& translate) const
    {
        YLineSeg3 segment;

        YMat3x3 rotate;// (quat);

        segment.direction = rotate * direction;
        segment.direction *= scale;

        segment.origin = rotate * origin;
        segment.origin *= scale;
        segment.origin += translate;

        return segment;

    }
    YLineSeg3
        YLineSeg3::transform(float scale, const YMat3x3& rotate,
            const YVec3& translate) const
    {
        YLineSeg3 segment;

        segment.direction = rotate * direction;
        segment.direction *= scale;

        segment.origin = rotate * origin;
        segment.origin *= scale;
        segment.origin += translate;

        return segment;

    }
    float
        distanceSquared(const YLineSeg3& segment0, const YLineSeg3& segment1,
            float& s_c, float& t_c)
    {
        // compute intermediate parameters
        YVec3 w0 = segment0.origin - segment1.origin;
        float a = segment0.direction.dot(segment0.direction);
        float b = segment0.direction.dot(segment1.direction);
        float c = segment1.direction.dot(segment1.direction);
        float d = segment0.direction.dot(w0);
        float e = segment1.direction.dot(w0);

        float denom = a * c - b * b;
        // parameters to compute s_c, t_c
        float sn, sd, tn, td;

        // if denom is zero, try finding closest point on segment1 to origin0
        if (IsZero(denom))
        {
            // clamp s_c to 0
            sd = td = c;
            sn = 0.0f;
            tn = e;
        }
        else
        {
            // clamp s_c within [0,1]
            sd = td = denom;
            sn = b * e - c * d;
            tn = a * e - b * d;

            // clamp s_c to 0
            if (sn < 0.0f)
            {
                sn = 0.0f;
                tn = e;
                td = c;
            }
            // clamp s_c to 1
            else if (sn > sd)
            {
                sn = sd;
                tn = e + b;
                td = c;
            }
        }

        // clamp t_c within [0,1]
        // clamp t_c to 0
        if (tn < 0.0f)
        {
            t_c = 0.0f;
            // clamp s_c to 0
            if (-d < 0.0f)
            {
                s_c = 0.0f;
            }
            // clamp s_c to 1
            else if (-d > a)
            {
                s_c = 1.0f;
            }
            else
            {
                s_c = -d / a;
            }
        }
        // clamp t_c to 1
        else if (tn > td)
        {
            t_c = 1.0f;
            // clamp s_c to 0
            if ((-d + b) < 0.0f)
            {
                s_c = 0.0f;
            }
            // clamp s_c to 1
            else if ((-d + b) > a)
            {
                s_c = 1.0f;
            }
            else
            {
                s_c = (-d + b) / a;
            }
        }
        else
        {
            t_c = tn / td;
            s_c = sn / sd;
        }

        // compute difference vector and distance squared
        YVec3 wc = w0 + s_c * segment0.direction - t_c * segment1.direction;
        return wc.dot(wc);

    }
    float
        distanceSquared(const YLineSeg3& segment, const YRay3& ray,
            float& s_c, float& t_c)
    {
        // compute intermediate parameters
        YVec3 w0 = segment.origin - ray.origin;
        float a = segment.direction.dot(segment.direction);
        float b = segment.direction.dot(ray.direction);
        float c = ray.direction.dot(ray.direction);
        float d = segment.direction.dot(w0);
        float e = ray.direction.dot(w0);

        float denom = a * c - b * b;
        // parameters to compute s_c, t_c
        float sn, sd, tn, td;

        // if denom is zero, try finding closest point on segment1 to origin0
        if (IsZero(denom))
        {
            // clamp s_c to 0
            sd = td = c;
            sn = 0.0f;
            tn = e;
        }
        else
        {
            // clamp s_c within [0,1]
            sd = td = denom;
            sn = b * e - c * d;
            tn = a * e - b * d;

            // clamp s_c to 0
            if (sn < 0.0f)
            {
                sn = 0.0f;
                tn = e;
                td = c;
            }
            // clamp s_c to 1
            else if (sn > sd)
            {
                sn = sd;
                tn = e + b;
                td = c;
            }
        }

        // clamp t_c within [0,+inf]
        // clamp t_c to 0
        if (tn < 0.0f)
        {
            t_c = 0.0f;
            // clamp s_c to 0
            if (-d < 0.0f)
            {
                s_c = 0.0f;
            }
            // clamp s_c to 1
            else if (-d > a)
            {
                s_c = 1.0f;
            }
            else
            {
                s_c = -d / a;
            }
        }
        else
        {
            t_c = tn / td;
            s_c = sn / sd;
        }

        // compute difference vector and distance squared
        YVec3 wc = w0 + s_c * segment.direction - t_c * ray.direction;
        return wc.dot(wc);

    }
    float
        distanceSquared(const YLineSeg3& segment, const YLine3& line,
            float& s_c, float& t_c)
    {
        // compute intermediate parameters
        YVec3 w0 = segment.origin - line.origin;// .GetOrigin();
        float a = segment.direction.dot(segment.direction);
        float b = segment.direction.dot(line.direction);// .GetDirection());
        float c = line.direction.dot(line.direction);// .GetDirection());
        float d = segment.direction.dot(w0);
        float e = line.direction.dot(w0);// .GetDirection().dot(w0);

        float denom = a * c - b * b;

        // if denom is zero, try finding closest point on segment1 to origin0
        if (IsZero(denom))
        {
            s_c = 0.0f;
            t_c = e / c;
            // compute difference vector and distance squared
            YVec3 wc = w0 - t_c * line.direction;// .GetDirection();
            return wc.dot(wc);
        }
        else
        {
            // parameters to compute s_c, t_c
            float sn;

            // clamp s_c within [0,1]
            sn = b * e - c * d;

            // clamp s_c to 0
            if (sn < 0.0f)
            {
                s_c = 0.0f;
                t_c = e / c;
            }
            // clamp s_c to 1
            else if (sn > denom)
            {
                s_c = 1.0f;
                t_c = (e + b) / c;
            }
            else
            {
                s_c = sn / denom;
                t_c = (a * e - b * d) / denom;
            }

            // compute difference vector and distance squared
            YVec3 wc = w0 + s_c * segment.direction - t_c * line.direction;// .GetDirection();
            return wc.dot(wc);
        }

    }
    float
        distanceSquared(const YLineSeg3& segment, const YVec3& point,
            float& t_c)
    {
        YVec3 w = point - segment.origin;
        float proj = w.dot(segment.direction);
        // endpoint 0 is closest point
        if (proj <= 0)
        {
            t_c = 0.0f;
            return w.dot(w);
        }
        else
        {
            float vsq = segment.direction.dot(segment.direction);
            // endpoint 1 is closest point
            if (proj >= vsq)
            {
                t_c = 1.0f;
                return w.dot(w) - 2.0f * proj + vsq;
            }
            // otherwise somewhere else in segment
            else
            {
                t_c = proj / vsq;
                return w.dot(w) - t_c * proj;
            }
        }

    }
    void closestPoints(YVec3& point0, YVec3& point1,
        const YLineSeg3& segment0,
        const YLineSeg3& segment1)
    {
        // compute intermediate parameters
        YVec3 w0 = segment0.origin - segment1.origin;
        float a = segment0.direction.dot(segment0.direction);
        float b = segment0.direction.dot(segment1.direction);
        float c = segment1.direction.dot(segment1.direction);
        float d = segment0.direction.dot(w0);
        float e = segment1.direction.dot(w0);

        float denom = a * c - b * b;
        // parameters to compute s_c, t_c
        float s_c, t_c;
        float sn, sd, tn, td;

        // if denom is zero, try finding closest point on segment1 to origin0
        if (IsZero(denom))
        {
            // clamp s_c to 0
            sd = td = c;
            sn = 0.0f;
            tn = e;
        }
        else
        {
            // clamp s_c within [0,1]
            sd = td = denom;
            sn = b * e - c * d;
            tn = a * e - b * d;

            // clamp s_c to 0
            if (sn < 0.0f)
            {
                sn = 0.0f;
                tn = e;
                td = c;
            }
            // clamp s_c to 1
            else if (sn > sd)
            {
                sn = sd;
                tn = e + b;
                td = c;
            }
        }

        // clamp t_c within [0,1]
        // clamp t_c to 0
        if (tn < 0.0f)
        {
            t_c = 0.0f;
            // clamp s_c to 0
            if (-d < 0.0f)
            {
                s_c = 0.0f;
            }
            // clamp s_c to 1
            else if (-d > a)
            {
                s_c = 1.0f;
            }
            else
            {
                s_c = -d / a;
            }
        }
        // clamp t_c to 1
        else if (tn > td)
        {
            t_c = 1.0f;
            // clamp s_c to 0
            if ((-d + b) < 0.0f)
            {
                s_c = 0.0f;
            }
            // clamp s_c to 1
            else if ((-d + b) > a)
            {
                s_c = 1.0f;
            }
            else
            {
                s_c = (-d + b) / a;
            }
        }
        else
        {
            t_c = tn / td;
            s_c = sn / sd;
        }

        // compute closest points
        point0 = segment0.origin + s_c * segment0.direction;
        point1 = segment1.origin + t_c * segment1.direction;

    }
    void closestPoints(YVec3& point0, YVec3& point1,
        const YLineSeg3& segment,
        const YRay3& ray)
    {
        // compute intermediate parameters
        YVec3 w0 = segment.origin - ray.origin;
        float a = segment.direction.dot(segment.direction);
        float b = segment.direction.dot(ray.direction);
        float c = ray.direction.dot(ray.direction);
        float d = segment.direction.dot(w0);
        float e = ray.direction.dot(w0);

        float denom = a * c - b * b;
        // parameters to compute s_c, t_c
        float s_c, t_c;
        float sn, sd, tn, td;

        // if denom is zero, try finding closest point on segment1 to origin0
        if (IsZero(denom))
        {
            // clamp s_c to 0
            sd = td = c;
            sn = 0.0f;
            tn = e;
        }
        else
        {
            // clamp s_c within [0,1]
            sd = td = denom;
            sn = b * e - c * d;
            tn = a * e - b * d;

            // clamp s_c to 0
            if (sn < 0.0f)
            {
                sn = 0.0f;
                tn = e;
                td = c;
            }
            // clamp s_c to 1
            else if (sn > sd)
            {
                sn = sd;
                tn = e + b;
                td = c;
            }
        }

        // clamp t_c within [0,+inf]
        // clamp t_c to 0
        if (tn < 0.0f)
        {
            t_c = 0.0f;
            // clamp s_c to 0
            if (-d < 0.0f)
            {
                s_c = 0.0f;
            }
            // clamp s_c to 1
            else if (-d > a)
            {
                s_c = 1.0f;
            }
            else
            {
                s_c = -d / a;
            }
        }
        else
        {
            t_c = tn / td;
            s_c = sn / sd;
        }

        // compute closest points
        point0 = segment.origin + s_c * segment.direction;
        point1 = ray.origin + t_c * ray.direction;

    }
    void closestPoints(YVec3& point0, YVec3& point1,
        const YLineSeg3& segment,
        const YLine3& line)
    {
        // compute intermediate parameters
        YVec3 w0 = segment.origin - line.origin;// .GetOrigin();
        float a = segment.direction.dot(segment.direction);
        float b = segment.direction.dot(line.direction);// .GetDirection());
        float c = line.direction.dot(line.direction);// .GetDirection());
        float d = segment.direction.dot(w0);
        float e = line.direction.dot(w0);// .GetDirection().dot(w0);

        float denom = a * c - b * b;

        // if denom is zero, try finding closest point on line to segment origin
        if (IsZero(denom))
        {
            // compute closest points
            point0 = segment.origin;
            point1 = line.origin + (e / c) * line.direction;// .GetOrigin() .GetDirection();
        }
        else
        {
            // parameters to compute s_c, t_c
            float s_c, t_c;
            float sn;

            // clamp s_c within [0,1]
            sn = b * e - c * d;

            // clamp s_c to 0
            if (sn < 0.0f)
            {
                s_c = 0.0f;
                t_c = e / c;
            }
            // clamp s_c to 1
            else if (sn > denom)
            {
                s_c = 1.0f;
                t_c = (e + b) / c;
            }
            else
            {
                s_c = sn / denom;
                t_c = (a * e - b * d) / denom;
            }

            // compute closest points
            point0 = segment.origin + s_c * segment.direction;
            point1 = line.origin + t_c * line.direction;// .GetOrigin() .GetDirection();
        }

    }
    YVec3 YLineSeg3::closestPoint(const YVec3& point) const
    {
        YVec3 w = point - origin;
        float proj = w.dot(direction);
        // endpoint 0 is closest point
        if (proj <= 0.0f)
            return origin;
        else
        {
            float vsq = direction.dot(direction);
            // endpoint 1 is closest point
            if (proj >= vsq)
                return origin + direction;
            // else somewhere else in segment
            else
                return origin + (proj / vsq) * direction;
        }
    }
}
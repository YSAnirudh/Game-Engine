#include "Ray3D.h"
#include "Vector3D.h"
namespace MathLib {
    YRay3::YRay3() :
        origin(0.0f, 0.0f, 0.0f),
        direction(1.0f, 0.0f, 0.0f)
    {
    }

    YRay3::YRay3(const YVec3& origin, const YVec3& direction) :
        origin(origin),
        direction(direction)
    {
        this->direction.normalize();

    }

    YRay3::YRay3(const YRay3& other) :
        origin(other.origin),
        direction(other.direction)
    {
        direction.normalize();

    }

    bool
        YRay3::operator==(const YRay3& ray) const
    {
        return (ray.origin == origin && ray.direction == direction);

    }

    bool
        YRay3::operator!=(const YRay3& ray) const
    {
        return !(ray.origin == origin && ray.direction == direction);
    }

    YRay3
        YRay3::transform(float scale, const YQuat& quat, const YVec3& translate) const
    {
        YRay3 ray;
        YMat3x3 rotate;// (quat);

        ray.direction = rotate * direction;
        ray.direction *= scale;

        ray.origin = rotate * origin;
        ray.origin *= scale;
        ray.origin += translate;

        return ray;

    }

    YRay3
        YRay3::transform(float scale, const YMat3x3& rotate, const YVec3& translate) const
    {
        YRay3 ray;

        ray.direction = rotate * direction;
        ray.direction *= scale;

        ray.origin = rotate * origin;
        ray.origin *= scale;
        ray.origin += translate;

        return ray;

    }

    float
        DistanceSquared(const YRay3& ray0, const YRay3& ray1,
            float& s_c, float& t_c)
    {
        // compute intermediate parameters
        YVec3 w0 = ray0.origin - ray1.origin;
        float a = ray0.direction.dot(ray0.direction);
        float b = ray0.direction.dot(ray1.direction);
        float c = ray1.direction.dot(ray1.direction);
        float d = ray0.direction.dot(w0);
        float e = ray1.direction.dot(w0);

        float denom = a * c - b * b;
        // parameters to compute s_c, t_c
        float sn, sd, tn, td;

        // if denom is zero, try finding closest point on ray1 to origin0
        if (IsZero(denom))
        {
            // clamp s_c to 0
            sd = td = c;
            sn = 0.0f;
            tn = e;
        }
        else
        {
            // clamp s_c within [0,+inf]
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
        YVec3 wc = w0 + s_c * ray0.direction - t_c * ray1.direction;
        return wc.dot(wc);

    }

    float
        DistanceSquared(const YRay3& ray, const YLine3& line,
            float& s_c, float& t_c)
    {
        // compute intermediate parameters
        YVec3 w0 = ray.origin - line.origin;
        float a = ray.direction.dot(ray.direction);
        float b = ray.direction.dot(line.direction);
        float c = line.direction.dot(line.direction);
        float d = ray.direction.dot(w0);
        float e = line.direction.dot(w0);

        float denom = a * c - b * b;

        // if denom is zero, try finding closest point on ray1 to origin0
        if (IsZero(denom))
        {
            s_c = 0.0f;
            t_c = e / c;
            // compute difference vector and distance squared
            YVec3 wc = w0 - t_c * line.direction;
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
            YVec3 wc = w0 + s_c * ray.direction - t_c * line.direction;
            return wc.dot(wc);
        }

    }

    float DistanceSquared(const YRay3& ray, const YVec3& point,
        float& t_c)
    {
        YVec3 w = point - ray.origin;
        float proj = w.dot(ray.direction);
        // origin is closest point
        if (proj <= 0)
        {
            t_c = 0.0f;
            return w.dot(w);
        }
        // else use normal line check
        else
        {
            float vsq = ray.direction.dot(ray.direction);
            t_c = proj / vsq;
            return w.dot(w) - t_c * proj;
        }

    }

    void closestPoints(YVec3& point0, YVec3& point1,
        const YRay3& ray0,
        const YRay3& ray1)
    {
        // compute intermediate parameters
        YVec3 w0 = ray0.origin - ray1.origin;
        float a = ray0.direction.dot(ray0.direction);
        float b = ray0.direction.dot(ray1.direction);
        float c = ray1.direction.dot(ray1.direction);
        float d = ray0.direction.dot(w0);
        float e = ray1.direction.dot(w0);

        float denom = a * c - b * b;
        // parameters to compute s_c, t_c
        float s_c, t_c;
        float sn, sd, tn, td;

        // if denom is zero, try finding closest point on ray1 to origin0
        if (IsZero(denom))
        {
            sd = td = c;
            sn = 0.0f;
            tn = e;
        }
        else
        {
            // start by clamping s_c
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
        point0 = ray0.origin + s_c * ray0.direction;
        point1 = ray1.origin + t_c * ray1.direction;
    }

    void closestPoints(YVec3& point0, YVec3& point1,
        const YRay3& ray,
        const YLine3& line)
    {
        // compute intermediate parameters
        YVec3 w0 = ray.origin - line.origin;
        float a = ray.direction.dot(ray.direction);
        float b = ray.direction.dot(line.direction);
        float c = line.direction.dot(line.direction);
        float d = ray.direction.dot(w0);
        float e = line.direction.dot(w0);

        float denom = a * c - b * b;

        // if denom is zero, try finding closest point on ray1 to origin0
        if (IsZero(denom))
        {
            // compute closest points
            point0 = ray.origin;
            point1 = line.origin + (e / c) * line.direction;
        }
        else
        {
            // parameters to compute s_c, t_c
            float sn, s_c, t_c;

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
            point0 = ray.origin + s_c * ray.direction;
            point1 = line.origin + t_c * line.direction;
        }

    }

    YVec3
        YRay3::closestPoint(const YVec3& point) const
    {
        YVec3 w = point - origin;
        float proj = w.dot(direction);
        // endpoint 0 is closest point
        if (proj <= 0.0f)
            return origin;
        else
        {
            float vsq = direction.dot(direction);
            // else somewhere else in ray
            return origin + (proj / vsq) * direction;
        }
    }
}
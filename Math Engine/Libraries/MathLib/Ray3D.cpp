#pragma once
#include "Ray3D.h"
#include "GenMath.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include "Quaternion.h"
namespace MathLib {
    //
	// STATIC VARIABLE DECLARATIONS
	//

    //
	// CONSTRUCTORS START
	//
    YRay3::YRay3() :
        origin(YVec3(0.0f, 0.0f, 0.0f)),
        direction(YVec3(1.0f, 0.0f, 0.0f))
    {
    }

    YRay3::YRay3(const YVec3& Origin, const YVec3& Direction, bool bDirectionIsNormalized = false) :
        origin(Origin),
        direction(Direction) {
        if (!bDirectionIsNormalized) {
            direction.Normalize(yEpsilon);
        }
    }

    YRay3::YRay3(const YRay3& Other, bool bDirectionIsNormalized = false) :
        origin(Other.origin),
        direction(Other.direction) {
        if (!bDirectionIsNormalized) {
            direction.Normalize(yEpsilon);
        }
    }
    //
	// CONSTRUCTORS END
	//

	// 
	// OPERATORS START
	//

    // Equality -> Returns true if this and Other are equal
    bool YRay3::operator==(const YRay3& Other) const {
        return (Other.origin == origin && Other.direction == direction);
    }

    // Equality -> Returns true if this and Other are not equal
    bool YRay3::operator!=(const YRay3& Other) const {
        return !(Other.origin == origin && Other.direction == direction);
    }
    
    // Returns a copy of this YRay transformed using Quat
    // and translated by Translation
    YRay3 YRay3::TransformBy(const YQuat& Quat,
                const YVec3& Translation) const {
        YRay3 ray;
        YMat3x3 rotate;
        rotate.SetupRotation(Quat);// (quat);

        // Is Column Major check and change
        ray.direction = rotate * direction;

        ray.origin = rotate * origin;
        ray.origin += Translation;

        return ray;
    }
    
    // Returns a copy of this YRay transformed using Rotate
    // and translated by Translation
    YRay3 YRay3::TransformBy(const YMat3x3& Rotate,
                const YVec3& Translation) const {
        YRay3 ray;

        // Is Column Major check and change
        ray.direction = Rotate * direction;

        ray.origin = Rotate * origin;
        ray.origin += Translation;

        return ray;
    }

    // Returns a copy of this YRay transformed using Quat
    // Scaled by Scale
    // and translated by Translation
    YRay3 YRay3::TransformBy(float Scale, const YQuat& Quat, 
                const YVec3& Translation) const {
        YRay3 ray;
        YMat3x3 rotate;
        rotate.SetupRotation(Quat);// (quat);

        // Is Column Major check and change
        ray.direction = rotate * direction;
        ray.direction *= Scale;

        ray.origin = rotate * origin;
        ray.origin *= Scale;
        ray.origin += Translation;

        return ray;
    }

    // Returns a copy of this YRay transformed using Rotate
    // Scaled by Scale
    // and translated by Translation
    YRay3 YRay3::TransformBy(float Scale, const YMat3x3& Rotate, 
                const YVec3& Translation) const {
        YRay3 ray;

        // Is Column Major check and change
        ray.direction = Rotate * direction;
        ray.direction *= Scale;

        ray.origin = Rotate * origin;
        ray.origin *= Scale;
        ray.origin += Translation;

        return ray;
    }

    // Returns the distance squared between ray0 and ray1
    float DistanceSquared(const YRay3& ray0, const YRay3& ray1,
            float& s_c, float& t_c) {
        // compute intermediate parameters
        YVec3 w0 = ray0.origin - ray1.origin;
        float a = ray0.direction|(ray0.direction);
        float b = ray0.direction|(ray1.direction);
        float c = ray1.direction|(ray1.direction);
        float d = ray0.direction|(w0);
        float e = ray1.direction|(w0);

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
        return wc|(wc);

    }

    //// Returns the distance squared between ray and line
    //float DistanceSquared(const YRay3& ray, const YLine3& line,
    //        float& s_c, float& t_c) {
    //    // compute intermediate parameters
    //    YVec3 w0 = ray.origin - line.origin;
    //    float a = ray.direction|(ray.direction);
    //    float b = ray.direction|(line.direction);
    //    float c = line.direction|(line.direction);
    //    float d = ray.direction|(w0);
    //    float e = line.direction|(w0);

    //    float denom = a * c - b * b;

    //    // if denom is zero, try finding closest point on ray1 to origin0
    //    if (IsZero(denom))
    //    {
    //        s_c = 0.0f;
    //        t_c = e / c;
    //        // compute difference vector and distance squared
    //        YVec3 wc = w0 - t_c * line.direction;
    //        return wc|(wc);
    //    }
    //    else
    //    {
    //        // parameters to compute s_c, t_c
    //        float sn;

    //        // clamp s_c within [0,1]
    //        sn = b * e - c * d;

    //        // clamp s_c to 0
    //        if (sn < 0.0f)
    //        {
    //            s_c = 0.0f;
    //            t_c = e / c;
    //        }
    //        // clamp s_c to 1
    //        else if (sn > denom)
    //        {
    //            s_c = 1.0f;
    //            t_c = (e + b) / c;
    //        }
    //        else
    //        {
    //            s_c = sn / denom;
    //            t_c = (a * e - b * d) / denom;
    //        }

    //        // compute difference vector and distance squared
    //        YVec3 wc = w0 + s_c * ray.direction - t_c * line.direction;
    //        return wc|(wc);
    //    }

    //}

    // Returns the distance squared between ray and point
    float DistanceSquared(const YRay3& ray, const YVec3& point,
        float& t_c) {
        YVec3 w = point - ray.origin;
        float proj = w|(ray.direction);
        // origin is closest point
        if (proj <= 0)
        {
            t_c = 0.0f;
            return w|(w);
        }
        // else use normal line check
        else
        {
            float vsq = ray.direction|(ray.direction);
            t_c = proj / vsq;
            return w|(w) - t_c * proj;
        }

    }

    // Assigns the closest points from ray0 and ray1
    // to point0 and point1
    void ClosestPoints(YVec3& point0, YVec3& point1,
        const YRay3& ray0,
        const YRay3& ray1) {
        // compute intermediate parameters
        YVec3 w0 = ray0.origin - ray1.origin;
        float a = ray0.direction|(ray0.direction);
        float b = ray0.direction|(ray1.direction);
        float c = ray1.direction|(ray1.direction);
        float d = ray0.direction|(w0);
        float e = ray1.direction|(w0);

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

    //// Assigns the closest points from ray and line
    //// to point0 and point1
    //void ClosestPoints(YVec3& point0, YVec3& point1,
    //    const YRay3& ray,
    //    const YLine3& line) {
    //    // compute intermediate parameters
    //    YVec3 w0 = ray.origin - line.origin;
    //    float a = ray.direction|(ray.direction);
    //    float b = ray.direction|(line.direction);
    //    float c = line.direction|(line.direction);
    //    float d = ray.direction|(w0);
    //    float e = line.direction|(w0);

    //    float denom = a * c - b * b;

    //    // if denom is zero, try finding closest point on ray1 to origin0
    //    if (IsZero(denom))
    //    {
    //        // compute closest points
    //        point0 = ray.origin;
    //        point1 = line.origin + (e / c) * line.direction;
    //    }
    //    else
    //    {
    //        // parameters to compute s_c, t_c
    //        float sn, s_c, t_c;

    //        // clamp s_c within [0,1]
    //        sn = b * e - c * d;

    //        // clamp s_c to 0
    //        if (sn < 0.0f)
    //        {
    //            s_c = 0.0f;
    //            t_c = e / c;
    //        }
    //        // clamp s_c to 1
    //        else if (sn > denom)
    //        {
    //            s_c = 1.0f;
    //            t_c = (e + b) / c;
    //        }
    //        else
    //        {
    //            s_c = sn / denom;
    //            t_c = (a * e - b * d) / denom;
    //        }

    //        // compute closest points
    //        point0 = ray.origin + s_c * ray.direction;
    //        point1 = line.origin + t_c * line.direction;
    //    }

    //}

    // Returns the closest point from this YRay to point
    YVec3 YRay3::ClosestPoint(const YVec3& point) const {
        YVec3 w = point - origin;
        float proj = w|(direction);
        // endpoint 0 is closest point
        if (proj <= 0.0f)
            return origin;
        else
        {
            float vsq = direction|(direction);
            // else somewhere else in ray
            return origin + (proj / vsq) * direction;
        }
    }

    //
	// FUNCTIONS END
	//
}
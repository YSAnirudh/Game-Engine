#pragma once

namespace MathLib {
    class YQuat;
    class YMat3x3;
    class YLine3;
    class YVec3;
	class YRay3 {
    public:
		YVec3 origin;
		YVec3 direction;
        //
		// CONSTRUCTOR OVERLOADS START
		//

		// Constructor - Empty
		// Initializes origin to 0,0,0 and direction 1,0,0
        YRay3();
        // Constructor - 2 YVec3 1 bool
		// Initializes origin to Origin and direction Direction
        // Normalizes direction based on bDirectionIsNormalized
        YRay3(const YVec3& Origin, const YVec3& Direction, bool bDirectionIsNormalized);
        // Constructor - 1 YRay 1 bool
		// Initializes this to Other
        // Normalizes direction based on bDirectionIsNormalized
        YRay3(const YRay3& Other, bool bDirectionIsNormalized);

        //
		// CONSTRUCTOR OVERLOADS END
		//
		
		//
		// OPERATORS START
		//

		// COMPARISION OPERATORS
		
		// Operator -> Equality 
		bool operator==(const YRay3& Other) const;
        // Operator -> Inequality
		bool operator!=(const YRay3& Other) const;

        //
		// FUNCTIONS START
		//

		// Const Functions
        YRay3 TransformBy(float Scale, const YQuat& Quat,
            const YVec3& Translation) const;
        YRay3 TransformBy(float Scale, const YMat3x3& Rotate,
            const YVec3& Translation) const;
        YRay3 TransformBy(const YQuat& Quat,
            const YVec3& Translation) const;
        YRay3 TransformBy(const YMat3x3& Rotate,
            const YVec3& Translation) const;
        YVec3 ClosestPoint(const YVec3& point) const;

        // Non Const Functions
        friend float DistanceSquared(const YRay3& ray0, const YRay3& ray1,
            float& s_c, float& t_c);
        friend float DistanceSquared(const YRay3& ray, const YLine3& line,
            float& s_c, float& t_c);
        inline friend float DistanceSquared(const YLine3& line, const YRay3& ray,
            float& s_c, float& t_c)
        {
            return DistanceSquared(ray, line, t_c, s_c);
        }
        friend float DistanceSquared(const YRay3& ray, const YVec3& point,
            float& t_c);

        friend void ClosestPoints(YVec3& point0, YVec3& point1,
            const YRay3& ray0,
            const YRay3& ray1);
        friend void ClosestPoints(YVec3& point0, YVec3& point1,
            const YRay3& ray,
            const YLine3& line);
	};
}
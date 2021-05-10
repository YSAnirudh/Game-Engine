#pragma once


namespace MathLib {
    class YVec3;
    class YQuat;
    class YMat3x3;
    class YMat4x4;
    class YVec4;
	class YPlane {
    public:
        float offset;
        YVec3 normal;
        YPlane();
        YPlane(const YVec3& Normal, float Offset);
        YPlane(const YVec3& InPoint, const YVec3& InNormal);
        YPlane(float InX, float InY, float InZ, float InW);
        YPlane(const YVec4& V);
        
        //YPlane(YVec3 A, YVec3 C, YVec3 C);

        // copy operations
        YPlane(const YPlane& other);

        inline bool operator==(const YPlane& Plane) const;
        inline bool operator!=(const YPlane& Plane) const;

        inline YPlane operator+(const YPlane& Plane) const;
        inline YPlane operator+=(const YPlane& Plane);
        inline YPlane operator-(const YPlane& Plane) const;
        inline YPlane operator-=(const YPlane& Plane);
        inline YPlane operator*(const YPlane& Plane) const;
        inline YPlane operator*=(const YPlane& Plane) const;
        inline YPlane operator*(float Scale) const;
        inline friend YPlane operator*(float Scale, const YPlane& Plane);
        inline YPlane operator*=(float Scale);
        inline YPlane operator/(float Scale) const;
        inline YPlane operator/=(float Scale);
        inline float operator|(const YPlane& Plane) const;
        

        inline bool Equals(const YPlane& Plane, float Tolerance) const;
        inline YPlane Flip() const;
        inline YVec3 GetNormal() const;
        inline YVec3 GetOrigin() const;
        inline bool IsValid() const;
        inline float PlaneDot(const YVec3& V) const;
        inline YPlane TransformBy(const YMat4x4& M) const;
        inline YPlane TransformBy(const YQuat& Quat) const;
        inline YPlane TransformBy(
            float scale, 
            const YQuat& rotation,
            const YVec3& translation
        ) const;

        inline bool Normalize(float Tolerance);
        // closest point
        inline YVec3 ClosestPoint(const YVec3& point) const;
	};
}
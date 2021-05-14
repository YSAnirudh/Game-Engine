#pragma once

namespace MathLib {
	class YEuler;
	class YMat3x3;
	class YQuat;
	class YVec3;
	class YMat4x3 {
	public:
		float m11, m12, m13;
		float m21, m22, m23;
		float m31, m32, m33;
		float tx, ty, tz;

		//
		// Constructors START
		//
		YMat4x3();
		YMat4x3(const YMat4x3& m);
		YMat4x3(const YVec3& top, const YVec3& middle, const YVec3& bottom, const YVec3& translation);
		// Constructors END

		//
		// Operators START
		//

		//Operators END

		//
		// Functions START
		//
		void setToIdentity();

		void zeroTranslation();
		void setTranslation(const YVec3& d);
		void setupTranslation(const YVec3& d);

		void setupLocalToParent(const YVec3& pos, const YEuler& orient);
		void setupLocalToParent(const YVec3& pos, const YMat3x3& orient);
		void setupParentToLocal(const YVec3& pos, const YEuler& orient);
		void setupParentToLocal(const YVec3& pos, const YMat3x3& orient);
		
		void setupRotate(int axis, float theta);
		void setupRotate(const YVec3& axis, float theta);
		
		void fromQuaternion(const YQuat& quat);

		void setupScale(const YVec3& scale);
		void setupScale(const YVec3& axis, float k);
		void setupShear(int axis, float s, float t);
		void setupProject(const YVec3& n);
		void setupReflect(int axis, float k = 0.0f);
		void setupReflect(const YVec3& n);
		// Functions END
	};
	//
	// Non Member functions START
	//
	extern YVec3 operator *(const YVec3& vec, const YMat4x3& mat);
	extern YMat4x3 operator *(const YMat4x3& mat1, const YMat4x3& mat2);
	extern YMat4x3& operator*=(YMat4x3& a, const YMat4x3& b);
	extern float determinant(const YMat4x3& mat);
	extern YMat4x3 inverse(const YMat4x3& mat);
	extern YVec3 getTranslation(const YMat4x3& mat);

	extern YVec3 getPositionFromParentToLocalMatrix(const YMat4x3& m);
	extern YVec3 getPositionFromLocalToParentMatrix(const YMat4x3& m);
	// Non Member functions END
}
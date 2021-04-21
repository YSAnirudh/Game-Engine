#pragma once
#include "Matrix4x3.h"
namespace MathLib {
	class YMat4x3;
	class YMat3x3;
	class YQuat;
	class YEuler {
	public:
		float roll, pitch, yaw;
		// Z, X, Y
		
		//
		// Constructor overloads
		//
		YEuler();
		YEuler(float roll, float pitch, float yaw);

		//
		// Operators START
		//

		// Operators END

		//
		// Functions START
		//

		void canonize();
		void fromInertialToObjectQuat(YQuat& quat);
		void fromObjectToInertialQuat(YQuat& quat);

		void fromWorldToObjectMat(YMat4x3& mat);
		void fromObjectToWorldMat(YMat4x3& mat);

		void fromRotationMat(YMat3x3& rotmat);

		// Functions END
	};

	//
	// Non Member Functions START
	//
	
	//YEuler 

	// Non Member Functions END
}
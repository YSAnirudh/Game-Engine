#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
namespace YSAoo {

	// Object is something that can be added onto the screen
	enum class YObjectType {
		YLight,
		YModel,
		YMesh,
		YDefault
	};

	class GameObject
	{
	public:
		GameObject();

		virtual void CreateObject(const char* ObjectName, YObjectType ObjectType);
		virtual void SetTransform(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f));
		
		// Setters
		inline void SetObjectName(const char* ObjectName) { this->ObjectName = ObjectName; };
		
		// Getters
		inline const char* GetObjectName() const { return ObjectName; };
		inline glm::vec3 GetObjectPosition() const { return ObjectPosition; };
		inline glm::vec3 GetObjectRotation() const { return ObjectRotation; };
		inline glm::vec3 GetObjectScale() const { return ObjectScale; };


		~GameObject();
	protected:
		const char* ObjectName;
		YObjectType ObjectType;

		// Add Positions
		glm::vec3 ObjectPosition;
		glm::vec3 ObjectRotation;
		glm::vec3 ObjectScale;
	};
}

#endif // !GAMEOBJECT_H
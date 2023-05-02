#include "GameObject.h"
namespace YSAoo {
	GameObject::GameObject()
	{
		ObjectName = "Default Object";
		ObjectType = YObjectType::YDefault;
		ObjectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		ObjectRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		ObjectScale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void GameObject::CreateObject(const char* ObjectName, YObjectType ObjectType)
	{
		this->ObjectName = ObjectName;
		this->ObjectType = ObjectType;
		ObjectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		ObjectRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		ObjectScale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void GameObject::SetTransform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
	{
		ObjectPosition = Position;
		ObjectRotation = Rotation;
		ObjectScale = Scale;
	}

	GameObject::~GameObject()
	{
	}
}

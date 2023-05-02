#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Objects/GameObject.h"
#include "Lights/Light.h"
#include "Meshes/Mesh.h"
#include "Meshes/Model.h"
#include "Common.h"
#include "RenderingCommons.h"
#include <unordered_map>

namespace YSAoo {
	class ObjectManager
	{
	public:
		ObjectManager();

		void AddModelMatrixLocation(GLuint UniformModelMatrixLocation);
		void SetUniformModelMatrix(GameObject* Object, bool UseModel = true);

		void CreateModel(const char* ObjectName, const std::string& FileName, 
			const glm::vec3& Position = glm::vec3(0.0f), 
			const glm::vec3& Rotation = glm::vec3(0.0f),
			const glm::vec3& Scale = glm::vec3(1.0f));
		void CreateCustomMesh(const char* ObjectName,
			GLfloat* Vertices, unsigned int* Indices, unsigned int NoOfVertices, unsigned int NoOfIndices,
			Material* BaseMaterial, Texture* BaseTexture,
			const glm::vec3& Position = glm::vec3(0.0f),
			const glm::vec3& Rotation = glm::vec3(0.0f),
			const glm::vec3& Scale = glm::vec3(1.0f));
		void CreateLight(const char* ObjectName, Light* BaseLight,
			const glm::vec3& Position = glm::vec3(0.0f),
			const glm::vec3& Rotation = glm::vec3(0.0f),
			const glm::vec3& Scale = glm::vec3(1.0f));

		// Object Handlers
		void CreateModel(Model* Object);
		void CreateCustomMesh(Mesh* Object);
		void CreateLight(Light* Object);
		void CreateLightVolume(Model* LightVolume);
		
		void DeleteModel(const char* ObjectName);
		void DeleteCustomMesh(const char* ObjectName);
		void DeleteLight(const char* ObjectName);
		void DeleteLightVolume(const char* ObjectName);
		
		void RenderModels();
		void RenderCustomMeshes();
		void UseLights();
		void RenderLightVolumes(Light* BaseLight);

		inline std::unordered_map<const char*, Model*> GetModelsList() const { return ModelsList; };
		inline std::unordered_map<const char*, Mesh*> GetMeshList() const { return CustomMeshList; };
		inline std::unordered_map<const char*, Light*> GetLightsList() const { return LightsList; };
		inline std::unordered_map<const char*, Model*> GetLightVolumes() const { return LightVolumes; };

		~ObjectManager();
	private:
		std::unordered_map<const char*, Model*> ModelsList;
		std::unordered_map<const char*, Mesh*> CustomMeshList;
		std::unordered_map<const char*, Light*> LightsList;
		std::unordered_map<const char*, Model*> LightVolumes;

		GLuint UniformModelMatrixLocation;
	};
}

#endif
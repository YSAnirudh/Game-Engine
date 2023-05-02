#include "ObjectManager.h"
namespace YSAoo {
	ObjectManager::ObjectManager()
	{
		ModelsList.clear();
		LightsList.clear();
		CustomMeshList.clear();

		UniformModelMatrixLocation = 0;
	}

	void ObjectManager::AddModelMatrixLocation(GLuint UniformModelMatrixLocation)
	{
		this->UniformModelMatrixLocation = UniformModelMatrixLocation;
	}

	void ObjectManager::SetUniformModelMatrix(GameObject* Object, bool UseModel)
	{
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		if (UseModel) {
			ModelMatrix = glm::translate(ModelMatrix, Object->GetObjectPosition());

			ModelMatrix = glm::rotate(ModelMatrix, Object->GetObjectRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, Object->GetObjectRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::rotate(ModelMatrix, Object->GetObjectRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

			ModelMatrix = glm::scale(ModelMatrix, Object->GetObjectScale());
		}

		glUniformMatrix4fv(UniformModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	}

	void ObjectManager::CreateModel(const char* ObjectName, const std::string& FileName, const glm::vec3& Position, const glm::vec3& Rotation, const glm::vec3& Scale)
	{
		Model* TempModel = new Model();
		TempModel->CreateObject(ObjectName, YObjectType::YModel);
		if (!TempModel->LoadModel(FileName)) {
			printf("COuldnt load model!\n");
		}
		TempModel->SetTransform(Position, Rotation, Scale);
		CreateModel(TempModel);
	}

	void ObjectManager::CreateCustomMesh(const char* ObjectName, GLfloat* Vertices, unsigned int* Indices, unsigned int NoOfVertices, unsigned int NoOfIndices, Material* BaseMaterial, Texture* BaseTexture, const glm::vec3& Position, const glm::vec3& Rotation, const glm::vec3& Scale)
	{
		Mesh* TempCustomMesh = new Mesh();
		TempCustomMesh->CreateObject("MainCube", YObjectType::YMesh);
		TempCustomMesh->InitMesh(Vertices, Indices, NoOfVertices, NoOfIndices);
		TempCustomMesh->SetTransform(Position, Rotation, Scale);
		TempCustomMesh->AddMatTex(BaseMaterial, BaseTexture);
		CreateCustomMesh(TempCustomMesh);
	}

	void ObjectManager::CreateLight(const char* ObjectName, Light* BaseLight)
	{
		BaseLight->SetObjectName(ObjectName);
		CreateLight(BaseLight);
	}

	void ObjectManager::CreateModel(Model* Object)
	{
		if (ModelsList.find(Object->GetObjectName()) != ModelsList.end()) {
			printf("There is already an object named: %s\n", Object->GetObjectName());
			printf("Object Not Added.\n");
			return;
		}

		ModelsList.insert(std::make_pair(Object->GetObjectName(), Object));
	}

	void ObjectManager::CreateCustomMesh(Mesh* Object)
	{
		if (CustomMeshList.find(Object->GetObjectName()) != CustomMeshList.end()) {
			printf("There is already an object named: %s\n", Object->GetObjectName());
			printf("Object Not Added.\n");
			return;
		}

		CustomMeshList.insert(std::make_pair(Object->GetObjectName(), Object));
	}

	void ObjectManager::CreateLight(Light* Object)
	{
		if (LightsList.find(Object->GetObjectName()) != LightsList.end()) {
			printf("There is already an object named: %s\n", Object->GetObjectName());
			printf("Object Not Added.\n");
			return;
		}

		if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::DEFERRED_RENDERING) {
			Object->CreateLightVolume();
		}

		LightsList.insert(std::make_pair(Object->GetObjectName(), Object));
	}

	void ObjectManager::CreateLightVolume(Model* LightVolume)
	{
		if (LightVolumes.find(LightVolume->GetObjectName()) != LightVolumes.end()) {
			printf("There is already an object named: %s\n", LightVolume->GetObjectName());
			printf("Object Not Added.\n");
			return;
		}

		LightVolumes.insert(std::make_pair(LightVolume->GetObjectName(), LightVolume));
	}

	void ObjectManager::DeleteModel(const char* ObjectName)
	{
		if (ModelsList.find(ObjectName) == ModelsList.end()) {
			printf("There is no object named: %s\n", ObjectName);
			printf("Object Not Deleted.\n");
			return;
		}
		delete ModelsList[ObjectName];
		ModelsList[ObjectName] = nullptr;
		ModelsList.erase(ObjectName);
	}

	void ObjectManager::DeleteCustomMesh(const char* ObjectName)
	{
		if (CustomMeshList.find(ObjectName) == CustomMeshList.end()) {
			printf("There is no object named: %s\n", ObjectName);
			printf("Object Not Deleted.\n");
			return;
		}
		delete CustomMeshList[ObjectName];
		CustomMeshList[ObjectName] = nullptr;
		CustomMeshList.erase(ObjectName);
	}

	void ObjectManager::DeleteLight(const char* ObjectName)
	{
		if (LightsList.find(ObjectName) == LightsList.end()) {
			printf("There is no object named: %s\n", ObjectName);
			printf("Object Not Deleted.\n");
			return;
		}
		delete LightsList[ObjectName];
		LightsList[ObjectName] = nullptr;
		LightsList.erase(ObjectName);
	}

	void ObjectManager::DeleteLightVolume(const char* ObjectName)
	{
		if (LightVolumes.find(ObjectName) == LightVolumes.end()) {
			printf("There is no object named: %s\n", ObjectName);
			printf("Object Not Deleted.\n");
			return;
		}
		delete LightVolumes[ObjectName];
		LightVolumes[ObjectName] = nullptr;
		LightVolumes.erase(ObjectName);
	}

	void ObjectManager::RenderModels()
	{
		for (auto pair : ModelsList) {
			SetUniformModelMatrix(pair.second);
			pair.second->RenderModel();
		}
	}

	void ObjectManager::RenderCustomMeshes()
	{
		for (auto pair : CustomMeshList) {
			SetUniformModelMatrix(pair.second);
			pair.second->BaseRenderMesh();
		}
	}

	void ObjectManager::UseLights()
	{
		for (auto pair : LightsList) {
			pair.second->UseLight();
		}
	}

	void ObjectManager::RenderLightVolumes(Light* BaseLight)
	{
		if (BaseLight->GetLightVolume()) {
			SetUniformModelMatrix(BaseLight->GetLightVolume());
			BaseLight->GetLightVolume()->RenderModel();
		}
	}

	ObjectManager::~ObjectManager()
	{
		for (auto a : ModelsList) {
			delete a.second;
			a.second = nullptr;
		}
		ModelsList.clear();

		for (auto a : CustomMeshList) {
			delete a.second;
			a.second = nullptr;
		}
		CustomMeshList.clear();

		for (auto a : LightsList) {
			delete a.second;
			a.second = nullptr;
		}
		LightsList.clear();

		for (auto a : LightVolumes) {
			delete a.second;
			a.second = nullptr;
		}
		LightVolumes.clear();
	}
}
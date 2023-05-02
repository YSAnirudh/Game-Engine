#include "Model.h"

#define POSITION_LOCATION 0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION 2

YSAoo::Model::Model()
{
	Buffers[0] = 0;
	Buffers[1] = 0;
	Buffers[2] = 0;
	Buffers[3] = 0;
	Buffers[4] = 0;
	Buffers[5] = 0;
}

bool YSAoo::Model::LoadModel(const std::string& FileName)
{
	//ClearModel();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(ARRAY_SIZE_IN_ELEM(Buffers), Buffers);

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene * pScene = Importer.ReadFile(FileName.c_str(), ASSIMP_LOAD_FLAGS);

	if (pScene) {
		Ret = InitFromScene(pScene, FileName.c_str());
	}
	else {
		printf("Error Parsing '%s': '%s'\n", FileName.c_str(), Importer.GetErrorString());
	}

	glBindVertexArray(0);
	return Ret;
}

bool YSAoo::Model::InitFromScene(const aiScene* pScene, const char* FileName)
{
	MeshList.resize(pScene->mNumMeshes);
	TextureList.resize(pScene->mNumMaterials);

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;

	CountVerticesAndIndices(pScene, NumVertices, NumIndices);

	ReserveSpace(NumVertices, NumIndices);

	InitAllMeshes(pScene);
	
	if (!InitMaterials(pScene, FileName)) {
		return false;
	}
	PopulateBuffers();
	return true;
}

void YSAoo::Model::CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices)
{
	for (unsigned int i = 0; i < MeshList.size(); i++) {
		MeshList[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
		MeshList[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
		MeshList[i].BaseVertex = NumVertices;
		MeshList[i].BaseIndex = NumIndices;

		NumVertices += pScene->mMeshes[i]->mNumVertices;
		NumIndices += MeshList[i].NumIndices;
	}
}

void YSAoo::Model::ReserveSpace(unsigned int NumVertices, unsigned int NumIndices)
{
	Positions.reserve(NumVertices);
	Normals.reserve(NumVertices);
	TexCoords.reserve(NumVertices);
	Indices.reserve(NumIndices);
}

void YSAoo::Model::InitAllMeshes(const aiScene* pScene)
{
	for (unsigned int i = 0; i < MeshList.size(); i++) {
		const aiMesh* pAiMesh = pScene->mMeshes[i];
		InitSingleMesh(pAiMesh);
	}
}

void YSAoo::Model::InitSingleMesh(const aiMesh* pAiMesh)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < pAiMesh->mNumVertices; i++) {
		const aiVector3D& pPos = pAiMesh->mVertices[i];
		const aiVector3D& pNormal = pAiMesh->mNormals[i];
		const aiVector3D& pTexCoord = pAiMesh->HasTextureCoords(0) ? pAiMesh->mTextureCoords[0][i] : Zero3D;

		Positions.push_back(glm::vec3(pPos.x, pPos.y, pPos.z));
		Normals.push_back(glm::vec3(pNormal.x, pNormal.y, pNormal.z));
		TexCoords.push_back(glm::vec2(pTexCoord.x, pTexCoord.y));
	}

	for (unsigned int i = 0; i < pAiMesh->mNumFaces; i++) {
		const aiFace& Face = pAiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);

		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}
}

bool YSAoo::Model::InitMaterials(const aiScene* pScene, const char* FileName)
{
	std::string FName = FileName;
	std::string::size_type SlashIndex = FName.find_last_of("/");

	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = FName.substr(0, SlashIndex);
	}

	bool Ret = true;

	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		TextureList[i] = nullptr;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				size_t idx = std::string(Path.data).rfind("\\");
				
				std::string FPath = std::string(Path.data).substr(idx + 1);

				std::string FullPath = std::string("Textures/") + FPath;

				TextureList[i] = new Texture(FullPath.c_str());

				if (!TextureList[i]->LoadTextureA()) {
					printf("Error Loading Texture '%s'\n", FullPath.c_str());
					delete TextureList[i];
					TextureList[i] = nullptr;
					Ret = false;
				}
				else {
					//printf("Loaded Texture '%s'\n", FullPath.c_str());
				}
			}
		}
	}
	return Ret;
}

void YSAoo::Model::PopulateBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(POSITION_LOCATION);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TEX_COORD_LOCATION);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(NORMAL_LOCATION);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

void YSAoo::Model::RenderModel()
{
	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < MeshList.size(); i++) {
		unsigned int  MaterialIndex = MeshList[i].MaterialIndex;

		assert(MaterialIndex < TextureList.size());

		if (TextureList[MaterialIndex]) {
			TextureList[MaterialIndex]->UseTexture();
		}

		glDrawElementsBaseVertex(
			GL_TRIANGLES,
			MeshList[i].NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(unsigned int) * MeshList[i].BaseIndex),
			MeshList[i].BaseVertex
		);
	}

	glBindVertexArray(0);
}

void YSAoo::Model::Render(unsigned int NumInstances, const glm::mat4* WVPMats, const glm::mat4* WorldMats)
{
}

void YSAoo::Model::ClearModel()
{
	for (unsigned int i = 0; i < TextureList.size(); i++) {
		SAFE_DELETE(TextureList[i]);
	}

	if (Buffers[0] != 0) {
		glDeleteBuffers(ARRAY_SIZE_IN_ELEM(Buffers), Buffers);
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}

YSAoo::Model::~Model()
{
	ClearModel();
}
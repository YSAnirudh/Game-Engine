#ifndef MODEL_H
#define MODEL_H
#include "Objects/GameObject.h"
#include <vector>
#include <string>
#include "Common.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "MaterialProperties/Texture.h"

namespace YSAoo {
	class Model : public GameObject
	{
	public:
		Model();

		bool LoadModel(const std::string& FileName);
		void RenderModel();
		void Render(unsigned int NumInstances, const glm::mat4* WVPMats, const glm::mat4* WorldMats);
		void ClearModel();

		~Model();
	private:

		bool InitFromScene(const aiScene* pScene, const char* FileName);

		void CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices);

		void ReserveSpace(unsigned int NumVertices, unsigned int NumIndices);

		void InitAllMeshes(const aiScene* pScene);
		void InitSingleMesh(const aiMesh* pAiMesh);

		bool InitMaterials(const aiScene* pScene, const char* FileName);

		void PopulateBuffers();

	private:
#define INVALID_MATERIAL 0xFFFFFFFF
		struct BasicMeshEntry {
			BasicMeshEntry() {
				NumIndices = 0;
				BaseVertex = 0;
				BaseIndex = 0;
				MaterialIndex = INVALID_MATERIAL;
			}

			unsigned int NumIndices;
			unsigned int BaseVertex;
			unsigned int BaseIndex;
			unsigned int MaterialIndex;
		};

		enum BufferType {
			INDEX_BUFFER = 0,
			POS_VB = 1,
			TEXCOORD_VB = 2,
			NORMAL_VB = 3,
			WVP_MAT_VB = 4,
			WORLD_MAT_VB = 5,
			NUM_BUFFERS = 6
		};

		GLuint VAO = 0;
		GLuint Buffers[NUM_BUFFERS];

		std::vector<BasicMeshEntry> MeshList;
		std::vector<Texture*> TextureList;
		std::vector<unsigned int> MeshToTex;

		std::vector<glm::vec3> Positions;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec2> TexCoords;
		std::vector<unsigned int> Indices;
	};
}

#endif
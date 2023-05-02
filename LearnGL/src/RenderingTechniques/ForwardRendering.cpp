#include "ForwardRendering.h"
namespace YSAoo{
	ForwardRendering::ForwardRendering()
	{
		WindowWidth = 0;
		WindowHeight = 0;
		Projection = glm::mat4();
		View = glm::mat4();
		CameraPosition = glm::vec3();
	}

	ForwardRendering::ForwardRendering(GLint WindowWidth, GLint WindowHeight)
	{
		this->WindowWidth = WindowWidth;
		this->WindowHeight = WindowHeight;
		Projection = glm::mat4();
		View = glm::mat4();
		CameraPosition = glm::vec3();
	}

	void ForwardRendering::DirectionalShadowMapPass(ObjectManager* ObjectManagerRef, DirectionalLight* dLight)
	{
		ShaderList[1]->UseShader();
		
		glViewport(0, 0, dLight->GetShadowMap()->GetShadowWidth(), dLight->GetShadowMap()->GetShadowHeight());
		dLight->GetShadowMap()->Write();

		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 LightTransform = glm::mat4(1.0f);
		UniformModel = ShaderList[1]->GetModelMatrixLocation();
		LightTransform = dLight->CalculateDirectionalLightTransform();
		ShaderList[1]->SetDirectionalLightTransform(&LightTransform);

		ShaderList[1]->Validate();

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ForwardRendering::OmniDirectionalShadowMapPass(ObjectManager* ObjectManagerRef, PointLight* pLight)
	{
		ShaderList[2]->UseShader();

		glViewport(0, 0, pLight->GetShadowMap()->GetShadowWidth(), pLight->GetShadowMap()->GetShadowHeight());

		pLight->GetShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		UniformModel = ShaderList[2]->GetModelMatrixLocation();

		ShaderList[2]->SetOmniShadowSpecs(pLight->GetPosition(), pLight->GetFarPlane());
		ShaderList[2]->SetLightMatrices(pLight->CalculateLightTransform());

		ShaderList[2]->Validate();

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ForwardRendering::RenderPass(ObjectManager* ObjectManagerRef)
	{
		glViewport(0, 0, WindowWidth, WindowHeight);
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShaderList[0]->UseShader();

		ShaderList[0]->SetProjectionView(Projection, View);
		ShaderList[0]->SetEyePosition(CameraPosition);

		UniformModel = ShaderList[0]->GetModelMatrixLocation();
		UniformSpecularIntensity = ShaderList[0]->GetSpecularIntensityLocation();
		UniformShininess = ShaderList[0]->GetShininessLocation();
		static_cast<ForwardShader*>(ShaderList[0])->ResetShaderLightCount();
		for (auto light : ObjectManagerRef->GetLightsList()) {
			if (light.second->GetLightType() == YLightType::YDirectionalLight) {
				//glm::mat4 DirectionalLightTransform = static_cast<DirectionalLight*>(light.second)->CalculateDirectionalLightTransform();

				//ShaderList[0]->SetDirectionalLightTransform(&DirectionalLightTransform);

				//light.second->GetShadowMap()->Read(GL_TEXTURE1);
				////ShaderList[0]->SetTexture(0);
				//ShaderList[0]->SetDirectionalShadowMap(1);
			}
			else if (light.second->GetLightType() == YLightType::YPointLight) {
				//ShaderList[0]->GetLocationsForLighting(light.second);
			}
			else if (light.second->GetLightType() == YLightType::YSpotLight) {
				//ShaderList[0]->GetLocationsForLighting(light.second);
			}
			ShaderList[0]->GetLocationsForLighting(light.second);
		}
		static_cast<ForwardShader*>(ShaderList[0])->SetLightCounts();

		ShaderList[0]->Validate();

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);
	}

	void ForwardRendering::RenderObjectsWithMaterialSpecs(ObjectManager* ObjectManagerRef)
	{
		ObjectManagerRef->AddModelMatrixLocation(UniformModel);

		glm::mat4 model(1.0f);
		auto MeshList = ObjectManagerRef->GetMeshList();
		for (auto a : MeshList) {
			a.second->SetSpecs(UniformSpecularIntensity, UniformShininess);
		}
		ObjectManagerRef->RenderModels();
		ObjectManagerRef->RenderCustomMeshes();
		ObjectManagerRef->UseLights();
	}

	void ForwardRendering::ForwardRender(ObjectManager* ObjectManagerRef, const glm::mat4& Projection, const glm::mat4& View , const glm::vec3 CameraPosition)
	{
		/*for (auto light : ObjectManagerRef->GetLightsList()) {
			if (light.second->GetLightType() == YLightType::YDirectionalLight) {
				DirectionalShadowMapPass(ObjectManagerRef, static_cast<DirectionalLight*>(light.second));
			} else if (light.second->GetLightType() == YLightType::YPointLight) {
				OmniDirectionalShadowMapPass(ObjectManagerRef, static_cast<PointLight*>(light.second));
			}
		}*/
		SetProjectionView(Projection, View);
		SetCameraPosition(CameraPosition);
		RenderPass(ObjectManagerRef);
	}

	void ForwardRendering::AddShader(const char* VertexShaderLocation, const char* FragmentShaderLocation, const char* GeometryShaderLocation)
	{
		ShaderList.push_back(new ForwardShader());
		if (GeometryShaderLocation == "") {
			ShaderList[ShaderList.size() - 1]->CreateFromFiles(VertexShaderLocation, FragmentShaderLocation);
		}
		else {
			ShaderList[ShaderList.size() - 1]->CreateFromFiles(VertexShaderLocation, FragmentShaderLocation, GeometryShaderLocation);
		}
	}

	ForwardRendering::~ForwardRendering()
	{
	}
}

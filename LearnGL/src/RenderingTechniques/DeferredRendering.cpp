#include "DeferredRendering.h"
namespace YSAoo {
	DeferredRendering::DeferredRendering()
	{
		WindowWidth = 0;
		WindowHeight = 0;
		Projection = glm::mat4();
		DirLightProjection = glm::mat4();
		View = glm::mat4();
		CameraPosition = glm::vec3();

		GBufferMap = new GBufferShader();
		GBufferMap->Init();
	}

	DeferredRendering::DeferredRendering(GLuint WindowWidth, GLuint WindowHeight)
	{
		this->WindowWidth = WindowWidth;
		this->WindowHeight = WindowHeight;
		Projection = glm::mat4();
		DirLightProjection = glm::mat4();
		View = glm::mat4();
		CameraPosition = glm::vec3();

		GBufferMap = new GBufferShader();
		if (MAIN_RENDERING_TECHNIQUE == GBUFFER_RENDERING) {
			GBufferMap->GBufferInit();
		}
		else {
			GBufferMap->Init();
		}
	}

	void DeferredRendering::GBufferRender(ObjectManager* ObjectManagerRef, const glm::mat4& Projection, const glm::mat4& View, const glm::vec3 CameraPosition)
	{
		SetProjectionView(Projection, View);
		SetCameraPosition(CameraPosition);
		GBufferGeometryPass(ObjectManagerRef);
		GBufferLightPassX4();
	}

	void DeferredRendering::DeferredRender(ObjectManager* ObjectManagerRef, const glm::mat4& Projection, const glm::mat4& View, const glm::vec3 CameraPosition)
	{
		DirLightProjection = glm::ortho(-100.f, 100.f, 100.0f, -100.0f);
		SetProjectionView(Projection, View);
		SetCameraPosition(CameraPosition);
		DeferredPrePassStartFrame();
		DeferredGeometryPass(ObjectManagerRef);
		glEnable(GL_STENCIL_TEST);
		for (auto point : ObjectManagerRef->GetLightsList()) {
			if (point.second->GetLightType() == YLightType::YPointLight) {
				PointLight* Temp = static_cast<PointLight*>(point.second);
				//DeferredPointLightShadows(ObjectManagerRef, Temp);
				DeferredStencilPass(ObjectManagerRef, Temp);
				DeferredPointLightPass(ObjectManagerRef, Temp);
			}
		}
		glDisable(GL_STENCIL_TEST);
		for (auto point : ObjectManagerRef->GetLightsList()) {
			if (point.second->GetLightType() == YLightType::YDirectionalLight) {
				DeferredDirectionalLightPass(ObjectManagerRef, static_cast<DirectionalLight*>(point.second));
			}
		}
		DeferredFinalPass();
	}

	void DeferredRendering::GBufferLightPassX4()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GBufferMap->ReadGBuffer();

		GLsizei HalfWidth = (GLsizei)(WindowWidth / 2.0f);
		GLsizei HalfHeight = (GLsizei)(WindowHeight / 2.0f);

		GBufferMap->SetReadBuffer(GBufferShader::GBUFFER_TEXTURE_TYPE_POSITION);
		glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
			0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		GBufferMap->SetReadBuffer(GBufferShader::GBUFFER_TEXTURE_TYPE_DIFFUSE);
		glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
			0, HalfHeight, HalfWidth, WindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		GBufferMap->SetReadBuffer(GBufferShader::GBUFFER_TEXTURE_TYPE_NORMAL);
		glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
			HalfWidth, HalfHeight, WindowWidth, WindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		GBufferMap->SetReadBuffer(GBufferShader::GBUFFER_TEXTURE_TYPE_TEXCOORD);
		glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
			HalfWidth, 0, WindowWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	void DeferredRendering::GBufferGeometryPass(ObjectManager* ObjectManagerRef)
	{
		ShaderList[0]->UseShader();

		GBufferMap->Write();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		UniformModel = ShaderList[0]->GetModelMatrixLocation();
		UniformSpecularIntensity = ShaderList[0]->GetSpecularIntensityLocation();
		UniformShininess = ShaderList[0]->GetShininessLocation();

		ShaderList[0]->SetProjectionView(Projection, View);
		ShaderList[0]->SetEyePosition(CameraPosition);

		ShaderList[0]->Validate();

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);
	}

	void DeferredRendering::DeferredDirectionalLightShadows(ObjectManager* ObjectManagerRef, DirectionalLight* dLight)
	{
		ShaderList[4]->UseShader();

		glViewport(0, 0, dLight->GetShadowMap()->GetShadowWidth(), dLight->GetShadowMap()->GetShadowHeight());

		dLight->GetShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		glm::mat4 LightTransform = glm::mat4(1.0f);
		UniformModel = ShaderList[4]->GetModelMatrixLocation();
		LightTransform = dLight->CalculateDirectionalLightTransform();
		ShaderList[4]->SetDirectionalLightTransform(&LightTransform);

		ShaderList[4]->Validate();

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);
	}

	void DeferredRendering::DeferredPointLightShadows(ObjectManager* ObjectManagerRef, PointLight* pLight)
	{
		ShaderList[5]->UseShader();

		glViewport(0, 0, pLight->GetShadowMap()->GetShadowWidth(), pLight->GetShadowMap()->GetShadowHeight());

		pLight->GetShadowMap()->Write();
		glClear(GL_DEPTH_BUFFER_BIT);

		UniformModel = ShaderList[5]->GetModelMatrixLocation();
		ShaderList[5]->SetOmniShadowSpecs(pLight->GetPosition(), pLight->GetFarPlane());

		ShaderList[5]->SetLightMatrices(pLight->CalculateLightTransform());

		ShaderList[5]->Validate();

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void DeferredRendering::DeferredPrePassStartFrame()
	{
		GBufferMap->StartFrame();
	}

	void DeferredRendering::DeferredGeometryPass(ObjectManager* ObjectManagerRef)
	{
		ShaderList[0]->UseShader();

		GBufferMap->BindForGeomPass();

		glViewport(0, 0, WindowWidth, WindowHeight);
		glDepthMask(GL_TRUE);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		UniformModel = ShaderList[0]->GetModelMatrixLocation();
		ShaderList[0]->SetProjectionView(Projection, View);

		RenderObjectsWithMaterialSpecs(ObjectManagerRef);

		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
	}
	
	void DeferredRendering::DeferredStencilPass(ObjectManager* ObjectManagerRef, PointLight* pLight)
	{
		ShaderList[1]->UseShader();

		GBufferMap->BindForStencilPass();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClear(GL_STENCIL_BUFFER_BIT);

		glStencilFunc(GL_ALWAYS, 0, 0);

		glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
		glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

		UniformModel = ShaderList[1]->GetModelMatrixLocation();
		ShaderList[1]->SetProjectionView(Projection, View);

		ShaderList[1]->Validate();

		RenderLightVolumes(ObjectManagerRef, pLight);
	}

	void DeferredRendering::DeferredPointLightPass(ObjectManager* ObjectManagerRef, PointLight* pLight)
	{
		ShaderList[2]->UseShader();

		GBufferMap->BindForLightPass();

		glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		ShaderList[2]->SetGSamplers(GBufferShader::GBUFFER_TEXTURE_TYPE_POSITION + 3, GBufferShader::GBUFFER_TEXTURE_TYPE_DIFFUSE + 3, GBufferShader::GBUFFER_TEXTURE_TYPE_NORMAL + 3);

		//glViewport(0, 0, MainWindow->GetWindowWidth(), MainWindow->GetWindowHeight());

		UniformModel = ShaderList[2]->GetModelMatrixLocation();
		UniformSpecularIntensity = ShaderList[2]->GetSpecularIntensityLocation();
		UniformShininess = ShaderList[2]->GetShininessLocation();

		ShaderList[2]->SetProjectionView(Projection, View);
		ShaderList[2]->SetEyePosition(CameraPosition);
		ShaderList[2]->SetScreenSize(glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

		ShaderList[2]->GetLocationsForLighting(pLight);
		ObjectManagerRef->UseLights();

		ShaderList[2]->Validate();

		RenderLightVolumes(ObjectManagerRef, pLight);

		glCullFace(GL_BACK);
		glDisable(GL_BLEND);
	}

	void DeferredRendering::DeferredDirectionalLightPass(ObjectManager* ObjectManagerRef, DirectionalLight* dLight)
	{
		GBufferMap->BindForLightPass();

		ShaderList[3]->UseShader();

		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);

		ShaderList[3]->SetGSamplers(GBufferShader::GBUFFER_TEXTURE_TYPE_POSITION + 3, GBufferShader::GBUFFER_TEXTURE_TYPE_DIFFUSE + 3, GBufferShader::GBUFFER_TEXTURE_TYPE_NORMAL + 3);

		//glViewport(0, 0, MainWindow->GetWindowWidth(), MainWindow->GetWindowHeight());

		UniformModel = ShaderList[3]->GetModelMatrixLocation();
		UniformSpecularIntensity = ShaderList[3]->GetSpecularIntensityLocation();
		UniformShininess = ShaderList[3]->GetShininessLocation();

		//ShaderList[3]->SetProjectionView(Projection, View);
		ShaderList[3]->SetProjectionView(DirLightProjection, View);
		ShaderList[3]->SetEyePosition(CameraPosition);
		ShaderList[3]->SetScreenSize(glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

		ShaderList[3]->GetLocationsForLighting(dLight);
		ObjectManagerRef->UseLights();
		ShaderList[3]->Validate();

		RenderLightVolumes(ObjectManagerRef, dLight);

		glDisable(GL_BLEND);
	}

	void DeferredRendering::DeferredFinalPass()
	{
		GBufferMap->BindForFinalPass();
		glBlitFramebuffer(0, 0, WindowWidth, WindowHeight, 0, 0, WindowWidth, WindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

	float DeferredRendering::CalcPointLightSphereScale(PointLight* pLight)
	{
		return 0.0f;
	}

	void DeferredRendering::RenderObjectsWithMaterialSpecs(ObjectManager* ObjectManagerRef)
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

	void DeferredRendering::RenderLightVolumes(ObjectManager* ObjectManagerRef, Light* BaseLight)
	{
		ObjectManagerRef->AddModelMatrixLocation(UniformModel);
		auto MeshList = ObjectManagerRef->GetMeshList();
		for (auto a : MeshList) {
			a.second->SetSpecs(UniformSpecularIntensity, UniformShininess);
			a.second->AddSpecs();
		}
		ObjectManagerRef->RenderLightVolumes(BaseLight);
	}

	DeferredRendering::~DeferredRendering()
	{
	}
}
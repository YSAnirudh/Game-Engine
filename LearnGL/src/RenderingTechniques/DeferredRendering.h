#ifndef DEFERRED_RENDERING_H
#define DEFERRED_RENDERING_H

#include "Rendering.h"
#include "Managers/ObjectManager.h"
#include "Shaders/GBufferShader.h"

namespace YSAoo {
	class DeferredRendering : public Rendering
	{
	public:
		DeferredRendering();
		DeferredRendering(GLuint WindowWidth, GLuint WindowHeight);

		void GBufferRender(ObjectManager* ObjectManagerRef, const glm::mat4& Projection, const glm::mat4& View, const glm::vec3 CameraPosition);
		void DeferredRender(ObjectManager* ObjectManagerRef, const glm::mat4& Projection, const glm::mat4& View, const glm::vec3 CameraPosition);
		
		void GBufferGeometryPass(ObjectManager* ObjectManagerRef);
		void GBufferLightPassX4();

		void DeferredDirectionalLightShadows(ObjectManager* ObjectManagerRef, DirectionalLight* dLight);
		void DeferredPointLightShadows(ObjectManager* ObjectManagerRef, PointLight* pLight);
		void DeferredPrePassStartFrame();
		void DeferredGeometryPass(ObjectManager* ObjectManagerRef);
		void DeferredStencilPass(ObjectManager* ObjectManagerRef, PointLight* pLight);
		void DeferredPointLightPass(ObjectManager* ObjectManagerRef, PointLight* pLight);
		void DeferredDirectionalLightPass(ObjectManager* ObjectManagerRef, DirectionalLight* dLight);

		void DeferredFinalPass();

		float CalcPointLightSphereScale(PointLight* pLight);

		void RenderObjectsWithMaterialSpecs(ObjectManager* ObjectManagerRef);
		void RenderLightVolumes(ObjectManager* ObjectManagerRef, Light* BaseLight);

		~DeferredRendering();
	private:
		GBufferShader* GBufferMap = nullptr;
		glm::mat4 DirLightProjection;
	};
}
#endif
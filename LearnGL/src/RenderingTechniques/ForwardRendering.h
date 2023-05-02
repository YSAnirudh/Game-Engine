#ifndef FORWARD_RENDERING_H
#define FORWARD_RENDERING_H

#include "Rendering.h"
#include "Shaders/ForwardShader.h"
#include "Managers/ObjectManager.h"

namespace YSAoo {
	class ForwardRendering : public Rendering
	{
	public:
		ForwardRendering();
		ForwardRendering(GLint WindowWidth, GLint WindowHeight);
		void ForwardRender(ObjectManager* ObjectManagerRef, const glm::mat4& Projection, const glm::mat4& View, const glm::vec3 CameraPosition);
		virtual void AddShader(const char* VertexShaderLocation, const char* FragmentShaderLocation, const char* GeometryShaderLocation = "") override;
		~ForwardRendering();
	private:
		void DirectionalShadowMapPass(ObjectManager* ObjectManagerRef, DirectionalLight* dLight);
		void OmniDirectionalShadowMapPass(ObjectManager* ObjectManagerRef, PointLight* pLight);
		void RenderPass(ObjectManager* ObjectManagerRef);
		void RenderObjectsWithMaterialSpecs(ObjectManager* ObjectManagerRef);
	
	private:
	};
}
#endif
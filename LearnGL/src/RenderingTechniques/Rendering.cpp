#include "Rendering.h"

YSAoo::Rendering::Rendering()
{
	Projection = glm::mat4();
	View = glm::mat4();
	CameraPosition = glm::vec3();
}

void YSAoo::Rendering::AddShader(const char* VertexShaderLocation, const char* FragmentShaderLocation, const char* GeometryShaderLocation)
{
	ShaderList.push_back(new Shader());
	if (GeometryShaderLocation == "") {
		ShaderList[ShaderList.size() - 1]->CreateFromFiles(VertexShaderLocation, FragmentShaderLocation);
	}
	else {
		ShaderList[ShaderList.size() - 1]->CreateFromFiles(VertexShaderLocation, FragmentShaderLocation, GeometryShaderLocation);
	}
}

YSAoo::Rendering::~Rendering()
{
}

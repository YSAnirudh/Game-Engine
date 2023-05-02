#include "Shader.h"

YSAoo::Shader::Shader()
{
	ShaderType = YShaderType::YLightingShader;
}

void YSAoo::Shader::CreateShaderFromString(const char* VertexCodeLocation, const char* FragmentCodeLocation)
{
	CompileShaders(VertexCodeLocation, FragmentCodeLocation);
}

void YSAoo::Shader::CreateFromFiles(const char* VertexShaderLocation, const char* FragmentShaderLocation, const char* GeometryShaderLocation)
{
	std::string VertexString = ReadFromFile(VertexShaderLocation);
	std::string GeometryString = ReadFromFile(GeometryShaderLocation);
	std::string FragmentString = ReadFromFile(FragmentShaderLocation);

	CompileShaders(VertexString.c_str(), FragmentString.c_str(), GeometryString.c_str());
}

void YSAoo::Shader::CreateFromFiles(const char* VertexShaderLocation, const char* FragmentShaderLocation)
{
	std::string VertexString = ReadFromFile(VertexShaderLocation);;
	std::string FragmentString = ReadFromFile(FragmentShaderLocation);

	CompileShaders(VertexString.c_str(), FragmentString.c_str());
}

void YSAoo::Shader::GetLocationsForLighting(Light* MainLight)
{
	if (ShaderType == YShaderType::YLightingShader) {
		switch (MainLight->GetLightType()) {
		case YLightType::YDirectionalLight:
		{
			DirectionalLight* dLight = static_cast<DirectionalLight*>(MainLight);

			if (dLight) {
				dLight->DirectionalLightStruct.Base.ColorLocation = glGetUniformLocation(ShaderID, "directionalLight.base.color");
				dLight->DirectionalLightStruct.Base.AmbientIntensityLocation = glGetUniformLocation(ShaderID, "directionalLight.base.ambientIntensity");
				dLight->DirectionalLightStruct.Base.DiffuseIntensityLocation = glGetUniformLocation(ShaderID, "directionalLight.base.diffuseIntensity");
				dLight->DirectionalLightStruct.DirectionLocation = glGetUniformLocation(ShaderID, "directionalLight.direction");
			}
			MainLight = dLight;
			dLight = nullptr;
		}
		break;
		case YLightType::YPointLight:
		{
			PointLight* pLight = static_cast<PointLight*>(MainLight);

			if (pLight) {
				pLight->PointLightStruct.Base.ColorLocation = glGetUniformLocation(ShaderID, "pointLight.base.color");
				pLight->PointLightStruct.Base.AmbientIntensityLocation = glGetUniformLocation(ShaderID, "pointLight.base.ambientIntensity");
				pLight->PointLightStruct.Base.DiffuseIntensityLocation = glGetUniformLocation(ShaderID, "pointLight.base.diffuseIntensity");
				pLight->PointLightStruct.PositionLocation = glGetUniformLocation(ShaderID, "pointLight.position");
				pLight->PointLightStruct.ConstantLocation = glGetUniformLocation(ShaderID, "pointLight.constant");
				pLight->PointLightStruct.LinearLocation = glGetUniformLocation(ShaderID, "pointLight.linear");
				pLight->PointLightStruct.ExponentLocation = glGetUniformLocation(ShaderID, "pointLight.exponent");

				pLight->GetShadowMap()->Read(GL_TEXTURE2);
				glUniform1i(uniformOmniShadowMaps.shadowMap, 2);
				glUniform1f(uniformOmniShadowMaps.farPlane, pLight->GetFarPlane());
			}
			MainLight = pLight;
			pLight = nullptr;
		}
		break;
		case YLightType::YSpotLight:
		{
			SpotLight* sLight = static_cast<SpotLight*>(MainLight);

			if (sLight) {
				sLight->SpotLightStruct.Base.Base.ColorLocation = glGetUniformLocation(ShaderID, "spotLight.base.base.color");
				sLight->SpotLightStruct.Base.Base.AmbientIntensityLocation = glGetUniformLocation(ShaderID, "spotLight.base.base.ambientIntensity");
				sLight->SpotLightStruct.Base.Base.DiffuseIntensityLocation = glGetUniformLocation(ShaderID, "spotLight.base.base.diffuseIntensity");
				sLight->SpotLightStruct.Base.PositionLocation = glGetUniformLocation(ShaderID, "spotLight.base.position");
				sLight->SpotLightStruct.Base.ConstantLocation = glGetUniformLocation(ShaderID, "spotLight.base.constant");
				sLight->SpotLightStruct.Base.LinearLocation = glGetUniformLocation(ShaderID, "spotLight.base.linear");
				sLight->SpotLightStruct.Base.ExponentLocation = glGetUniformLocation(ShaderID, "spotLight.base.exponent");
				sLight->SpotLightStruct.DirectionLocation = glGetUniformLocation(ShaderID, "spotLight.direction");
				sLight->SpotLightStruct.ProcEdgeLocation = glGetUniformLocation(ShaderID, "spotLight.edge");
			}
			MainLight = sLight;
			sLight = nullptr;
		}
		break;
		default:
			printf("Check Light Type. Cant detect Light Type for %s\n", MainLight->GetObjectName());
			break;
		}
	}
}

void YSAoo::Shader::SetTexture(GLuint TextureUnit)
{
	glUniform1i(UniformTexture, TextureUnit);
}

void YSAoo::Shader::SetDirectionalShadowMap(GLuint TextureUnit)
{
	glUniform1i(UniformDirectionalShadowMap, TextureUnit);
}

void YSAoo::Shader::SetDirectionalLightTransform(glm::mat4* MatTrans)
{
	//PRINT_MATRIX(&MatTrans);
	glUniformMatrix4fv(UniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*MatTrans));
}

void YSAoo::Shader::SetLightMatrices(std::vector<glm::mat4> LightMatrices)
{
	for (size_t i = 0; i < 6; i++) {
		glUniformMatrix4fv(UniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(LightMatrices[i]));
	}
}

void YSAoo::Shader::SetGSamplers(GLuint TextureUnitPos, GLuint TextureUnitColor, GLuint TextureUnitNorm)
{
	glUniform1i(UniformGPositionMap, TextureUnitPos);
	glUniform1i(UniformGColorMap, TextureUnitColor);
	glUniform1i(UniformGNormalMap, TextureUnitNorm);
}

void YSAoo::Shader::SetScreenSize(const glm::vec2& ScreenSize)
{
	glUniform2f(UniformScreenSize, ScreenSize.x, ScreenSize.y);
}

void YSAoo::Shader::SetProjectionView(const glm::mat4& ProjectionMatrix, const glm::mat4& ViewMatrix)
{
	glUniformMatrix4fv(UniformProjectionMatrix, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	glUniformMatrix4fv(UniformViewMatrix, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
}

void YSAoo::Shader::SetEyePosition(const glm::vec3& CameraPosition)
{
	glUniform3f(UniformEyePositionLocation, CameraPosition.x, CameraPosition.y, CameraPosition.z);
}

void YSAoo::Shader::SetOmniShadowSpecs(const glm::vec3& PointLightPosition, const GLfloat& FarPlane)
{
	glUniform3f(UniformOmniLightPos, PointLightPosition.x, PointLightPosition.y, PointLightPosition.z);
	glUniform1f(UniformFarPlane, FarPlane);
}

std::string YSAoo::Shader::ReadFromFile(const char* Location)
{
	std::string content;
	std::ifstream fileStream(Location, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to open file at Location: %s", Location);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();

	return content;
}

void YSAoo::Shader::UseShader()
{
	glUseProgram(ShaderID);
}

void YSAoo::Shader::ClearShader()
{
	if (ShaderID != 0) {
		glDeleteProgram(ShaderID);
		ShaderID = 0;
	}

	UniformModelMatrix = 0;
	UniformProjectionMatrix = 0;
}

int YSAoo::Shader::CompileShaders(const char* VertexCode, const char* FragmentCode, const char* GeometryCode)
{
	ShaderID = glCreateProgram();

	if (!ShaderID) {
		printf("Cannot create Shader Program");
		return 1;
	}

	AddShader(ShaderID, VertexCode, GL_VERTEX_SHADER);
	AddShader(ShaderID, GeometryCode, GL_GEOMETRY_SHADER);
	AddShader(ShaderID, FragmentCode, GL_FRAGMENT_SHADER);

	CompileProgram();
	
	return 0;
}

int YSAoo::Shader::CompileShaders(const char* VertexCode, const char* FragmentCode)
{
	ShaderID = glCreateProgram();

	if (!ShaderID) {
		printf("Cannot create Shader Program");
		return 1;
	}

	AddShader(ShaderID, VertexCode, GL_VERTEX_SHADER);
	AddShader(ShaderID, FragmentCode, GL_FRAGMENT_SHADER);

	CompileProgram();
	return 0;
}

void YSAoo::Shader::Validate()
{
	GLint Result = 0;
	GLchar eLog[1024] = { 0 };

	glValidateProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_VALIDATE_STATUS, &Result);
	if (!Result) {
		glGetProgramInfoLog(ShaderID, sizeof(eLog), NULL, eLog);
		printf("Error Validating the Shader Program:\n");
		printf("Info: %s\n", eLog);
		return;
	}
}

int YSAoo::Shader::CompileProgram()
{
	printf("Compliing Shaders...\n");
	GLint Result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_LINK_STATUS, &Result);
	if (!Result) {
		glGetProgramInfoLog(ShaderID, sizeof(eLog), NULL, eLog);
		printf("Error Linking the Shader Program:\n");
		printf("Info: %s\n", eLog);
		return 1;
	}

	UniformModelMatrix = glGetUniformLocation(ShaderID, "model");
	UniformProjectionMatrix = glGetUniformLocation(ShaderID, "projection");
	UniformViewMatrix = glGetUniformLocation(ShaderID, "view");
	UniformSpecularIntensity = glGetUniformLocation(ShaderID, "material.specularIntensity");
	UniformShininess = glGetUniformLocation(ShaderID, "material.shininess");
	UniformEyePositionLocation = glGetUniformLocation(ShaderID, "eyePosition");

	UniformTexture = glGetUniformLocation(ShaderID, "theTexture");
	UniformDirectionalLightTransform = glGetUniformLocation(ShaderID, "directionalLightSpaceTransform");
	UniformDirectionalShadowMap = glGetUniformLocation(ShaderID, "directionalShadowMap");

	UniformGPositionMap = glGetUniformLocation(ShaderID, "gPositionMap");
	UniformGColorMap = glGetUniformLocation(ShaderID, "gColorMap");
	UniformGNormalMap = glGetUniformLocation(ShaderID, "gNormalMap");

	UniformScreenSize = glGetUniformLocation(ShaderID, "screenSize");

	UniformOmniLightPos = glGetUniformLocation(ShaderID, "lightPos");
	UniformFarPlane = glGetUniformLocation(ShaderID, "farPlane");

	for (size_t i = 0; i < 6; i++) {
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "lightMatrices[%d]", i);
		UniformLightMatrices[i] = glGetUniformLocation(ShaderID, locBuff);
	}
	/*
	if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::FORWARD_RENDERING) {
		UniformDirectionalLight.UniformColor = glGetUniformLocation(ShaderID, "directionalLight.base.color");
		UniformDirectionalLight.UniformAmbientIntensity = glGetUniformLocation(ShaderID, "directionalLight.base.ambientIntensity");
		UniformDirectionalLight.UniformDiffuseIntensity = glGetUniformLocation(ShaderID, "directionalLight.base.diffuseIntensity");
		UniformDirectionalLight.UniformDirection = glGetUniformLocation(ShaderID, "directionalLight.direction");
		//printf("% d\n", UniformDirectionalLight.UniformDirection);

		UniformPointLightCount = glGetUniformLocation(ShaderID, "pointLightCount");

		for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
			char locBuff[100] = { '\0' };

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
			UniformPointLight[i].UniformColor = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
			UniformPointLight[i].UniformAmbientIntensity = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
			UniformPointLight[i].UniformDiffuseIntensity = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
			UniformPointLight[i].UniformPosition = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
			UniformPointLight[i].UniformConstant = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
			UniformPointLight[i].UniformLinear = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
			UniformPointLight[i].UniformExponent = glGetUniformLocation(ShaderID, locBuff);
		}

		UniformSpotLightCount = glGetUniformLocation(ShaderID, "spotLightCount");

		for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
			char locBuff[100] = { '\0' };

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
			UniformSpotLight[i].UniformColor = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
			UniformSpotLight[i].UniformAmbientIntensity = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
			UniformSpotLight[i].UniformDiffuseIntensity = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
			UniformSpotLight[i].UniformPosition = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
			UniformSpotLight[i].UniformConstant = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
			UniformSpotLight[i].UniformLinear = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
			UniformSpotLight[i].UniformExponent = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d]direction", i);
			UniformSpotLight[i].UniformDirection = glGetUniformLocation(ShaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
			UniformSpotLight[i].UniformEdge = glGetUniformLocation(ShaderID, locBuff);
		}
	}
	*/
	//// For Loop for multiple lights

	uniformOmniShadowMaps.shadowMap = glGetUniformLocation(ShaderID, "omniShadowMap.shadowMap");
	uniformOmniShadowMaps.farPlane = glGetUniformLocation(ShaderID, "omniShadowMap.farPlane");

	printf("Compiled Shaders Successfully!\n");
	return 0;
}

int YSAoo::Shader::CompileShadersAndInit(const char* VertexCode, const char* FragmentCode)
{
	ShaderID = glCreateProgram();

	if (!ShaderID) {
		printf("Cannot create Shader Program");
		return 1;
	}

	AddShader(ShaderID, VertexCode, GL_VERTEX_SHADER);
	AddShader(ShaderID, FragmentCode, GL_FRAGMENT_SHADER);

	GLint Result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_LINK_STATUS, &Result);
	if (!Result) {
		glGetProgramInfoLog(ShaderID, sizeof(eLog), NULL, eLog);
		printf("Error Linking the Shader Program:\n");
		printf("Info: %s\n", eLog);
		return 1;
	}

	glValidateProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_VALIDATE_STATUS, &Result);
	if (!Result) {
		glGetProgramInfoLog(ShaderID, sizeof(eLog), NULL, eLog);
		printf("Error Validating the Shader Program:\n");
		printf("Info: %s\n", eLog);
		return 1;
	}

	UniformModelMatrix = glGetUniformLocation(ShaderID, "model");
	UniformProjectionMatrix = glGetUniformLocation(ShaderID, "projection");
	UniformViewMatrix = glGetUniformLocation(ShaderID, "view");
	UniformSpecularIntensity = glGetUniformLocation(ShaderID, "material.specularIntensity");
	UniformShininess = glGetUniformLocation(ShaderID, "material.shininess");
	UniformEyePositionLocation = glGetUniformLocation(ShaderID, "eyePosition");

	//UniformDirectionalLight.UniformColor = glGetUniformLocation(ShaderID, "directionalLight.base.color");
	//UniformDirectionalLight.UniformAmbientIntensity = glGetUniformLocation(ShaderID, "directionalLight.base.ambientIntensity");
	//UniformDirectionalLight.UniformDiffuseIntensity = glGetUniformLocation(ShaderID, "directionalLight.base.diffuseIntensity");
	//UniformDirectionalLight.UniformDirection = glGetUniformLocation(ShaderID, "directionalLight.direction");
	////printf("% d\n", UniformDirectionalLight.UniformDirection);

	//UniformPointLightCount = glGetUniformLocation(ShaderID, "pointLightCount");

	//for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
	//	char locBuff[100] = { '\0' };

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
	//	UniformPointLight[i].UniformColor = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
	//	UniformPointLight[i].UniformAmbientIntensity = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
	//	UniformPointLight[i].UniformDiffuseIntensity = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
	//	UniformPointLight[i].UniformPosition = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
	//	UniformPointLight[i].UniformConstant = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
	//	UniformPointLight[i].UniformLinear = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
	//	UniformPointLight[i].UniformExponent = glGetUniformLocation(ShaderID, locBuff);
	//}

	//UniformSpotLightCount = glGetUniformLocation(ShaderID, "spotLightCount");

	//for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
	//	char locBuff[100] = { '\0' };

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
	//	UniformSpotLight[i].UniformColor = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
	//	UniformSpotLight[i].UniformAmbientIntensity = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
	//	UniformSpotLight[i].UniformDiffuseIntensity = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
	//	UniformSpotLight[i].UniformPosition = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
	//	UniformSpotLight[i].UniformConstant = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
	//	UniformSpotLight[i].UniformLinear = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
	//	UniformSpotLight[i].UniformExponent = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d]direction", i);
	//	UniformSpotLight[i].UniformDirection = glGetUniformLocation(ShaderID, locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
	//	UniformSpotLight[i].UniformEdge = glGetUniformLocation(ShaderID, locBuff);
	//}

	printf("Compiled Shaders Successfully!\n");
	return 0;
}

int YSAoo::Shader::AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
	GLuint TheShader = glCreateShader(ShaderType);

	const GLchar* Code[1];
	Code[0] = ShaderCode;

	GLint CodeLength[1];
	CodeLength[0] = strlen(ShaderCode);

	glShaderSource(TheShader, 1, Code, CodeLength);
	glCompileShader(TheShader);

	GLint Result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(TheShader, GL_COMPILE_STATUS, &Result);
	if (!Result) {
		glGetShaderInfoLog(TheShader, sizeof(eLog), NULL, eLog);
		printf("Error Compiling the %d Shader:\n", ShaderType);
		printf("Info: %s\n", eLog);
		return 1;
	}

	glAttachShader(ShaderProgram, TheShader);

	return 0;
}

YSAoo::Shader::~Shader()
{
	ClearShader();
}

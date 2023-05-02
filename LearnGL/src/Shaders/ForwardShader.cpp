#include "ForwardShader.h"
namespace YSAoo {
	ForwardShader::ForwardShader()
	{
	}

	void ForwardShader::GetLocationsForLighting(Light* MainLight)
	{
		switch (MainLight->GetLightType()) {
		case YLightType::YDirectionalLight:
		{
			DirectionalLight* dLight = static_cast<DirectionalLight*>(MainLight);

			if (dLight) {
				dLight->DirectionalLightStruct.Base.ColorLocation = UniformDirectionalLight[DirLightCount].UniformColor;
				dLight->DirectionalLightStruct.Base.AmbientIntensityLocation = UniformDirectionalLight[DirLightCount].UniformAmbientIntensity;
				dLight->DirectionalLightStruct.Base.DiffuseIntensityLocation = UniformDirectionalLight[DirLightCount].UniformDiffuseIntensity;
				dLight->DirectionalLightStruct.DirectionLocation = UniformDirectionalLight[DirLightCount].UniformDirection;
			}
			MainLight = dLight;
			DirLightCount++;
			dLight = nullptr;
		}
		break;
		case YLightType::YPointLight:
		{
			PointLight* pLight = static_cast<PointLight*>(MainLight);

			if (pLight) {
				pLight->PointLightStruct.Base.ColorLocation = UniformPointLight[PointLightCount].UniformColor;
				pLight->PointLightStruct.Base.AmbientIntensityLocation = UniformPointLight[PointLightCount].UniformAmbientIntensity;
				pLight->PointLightStruct.Base.DiffuseIntensityLocation = UniformPointLight[PointLightCount].UniformDiffuseIntensity;
				pLight->PointLightStruct.PositionLocation = UniformPointLight[PointLightCount].UniformPosition;
				pLight->PointLightStruct.ConstantLocation = UniformPointLight[PointLightCount].UniformConstant;
				pLight->PointLightStruct.LinearLocation = UniformPointLight[PointLightCount].UniformLinear;
				pLight->PointLightStruct.ExponentLocation = UniformPointLight[PointLightCount].UniformExponent;

				pLight->GetShadowMap()->Read(GL_TEXTURE2);
				glUniform1i(uniformOmniShadowMaps.shadowMap, 2);
				glUniform1f(uniformOmniShadowMaps.farPlane, pLight->GetFarPlane());
			}
			MainLight = pLight;
			PointLightCount++;
			pLight = nullptr;
		}
		break;
		case YLightType::YSpotLight:
		{
			SpotLight* sLight = static_cast<SpotLight*>(MainLight);

			if (sLight) {
				sLight->SpotLightStruct.Base.Base.ColorLocation = UniformSpotLight[SpotLightCount].UniformColor;
				sLight->SpotLightStruct.Base.Base.AmbientIntensityLocation = UniformSpotLight[SpotLightCount].UniformAmbientIntensity;
				sLight->SpotLightStruct.Base.Base.DiffuseIntensityLocation = UniformSpotLight[SpotLightCount].UniformDiffuseIntensity;
				sLight->SpotLightStruct.Base.PositionLocation = UniformSpotLight[SpotLightCount].UniformPosition;
				sLight->SpotLightStruct.Base.ConstantLocation = UniformSpotLight[SpotLightCount].UniformConstant;
				sLight->SpotLightStruct.Base.LinearLocation = UniformSpotLight[SpotLightCount].UniformLinear;
				sLight->SpotLightStruct.Base.ExponentLocation = UniformSpotLight[SpotLightCount].UniformExponent;
				sLight->SpotLightStruct.DirectionLocation = UniformSpotLight[SpotLightCount].UniformDirection;
				sLight->SpotLightStruct.ProcEdgeLocation = UniformSpotLight[SpotLightCount].UniformEdge;
			}
			MainLight = sLight;
			SpotLightCount++;
			sLight = nullptr;
		}
		break;
		default:
			printf("Check Light Type. Cant detect Light Type for %s\n", MainLight->GetObjectName());
			break;
		}
	}

	void ForwardShader::SetLightCounts()
	{
		glUniform1i(UniformDirectionalLightCount, DirLightCount);
		glUniform1i(UniformPointLightCount, PointLightCount);
		glUniform1i(UniformSpotLightCount, SpotLightCount);
	}

	void ForwardShader::ResetShaderLightCount()
	{
		DirLightCount = 0;
		PointLightCount = 0;
		SpotLightCount = 0;
	}

	ForwardShader::~ForwardShader()
	{
	}
	int ForwardShader::CompileProgram()
	{
		printf("Compliing Forward Shaders...\n");
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
		
		if (MAIN_RENDERING_TECHNIQUE == RENDERING_TECHNIQUE::FORWARD_RENDERING) {
			UniformDirectionalLightCount = glGetUniformLocation(ShaderID, "dirLightCount");

			for (size_t i = 0; i < MAX_DIR_LIGHTS; i++) {
				char locBuff[100] = { '\0' };

				snprintf(locBuff, sizeof(locBuff), "directionalLights[%d].base.color", i);
				UniformDirectionalLight[i].UniformColor = glGetUniformLocation(ShaderID, locBuff);

				snprintf(locBuff, sizeof(locBuff), "directionalLights[%d].base.ambientIntensity", i);
				UniformDirectionalLight[i].UniformAmbientIntensity = glGetUniformLocation(ShaderID, locBuff);

				snprintf(locBuff, sizeof(locBuff), "directionalLights[%d].base.diffuseIntensity", i);
				UniformDirectionalLight[i].UniformDiffuseIntensity = glGetUniformLocation(ShaderID, locBuff);

				snprintf(locBuff, sizeof(locBuff), "directionalLights[%d].direction", i);
				UniformDirectionalLight[i].UniformDirection = glGetUniformLocation(ShaderID, locBuff);
			}

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

				snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
				UniformSpotLight[i].UniformDirection = glGetUniformLocation(ShaderID, locBuff);

				snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
				UniformSpotLight[i].UniformEdge = glGetUniformLocation(ShaderID, locBuff);
			}
		}
		
		//// For Loop for multiple lights

		uniformOmniShadowMaps.shadowMap = glGetUniformLocation(ShaderID, "omniShadowMap.shadowMap");
		uniformOmniShadowMaps.farPlane = glGetUniformLocation(ShaderID, "omniShadowMap.farPlane");

		printf("Compiled Shaders Successfully!\n");
		return 0;
		return 0;
	}
}
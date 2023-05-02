#version 330

in vec4 vertColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 directionalLightSpacePos;

out vec4 color;

struct Light
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight
{
    Light base;
    vec3 direction;
};

struct PointLight
{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight
{
    PointLight base;
    vec3 direction;
    float edge;
};

struct OmniShadowMap
{
    samplerCube shadowMap;
    float farPlane;
};

struct Material 
{
    float specularIntensity;
    float shininess;
};

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;
uniform OmniShadowMap omniShadowMap;

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform Material material;

uniform vec3 eyePosition;

vec3 sampleOffsetDirections[20] = vec3[]
(
    vec3(1,1,1),vec3(1,-1,1),vec3(-1,-1,1),vec3(-1,1,1),
    vec3(1,1,-1),vec3(1,-1,-1),vec3(-1,-1,-1),vec3(-1,1,-1),
    vec3(1,1,0),vec3(1,-1,0),vec3(-1,-1,0),vec3(-1,1,0),
    vec3(1,0,1),vec3(-1,0,1),vec3(1,0,-1),vec3(-1,0,-1),
    vec3(0,1,1),vec3(0,-1,1),vec3(0,-1,-1),vec3(0,1,-1)
);

float CalcDirectionalShadowFactor(DirectionalLight dLight) {
    vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
    projCoords = (projCoords * 0.5) + 0.5;

    float current = projCoords.z; 

    vec3 mainNormal = normalize(normal);
    vec3 lightDir = normalize(dLight.direction);

    float bias = max(0.05 * (1 - dot(mainNormal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += current - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;
    
    if (projCoords.z > 1.0) {
        shadow = 0.0;
    }
    
    return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor) {
    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
    vec4 diffuseColor = vec4(light.color, 1.0f) * diffuseFactor * light.diffuseIntensity;

    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (diffuseFactor > 0.0f) {
        vec3 fragToEye = normalize(eyePosition - fragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));

        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor > 0.0f) {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(light.color, 1.0f) * specularFactor * material.specularIntensity;
        }
    }

    return (ambientColor + (1 - shadowFactor) * (diffuseColor + specularColor));
}

void main() {
    float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
    vec4 finalColor = CalcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
    
    color = texture(theTexture, texCoord) * finalColor;
}
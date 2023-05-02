#version 330

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

struct Material 
{
    float specularIntensity;
    float shininess;
};

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform sampler2D directionalShadowMap;

uniform Material material;
uniform vec3 eyePosition;
uniform vec2 screenSize;

float CalcDirectionalShadowFactor(DirectionalLight dLight, vec3 normal) {
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

vec4 CalcLightByDirection(Light light, vec3 direction, vec3 normal, vec3 fragPos, float shadowFactor) {
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
    //return (ambientColor + (diffuseColor + specularColor));
}

vec4 CalcDirectionalLight(vec3 normal, vec3 fragPos) {
    float shadowFactor = CalcDirectionalShadowFactor(directionalLight, normal);

    return CalcLightByDirection(directionalLight.base, directionalLight.direction, normal, fragPos, shadowFactor);
}

vec2 CalcTexCoord() {
    return gl_FragCoord.xy / screenSize;
}

void main()
{
    vec2 TexCoord = CalcTexCoord();
    vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
    vec3 Color = texture(gColorMap, TexCoord).xyz;
    vec3 Normal = texture(gNormalMap, TexCoord).xyz;
    Normal = normalize(Normal);

    //float shadowFactor = CalcDirectionalShadowFactor(directionalLight, Normal);
    color = vec4(Color, 1.0) * CalcLightByDirection(directionalLight.base, directionalLight.direction, Normal, WorldPos, 0.0);
}
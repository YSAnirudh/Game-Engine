#version 330

in vec4 vertColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 directionalLightSpacePos;

const MAX_DIR_LIGHTS = 8;
const MAX_POINT_LIGHTS = 8;
const MAX_SPOT_LIGHTS = 8;

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

float CalcOmniShadowFactor(PointLight pLight, int shadowIndex) {
    vec3 fragToLight = fragPos - pLight.position;
    float closest = texture(omniShadowMap.shadowMap, fragToLight).r;

    closest = closest * omniShadowMap.farPlane;

    float shadow = 0.0;
    float bias = 0.05;
    int samples = 20;
    float current = length(fragToLight);

    float viewDistance = length(eyePosition - fragPos);
    float diskRadius = (1.0 + (viewDistance / omniShadowMap.farPlane)) / 25.0;

    for (int i = 0; i < samples; i++) {
        float closest = texture(omniShadowMap.shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
        closest *= omniShadowMap.farPlane;

        if (current - bias > closest) {
            shadow += 1.0;
        }
    }

    shadow /= float(samples);
    
    return shadow;
}

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

vec4 CalcPointLight(PointLight pLight) {//Shadow Index include for multiple lights
    vec3 direction = fragPos - pLight.position;
    float fragDistance = length(direction);
    direction = normalize(direction);

    float shadowFactor = CalcOmniShadowFactor(pLight, 0);

    vec4 color = CalcLightByDirection(pLight.base, direction, shadowFactor);

    float attenuation = (pLight.exponent * fragDistance * fragDistance) + (pLight.linear * fragDistance) + pLight.constant;
    if (attenuation < 0.0f) {
        return color;
    }
    return color/attenuation;
    // return (color / attenuation);
}

vec4 CalcPointLights() {
    vec4 totalColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    return totalColor;
}

vec4 CalcSpotLight(SpotLight sLight) {
    vec3 rayDirection = normalize(fragPos - sLight.base.position);

    float slFactor = dot(rayDirection, normalize(sLight.direction));

    if (slFactor > sLight.edge) {
        vec4 color = CalcPointLight(sLight.base);

        return color * (1.0f - ((1.0f - slFactor) * (1.0f / (1.0f - sLight.edge))));
    }
    return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

vec4 CalcSpotLights() {
    vec4 totalColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    return totalColor;
}

void main() {
    float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
    vec4 finalColor = CalcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
    finalColor += CalcPointLight(pointLight);
    //finalColor += CalcSpotLight(spotLight);
    // vertColor -> finalColor
    color = texture(theTexture, texCoord) * finalColor;
    //color = vertColor;
}
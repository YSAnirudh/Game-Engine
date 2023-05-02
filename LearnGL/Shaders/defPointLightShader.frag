#version 330

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

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform OmniShadowMap omniShadowMap;

uniform Material material;
uniform vec3 eyePosition;
uniform vec2 screenSize;

vec3 sampleOffsetDirections[20] = vec3[]
(
    vec3(1,1,1),vec3(1,-1,1),vec3(-1,-1,1),vec3(-1,1,1),
    vec3(1,1,-1),vec3(1,-1,-1),vec3(-1,-1,-1),vec3(-1,1,-1),
    vec3(1,1,0),vec3(1,-1,0),vec3(-1,-1,0),vec3(-1,1,0),
    vec3(1,0,1),vec3(-1,0,1),vec3(1,0,-1),vec3(-1,0,-1),
    vec3(0,1,1),vec3(0,-1,1),vec3(0,-1,-1),vec3(0,1,-1)
);

float CalcOmniShadowFactor(PointLight pLight, vec3 fragPos) {
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

vec4 CalcPointLight(vec3 normal, vec3 fragPos) {//Shadow Index include for multiple lights
    vec3 direction = fragPos - pointLight.position;
    float fragDistance = length(direction);
    direction = normalize(direction);

    //float shadowFactor = CalcOmniShadowFactor(pointLight, fragPos);

    vec4 color = CalcLightByDirection(pointLight.base, direction, normal, fragPos, 0.0);

    float attenuation = (pointLight.exponent * fragDistance * fragDistance) + (pointLight.linear * fragDistance) + pointLight.constant;
    if (attenuation < 0.0f) {
        return color;
    }
    return color/attenuation;
    // return (color / attenuation);
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

    color = vec4(Color, 1.0) * CalcPointLight(Normal, WorldPos);
}
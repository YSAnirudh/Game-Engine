#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 directionalLightSpaceTransform;

out vec4 vertColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec4 directionalLightSpacePos;


void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    directionalLightSpacePos = directionalLightSpaceTransform * model * vec4(pos, 1.0f);
    vertColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

    texCoord = tex;

    normal = mat3(transpose(inverse(model))) * norm;

    fragPos = (model * vec4(pos, 1.0f)).xyz;
}
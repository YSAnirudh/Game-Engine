#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

void main()
{
    texCoord = tex;

    normal = mat3(transpose(inverse(model))) * norm;

    fragPos = (model * vec4(pos, 1.0f)).xyz;

    gl_Position = projection * view * model * vec4(pos, 1.0f);
}
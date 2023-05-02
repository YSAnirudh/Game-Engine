#version 330
layout (location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 view;

out vec3 texCoord;

void main() {
    gl_Position = projection * view * vec4(pos, 1.0f);

    texCoord = pos;
}
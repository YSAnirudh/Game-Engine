#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gDiffuse;
layout (location = 2) out vec3 gNormal;
layout (location = 3) out vec3 gTexCoord;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D gColorMap;

void main() {
    gPosition = fragPos;

    gNormal = normalize(normal);

    gDiffuse = texture(gColorMap, texCoord).rgb;

    gTexCoord = vec3(texCoord, 0.0);
}
#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;

layout (location = 0) out vec4 positionGBuffer;
layout (location = 1) out vec4 normalGBuffer;
layout (location = 2) out vec4 albedoGBuffer;

void main(){
    positionGBuffer = vec4(fragPosition, 1.0f);
    normalGBuffer = vec4(fragNormal, 1.0f);
    albedoGBuffer = vec4(fragTexCoord, 0.0f, 1.0f);
}

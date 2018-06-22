#version 430 core

in vec3 fragPosition;

uniform vec3 lightColour;

layout (location = 0) out vec4 albedoGBuffer;
layout (location = 1) out vec4 specularGBuffer;
layout (location = 2) out vec4 normalGBuffer;
layout (location = 3) out vec4 positionGBuffer;
layout (location = 4) out vec4 emmisiveGBuffer;

void main(){
    positionGBuffer = vec4(fragPosition, 1.0f);
    normalGBuffer = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    albedoGBuffer = vec4(lightColour, 1.0f);
    specularGBuffer = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    emmisiveGBuffer = vec4(lightColour, 1.0f);
}

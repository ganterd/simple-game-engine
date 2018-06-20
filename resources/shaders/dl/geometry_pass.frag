#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;

layout (location = 0) out vec4 position;
layout (location = 1) out vec4 normal;

void main(){
    position = vec4(vec3(1.0f) - fragNormal, 1.0f);
    normal = vec4(fragNormal, 1.0f);
}

#version 430 core

in vec3 fragPosition;

uniform vec3 inLightPosition;
uniform float inLightNearPlane;
uniform float inLightFarPlane;

out vec4 outDepth;

void main(){
    float depth = (length(fragPosition - inLightPosition) - inLightNearPlane) / inLightFarPlane;
    outDepth = vec4(vec3(depth), 1.0f);
}

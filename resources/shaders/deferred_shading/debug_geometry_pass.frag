#version 430 core

uniform vec4 debugColour;

out vec4 outEmissive;

void main(){
    outEmissive = debugColour;
}

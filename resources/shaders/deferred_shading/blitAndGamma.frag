#version 430 core

in vec2 fragPosition;
out vec4 outColour;

uniform sampler2D lightingPassTexture;


void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec3 colour = vec3(texture(lightingPassTexture, p));
    outColour = vec4(pow(colour, vec3(2.2f)), 1.0f );
    //outColour = texture(lightingPassTexture, p);
}

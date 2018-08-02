#version 430 core

in vec2 fragPosition;
out vec4 outColour;

uniform sampler2D colourFrame;

void main()
{
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    vec4 colour = texture(colourFrame, p);
    vec4 gammaCorrected = pow(colour, vec4(1.0f / 2.2f));
    outColour = vec4(gammaCorrected.rgb, colour.a);
}

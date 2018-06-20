#version 430 core

in vec2 fragPosition;
out vec4 color;

uniform sampler2D positionsTexture;
uniform sampler2D normalsTexture;

void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    if(p.y < 0.5f)
    {
        color = vec4(0.3f,0.3f,0.3f,1.0f);
    }
    else if (p.x < 0.5f)
    {
        color = texture(normalsTexture, (p - vec2(0.0f, 0.5f)) * 2.0f);
    }
    else
    {
        color = texture(positionsTexture, (p - vec2(0.5f, 0.5f)) * 2.0f);
    }
}
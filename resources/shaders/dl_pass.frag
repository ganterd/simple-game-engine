#version 330 core

in vec2 fragPosition;
out vec4 color;

void main(){
    vec2 p = (fragPosition + vec2(1.0f)) * 0.5f;
    color = vec4(p, 0.0f, 1.0f);
}

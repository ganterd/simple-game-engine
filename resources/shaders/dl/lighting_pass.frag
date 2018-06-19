#version 330 core

uniform float bufferWidth;
uniform float bufferHeight;

uniform sampler2D tDiffuse;

in vec2 screen_position;
out vec4 color;

void main(){
	vec2 p = vec2(gl_FragCoord.x / bufferWidth, gl_FragCoord.y / bufferHeight);
	color = texture2D(tDiffuse, p);
}

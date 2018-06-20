#version 330

in vec3 vPosition;

uniform mat4 modelViewProjection;

out vec3 fragNormal;

void main()
{
	vec4 v = vec4(vPosition, 1);
	gl_Position = modelViewProjection * v;
}

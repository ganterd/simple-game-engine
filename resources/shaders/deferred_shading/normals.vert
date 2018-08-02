#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec3 vOther;

uniform mat4 modelViewProjection;

varying vec3 fragNormal;

void main()
{
	vec4 v = vec4(vPosition, 1.0f);
	gl_Position = modelViewProjection * v;
	fragNormal = vNormal;
}

#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec3 vOther;

uniform mat4 modelViewProjection;

out vec3 fragNormal;
out vec3 fragPosition;

void main()
{
	vec4 v = vec4(vPosition, 1);
	gl_Position = modelViewProjection * v;

	fragNormal = vNormal;
	fragPosition = vPosition;
}

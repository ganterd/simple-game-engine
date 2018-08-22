#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

out vec3 fragPosition;

void main()
{
	vec4 v = vec4(vPosition, 1);
	gl_Position = viewProjectionMatrix * modelMatrix * v;

	fragPosition = vec3(modelMatrix * vec4(vPosition, 1.0f));
}

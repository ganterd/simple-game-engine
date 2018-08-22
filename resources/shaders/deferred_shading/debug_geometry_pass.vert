#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vTangent;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;
uniform float pointSize;

out vec3 fragNormal;
out vec3 fragPosition;
out vec2 fragTexCoord;
out mat3 normalMapTransform;

void main()
{
	vec4 v = vec4(vPosition, 1);
	gl_Position = viewProjectionMatrix * modelMatrix * v;
	gl_PointSize = pointSize;
}

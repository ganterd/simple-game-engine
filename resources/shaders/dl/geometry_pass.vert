#version 420

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

uniform mat4 modelViewProjection;

out vec3 fragNormal;
out vec3 fragPosition;
out vec2 fragTexCoord;

void main()
{
	vec4 v = vec4(vPosition, 1);
	gl_Position = modelViewProjection * v;

	fragNormal = vNormal;
	fragPosition = vPosition;
	fragTexCoord = vTexCoord;
}

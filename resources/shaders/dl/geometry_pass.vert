#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vTangent;

uniform mat4 modelViewProjection;
//uniform mat4 modelMatrix;

out vec3 fragNormal;
out vec3 fragPosition;
out vec2 fragTexCoord;
out mat3 normalMapTransform;

void main()
{
	vec4 v = vec4(vPosition, 1);
	gl_Position = modelViewProjection * v;

	fragNormal = vNormal;
	fragPosition = vPosition;
	fragTexCoord = vTexCoord;

	//mat4 modelMatrix = mat4(1.0f); // TMP model matrix
	//vec3 transformedNormal = normalize(vec3(modelMatrix * vec4(vNormal, 0.0f)));
	//vec3 transformedTangent = normalize(vec3(modelMatrix * vec4(vTangent, 0.0f)));
	//vec3 biTangent = cross(transformedNormal, transformedTangent);
	//normalMapTransform = mat3(transformedNormal, biTangent, transformedTangent);

	vec3 biTangent = cross(vNormal, vTangent);
	normalMapTransform = mat3(vTangent, biTangent, vNormal);
}

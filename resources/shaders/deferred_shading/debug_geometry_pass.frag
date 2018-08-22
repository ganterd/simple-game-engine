#version 430 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec2 fragTexCoord;
in mat3 normalMapTransform;

uniform sampler2D specularTexture;
uniform sampler2D normalsTexture;
uniform sampler2D emmisiveTexture;

out vec4 outEmissive;

void main(){
    outEmissive = vec4(0.8f, 1.0f, 0.8f, 0.8f);
    // positions = vec4(fragPosition, opacity);
    // normals = vec4(normal, opacity);
    // diffuse = vec4(vec3(texture(albedoTexture, fragTexCoord)), opacity);
    // specular = vec4(vec3(texture(specularTexture, fragTexCoord)), opacity);
}
